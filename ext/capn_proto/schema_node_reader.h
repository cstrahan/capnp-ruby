#ifndef SCHEMA_NODE_READER_H
#define SCHEMA_NODE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class SchemaNodeReader {
  public:
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(capnp::schema::Node::Reader reader, VALUE parent);
    static void free(capnp::schema::Node::Reader* p);
    static capnp::schema::Node::Reader* unwrap(VALUE self);
    static VALUE get_nested_nodes(VALUE self);
    static VALUE is_struct(VALUE self);
    static VALUE is_enum(VALUE self);
    static VALUE is_interface(VALUE self);

    static VALUE Class;
  };
}

#endif /* SCHEMA_NODE_READER_H */
