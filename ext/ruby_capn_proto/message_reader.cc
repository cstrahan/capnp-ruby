#include "ruby_capn_proto.h"
#include "message_reader.h"
#include "class_builder.h"
#include "struct_schema.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::MessageReader;
  VALUE MessageReader::Class;

  void MessageReader::Init() {
    ClassBuilder("MessageReader", rb_cObject).
      defineMethod("get_root", &get_root).
      store(&Class);
  }

  WrappedType* MessageReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, capnp::MessageReader, p);
    return p;
  }

  VALUE MessageReader::get_root(VALUE self, VALUE rb_schema) {
    auto schema = *StructSchema::unwrap(rb_schema);
    auto reader = unwrap(self)->getRoot<capnp::DynamicStruct>(schema);
    // return DynamicStructReader::create(schema, reader);
    return Qnil;
  }
}
