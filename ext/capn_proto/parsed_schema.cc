#include "ruby_capn_proto.h"
#include "parsed_schema.h"
#include "schema_node_reader.h"
#include "struct_schema.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::ParsedSchema;
  VALUE ParsedSchema::Class;

  void ParsedSchema::Init() {
    ClassBuilder("ParsedSchema", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("get_proto", &get_proto).
      defineMethod("get_nested", &get_nested).
      defineMethod("as_struct", &as_struct).
      store(&Class);
  }

  void ParsedSchema::free(WrappedType* p) {
    p->~ParsedSchema();
    ruby_xfree(p);
  }

  VALUE ParsedSchema::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* ParsedSchema::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE ParsedSchema::create(WrappedType schema, VALUE parent) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_schema = unwrap(rb_obj);
    *wrapped_schema = kj::mv(schema);

    rb_iv_set(rb_obj, "parent", parent);

    return rb_obj;
  }

  VALUE ParsedSchema::get_proto(VALUE self) {
    return SchemaNodeReader::create(unwrap(self)->getProto(), self);
  }

  VALUE ParsedSchema::get_nested(VALUE self, VALUE rb_name) {
    auto name = Util::toString(rb_name);
    return create(unwrap(self)->getNested(name), self);
  }

  VALUE ParsedSchema::as_struct(VALUE self) {
    return StructSchema::create(unwrap(self)->asStruct(), self);
  }
}
