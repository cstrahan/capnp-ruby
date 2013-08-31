#include "ruby_capn_proto.h"
#include "schema.h"
#include "schema_node_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  VALUE Schema::Class;

  void Schema::free(capnp::ParsedSchema* p) {
    p->~ParsedSchema();
    ruby_xfree(p);
  }

  VALUE Schema::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(capnp::ParsedSchema)));
  }

  capnp::ParsedSchema* Schema::unwrap(VALUE self) {
    capnp::ParsedSchema* p;
    Data_Get_Struct(self, capnp::ParsedSchema, p);
    return p;
  }

  VALUE Schema::create(capnp::ParsedSchema schema) {
    VALUE rb_schema = alloc(Class);
    capnp::ParsedSchema* wrapped_schema = unwrap(rb_schema);
    *wrapped_schema = kj::mv(schema);
    return rb_schema;
  }

  VALUE Schema::get_proto(VALUE self) {
    return SchemaNodeReader::create(Schema::unwrap(self)->getProto());
  }

  void Schema::Init() {
    ClassBuilder("Schema", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("get_proto", &get_proto).
      store(&Class);
  }
}
