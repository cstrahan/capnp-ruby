#include "ruby_capn_proto.h"
#include "message_reader.h"
#include "flat_array_message_reader.h"
#include "struct_schema.h"
#include "dynamic_struct_reader.h"
#include "class_builder.h"
#include "exception.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::FlatArrayMessageReader;
  VALUE FlatArrayMessageReader::Class;

  void FlatArrayMessageReader::Init() {
    ClassBuilder("FlatArrayMessageReader", MessageReader::Class).
      defineAlloc(&alloc).
      defineMethod("initialize", &initialize).
      defineMethod("get_root", &get_root).
      store(&Class);
  }

  VALUE FlatArrayMessageReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  VALUE FlatArrayMessageReader::initialize(VALUE self, VALUE rb_buff) {
    rb_iv_set(self, "buff", rb_buff);
    auto str = RSTRING_PTR(rb_buff);
    auto len = RSTRING_LEN(rb_buff);
    kj::ArrayPtr<const capnp::word> buff((const capnp::word*)str, len/sizeof(capnp::word));

    try {
      WrappedType* p = unwrap(self);
      new (p) WrappedType(buff);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }

    return Qnil;
  }

  void FlatArrayMessageReader::free(WrappedType* p) {
    p->~FlatArrayMessageReader();
    ruby_xfree(p);
  }

  WrappedType* FlatArrayMessageReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE FlatArrayMessageReader::get_root(VALUE self, VALUE rb_schema) {
    if (rb_respond_to(rb_schema, rb_intern("schema"))) {
      rb_schema = rb_funcall(rb_schema, rb_intern("schema"), 0);
    }

    auto schema = *StructSchema::unwrap(rb_schema);
    auto reader = unwrap(self)->getRoot<capnp::DynamicStruct>(schema);
    return DynamicStructReader::create(reader, self);
  }
}
