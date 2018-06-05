#include "ruby_capn_proto.h"
#include "message_reader.h"
#include "packed_array_message_reader.h"
#include "struct_schema.h"
#include "dynamic_struct_reader.h"
#include "class_builder.h"
#include "exception.h"
#include <string>

namespace ruby_capn_proto {
  using WrappedType = capnp::PackedMessageReader;
  VALUE PackedArrayMessageReader::Class;

  void PackedArrayMessageReader::Init()
  {
    ClassBuilder("PackedArrayMessageReader", MessageReader::Class).defineAlloc(&alloc).defineMethod("initialize", &initialize).defineMethod("get_root", &get_root).store(&Class);
  }

  VALUE PackedArrayMessageReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  VALUE PackedArrayMessageReader::initialize(VALUE self, VALUE rb_buff) {
    rb_iv_set(self, "buff", rb_buff);
    auto str = RSTRING_PTR(rb_buff);
    auto len = RSTRING_LEN(rb_buff);
    kj::ArrayPtr<unsigned char> bufferPtr = kj::arrayPtr((unsigned char *)str, len);
    kj::ArrayInputStream stream(bufferPtr);

    try {
      WrappedType* p = unwrap(self);
      new (p) WrappedType(stream);
    } catch (kj::Exception ex) {
      return Exception::raise(ex);
    }

    return Qnil;
  }

  void PackedArrayMessageReader::free(WrappedType* p) {
    p->~PackedMessageReader();
    ruby_xfree(p);
  }

  WrappedType* PackedArrayMessageReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE PackedArrayMessageReader::get_root(VALUE self, VALUE rb_schema) {
    if (rb_respond_to(rb_schema, rb_intern("schema"))) {
      rb_schema = rb_funcall(rb_schema, rb_intern("schema"), 0);
    }

    auto schema = *StructSchema::unwrap(rb_schema);
    auto reader = unwrap(self)->getRoot<capnp::DynamicStruct>(schema);
    return DynamicStructReader::create(reader, self);
  }
}
