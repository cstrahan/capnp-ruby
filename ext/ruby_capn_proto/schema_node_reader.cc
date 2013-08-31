#include "ruby_capn_proto.h"
#include "schema_node_reader.h"
#include "list_nested_node_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  VALUE SchemaNodeReader::Class;

  void SchemaNodeReader::Init() {
    ClassBuilder("SchemaNodeReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("nested_nodes", &get_nested_nodes).
      defineMethod("struct?", &is_struct).
      store(&Class);
  }

  VALUE SchemaNodeReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(capnp::schema::Node::Reader)));
  }

  VALUE SchemaNodeReader::create(capnp::schema::Node::Reader reader) {
    VALUE rb_obj = alloc(Class);
    capnp::schema::Node::Reader* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);
    return rb_obj;
  }

  void SchemaNodeReader::free(capnp::schema::Node::Reader* p) {
    p->~Reader();
    ruby_xfree(p);
  }

  capnp::schema::Node::Reader* SchemaNodeReader::unwrap(VALUE self) {
    capnp::schema::Node::Reader* p;
    Data_Get_Struct(self, capnp::schema::Node::Reader, p);
    return p;
  }

  VALUE SchemaNodeReader::get_nested_nodes(VALUE self) {
    return ListNestedNodeReader::create(unwrap(self)->getNestedNodes());
  }

  VALUE SchemaNodeReader::is_struct(VALUE self) {
    return unwrap(self)->isStruct() ? Qtrue : Qfalse;
  }

  VALUE SchemaNodeReader::is_enum(VALUE self) {
    return unwrap(self)->isEnum() ? Qtrue : Qfalse;
  }
}
