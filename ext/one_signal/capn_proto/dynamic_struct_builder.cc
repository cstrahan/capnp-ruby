#include "ruby_capn_proto.h"
#include "dynamic_struct_builder.h"
#include "dynamic_struct_reader.h"
#include "dynamic_value_reader.h"
#include "dynamic_value_builder.h"
#include "message_builder.h"
#include "malloc_message_builder.h"
#include "class_builder.h"
#include "exception.h"
#include "util.h"
#include "rb_str_output_stream.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicStruct::Builder;
  VALUE DynamicStructBuilder::Class;

  void DynamicStructBuilder::Init() {
    ClassBuilder("DynamicStructBuilder", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("which", &which).
      defineMethod("write", &write).
      defineMethod("write_packed", &write_packed).
      defineMethod("to_packed_string", &to_packed_string).
      defineMethod("to_string", &to_string).
      defineMethod("to_bytes", &to_bytes).
      defineMethod("[]", &get).
      defineMethod("[]=", &set).
      defineMethod("init", (VALUE (*)(int, VALUE*, VALUE))&init).
      store(&Class);
  }

  void DynamicStructBuilder::free(WrappedType* p) {
    p->~Builder();
    ruby_xfree(p);
  }

  VALUE DynamicStructBuilder::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* DynamicStructBuilder::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicStructBuilder::create(WrappedType reader, VALUE parent, bool is_root) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);

    rb_iv_set(rb_obj, "parent", parent);
    rb_iv_set(rb_obj, "is_root", is_root ? Qtrue : Qfalse);

    return rb_obj;
  }

  VALUE DynamicStructBuilder::init(int argc, VALUE* argv, VALUE self) {
    VALUE name;
    VALUE count;

    rb_scan_args(argc, argv, "11", &name, &count);

    try {
      return _init(self, name, count, argc);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::_init(VALUE self, VALUE rb_name, VALUE rb_count, int argc) {
    auto name = Util::toString(rb_name);

    if (argc == 1) {
      return DynamicValueBuilder::to_ruby(unwrap(self)->init(name), self);
    } else {
      auto count = NUM2ULONG(rb_count);
      return DynamicValueBuilder::to_ruby(unwrap(self)->init(name, count), self);
    }
  }

  VALUE DynamicStructBuilder::get(VALUE self, VALUE rb_name) {
    try {
      return _get(self, rb_name);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::_get(VALUE self, VALUE rb_name) {
    auto builder = *unwrap(self);
    auto name = Util::toString(rb_name);
    return DynamicValueBuilder::to_ruby(builder.get(name), self);
  }

  VALUE DynamicStructBuilder::set(VALUE self, VALUE rb_name, VALUE rb_obj) {
    try {
      return _set(self, rb_name, rb_obj);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::_set(VALUE self, VALUE rb_field, VALUE rb_obj) {
    VALUE klass = rb_funcall(rb_obj, rb_intern("class"), 0);
    auto field = Util::toString(rb_field);

    // TODO: handle assigning lists (see _setDynamicField)
    if (FIXNUM_P(rb_obj)) {
      if (Util::isNegative(rb_obj)) {
        unwrap(self)->set(field, NUM2LONG(rb_obj));
      } else {
        unwrap(self)->set(field, NUM2ULONG(rb_obj));
      }
    } else if (RB_TYPE_P(rb_obj, T_FLOAT)) {
      unwrap(self)->set(field, RFLOAT_VALUE(rb_obj));
    } else if (rb_obj == Qtrue || rb_obj == Qfalse) {
      unwrap(self)->set(field, (rb_obj == Qtrue) ? true : false);
    } else if (RB_TYPE_P(rb_obj, T_STRING)) {
      // TODO: need to ensure that the UTF8 char buffer is null terminated.
      // consider something similar to rb_string_value_cstr,
      // which grows the the buffer if necessary.
      capnp::DynamicValue::Reader tmp =
        capnp::Text::Reader(RSTRING_PTR(rb_obj), RSTRING_LEN(rb_obj));
      unwrap(self)->set(field, tmp);
    } else if (NIL_P(rb_obj)) {
      unwrap(self)->set(field, capnp::VOID);
    } else if (rb_equal(klass, DynamicStructReader::Class)) {
      unwrap(self)->set(field, *DynamicStructReader::unwrap(rb_obj));
    } else if (rb_equal(klass, DynamicStructBuilder::Class)) {
      unwrap(self)->set(field, (*DynamicStructBuilder::unwrap(rb_obj)).asReader());
    } else {
      // TODO: raise "Non primitive type"
    }

    return rb_obj;
  }

  VALUE DynamicStructBuilder::write(VALUE self, VALUE file) {
    VALUE rb_fileno = rb_funcall(file, rb_intern("fileno"), 0);
    int fileno = FIX2INT(rb_fileno);
    if (!RTEST(rb_iv_get(self, "is_root"))) {
      rb_raise(Exception::Class, "You can only call write() on the message's root struct.");
    }

    capnp::MessageBuilder* message_builder = MallocMessageBuilder::unwrap(rb_iv_get(self, "parent"));
    try {
      capnp::writeMessageToFd(fileno, message_builder->getSegmentsForOutput());
      return Qnil;
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::write_packed(VALUE self, VALUE file) {
    VALUE rb_fileno = rb_funcall(file, rb_intern("fileno"), 0);
    int fileno = FIX2INT(rb_fileno);
    if (!RTEST(rb_iv_get(self, "is_root"))) {
      rb_raise(Exception::Class, "You can only call write_packed() on the message's root struct.");
    }

    capnp::MessageBuilder* message_builder = MallocMessageBuilder::unwrap(rb_iv_get(self, "parent"));
    try {
      capnp::writePackedMessageToFd(fileno, message_builder->getSegmentsForOutput());
      return Qnil;
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::to_string(VALUE self, VALUE str) {
    if (!RTEST(rb_iv_get(self, "is_root")))
    {
      rb_raise(Exception::Class, "You can only call write_packed() on the message's root struct.");
    }

    auto str_output = new RbStrOutputStream(str);
    capnp::MessageBuilder *message_builder = MallocMessageBuilder::unwrap(rb_iv_get(self, "parent"));
    try
    {
      capnp::writeMessage(*str_output, message_builder->getSegmentsForOutput());
      return Qnil;
    }
    catch (kj::Exception ex)
    {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::to_packed_string(VALUE self, VALUE str) {
    if (!RTEST(rb_iv_get(self, "is_root")))
    {
      rb_raise(Exception::Class, "You can only call write_packed() on the message's root struct.");
    }

    auto str_output = new RbStrOutputStream(str);
    capnp::MessageBuilder *message_builder = MallocMessageBuilder::unwrap(rb_iv_get(self, "parent"));
    try
    {
      capnp::writePackedMessage(*str_output, message_builder->getSegmentsForOutput());
      return Qnil;
    }
    catch (kj::Exception ex)
    {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicStructBuilder::to_bytes(VALUE self)
  {
    if (!RTEST(rb_iv_get(self, "is_root"))) {
      rb_raise(Exception::Class, "You can only call to_bytes() on the message's root struct.");
    }

    capnp::MessageBuilder* message_builder = MallocMessageBuilder::unwrap(rb_iv_get(self, "parent"));
    auto array = capnp::messageToFlatArray(*message_builder);
    return rb_str_new((char*)array.begin(), sizeof(capnp::word) * array.size());
  }

  VALUE DynamicStructBuilder::which(VALUE self) {
    auto schema_maybe = unwrap(self)->which();
    KJ_IF_MAYBE(schema, schema_maybe) {
      auto name = schema->getProto().getName();
      return rb_str_new(name.begin(), name.size());
    } else {
      // throw std::invalid_argument("member was null");
      return Qnil;
    }
  }
}
