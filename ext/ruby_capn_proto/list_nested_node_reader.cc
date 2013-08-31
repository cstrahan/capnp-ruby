#include "ruby_capn_proto.h"
#include "list_nested_node_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using NodeList = ::capnp::List< ::capnp::schema::Node::NestedNode>::Reader;

  VALUE ListNestedNodeReader::Class;

  void ListNestedNodeReader::Init() {
    ClassBuilder("ListNestedNodeReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("size", &size).
      store(&Class);
  }

  void ListNestedNodeReader::free(NodeList* p) {
    p->~NodeList();
    ruby_xfree(p);
  }

  VALUE ListNestedNodeReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(NodeList)));
  }

  NodeList* ListNestedNodeReader::unwrap(VALUE self) {
    NodeList* p;
    Data_Get_Struct(self, NodeList, p);
    return p;
  }

  VALUE ListNestedNodeReader::create(NodeList schema) {
    VALUE rb_schema = alloc(Class);
    NodeList* wrapped_schema = unwrap(rb_schema);
    *wrapped_schema = kj::mv(schema);
    return rb_schema;
  }

  VALUE ListNestedNodeReader::size(VALUE self) {
    return INT2FIX(unwrap(self)->size());
  }
}
