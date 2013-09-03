#include "ruby_capn_proto.h"
#include "schema_node_reader.h"
#include "list_nested_node_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::schema::Node::Reader;
  VALUE SchemaNodeReader::Class;

  void SchemaNodeReader::Init() {
    ClassBuilder("SchemaNodeReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("nested_nodes", &get_nested_nodes).
      defineMethod("struct?", &is_struct).
      store(&Class);
  }

  VALUE SchemaNodeReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  VALUE SchemaNodeReader::create(WrappedType reader) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);
    return rb_obj;
  }

  void SchemaNodeReader::free(WrappedType* p) {
    p->~Reader();
    ruby_xfree(p);
  }

  WrappedType* SchemaNodeReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
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
