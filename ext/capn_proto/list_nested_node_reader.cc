#include "ruby_capn_proto.h"
#include "list_nested_node_reader.h"
#include "nested_node_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using NodeList = ::capnp::List< ::capnp::schema::Node::NestedNode>::Reader;

  VALUE ListNestedNodeReader::Class;

  void ListNestedNodeReader::Init() {
    ClassBuilder("ListNestedNodeReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("size", &size).
      defineMethod("[]", &get).
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

  VALUE ListNestedNodeReader::create(NodeList schema, VALUE parent) {
    VALUE rb_obj = alloc(Class);
    NodeList* wrapped_schema = unwrap(rb_obj);
    *wrapped_schema = kj::mv(schema);

    rb_iv_set(rb_obj, "parent", parent);

    return rb_obj;
  }

  VALUE ListNestedNodeReader::size(VALUE self) {
    return INT2FIX(unwrap(self)->size());
  }

  VALUE ListNestedNodeReader::get(VALUE self, VALUE index) {
    auto idx = FIX2INT(index);
    auto list = *unwrap(self);
    return NestedNodeReader::create(list[idx]);
  }
}
