#include "ruby_capn_proto.h"
#include "schema.h"
#include "schema_node_reader.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  VALUE Schema::Class;

  void Schema::Init() {
    ClassBuilder("Schema", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("get_proto", &get_proto).
      defineMethod("get_nested", &get_nested).
      // defineMethod("as_struct", &as_struct).
      store(&Class);
  }

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

  VALUE Schema::create(VALUE parent, capnp::ParsedSchema schema) {
    VALUE rb_schema = alloc(Class);
    capnp::ParsedSchema* wrapped_schema = unwrap(rb_schema);
    *wrapped_schema = kj::mv(schema);

    rb_iv_set(rb_schema, "parent", parent);

    return rb_schema;
  }

  VALUE Schema::get_proto(VALUE self) {
    return SchemaNodeReader::create(unwrap(self)->getProto());
  }

  VALUE Schema::get_nested(VALUE self, VALUE rb_name) {
    auto name = Util::toString(rb_name);
    return create(self, unwrap(self)->getNested(name));
  }
}
