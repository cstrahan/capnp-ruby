#include "ruby_capn_proto.h"
#include "dynamic_list_builder.h"
#include "dynamic_value_builder.h"
#include "dynamic_struct_reader.h"
#include "dynamic_struct_builder.h"
#include "exception.h"
#include "util.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicList::Builder;
  VALUE DynamicListBuilder::Class;

  void DynamicListBuilder::Init() {
    ClassBuilder("DynamicListBuilder", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("[]", &get).
      defineMethod("[]=", &set).
      defineMethod("size", &size).
      store(&Class);
  }

  VALUE DynamicListBuilder::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  void DynamicListBuilder::free(WrappedType* p) {
    p->~Builder();
    ruby_xfree(p);
  }

  WrappedType* DynamicListBuilder::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicListBuilder::create(WrappedType builder, VALUE parent) {
    auto rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(builder);

    rb_iv_set(rb_obj, "parent", parent);

    return rb_obj;
  }

  VALUE DynamicListBuilder::size(VALUE self) {
    return INT2FIX(unwrap(self)->size());
  }

  VALUE DynamicListBuilder::get(VALUE self, VALUE rb_index) {
    try {
      return _get(self, rb_index);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicListBuilder::_get(VALUE self, VALUE rb_index) {
    auto builder = *unwrap(self);
    auto size = builder.size();

    unsigned long index;
    if (Util::isNegative(rb_index)) {
      index = NUM2LONG(rb_index) % builder.size();
    } else {
      index = NUM2ULONG(rb_index);
    }

    // return DynamicValueBuilder::to_ruby(builder.get(field), self);
    return DynamicValueBuilder::to_ruby(builder[index], self);
  }

  VALUE DynamicListBuilder::set(VALUE self, VALUE rb_index, VALUE rb_obj) {
    try {
      return _set(self, rb_index, rb_obj);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }
  }

  VALUE DynamicListBuilder::_set(VALUE self, VALUE rb_index, VALUE rb_obj) {
    VALUE klass = rb_funcall(rb_obj, rb_intern("class"), 0);

    unsigned long field;
    if (Util::isNegative(rb_index)) {
      field = NUM2LONG(rb_index) % unwrap(self)->size();
    } else {
      field = NUM2ULONG(rb_index);
    }

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
}
