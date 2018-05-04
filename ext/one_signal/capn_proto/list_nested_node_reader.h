#ifndef LIST_NESTED_NODE_READER_H
#define LIST_NESTED_NODE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class ListNestedNodeReader {
  public:
    using NodeList = ::capnp::List< ::capnp::schema::Node::NestedNode>::Reader;

    static void Init();
    static VALUE initialize(VALUE klass);
    static VALUE alloc(VALUE klass);
    static void free(NodeList* p);
    static NodeList* unwrap(VALUE self);
    static VALUE create(NodeList reader, VALUE parent);
    static VALUE size(VALUE self);
    static VALUE get(VALUE self, VALUE index);

    static VALUE Class;
  };
}

#endif /* LIST_NESTED_NODE_READER_H */
