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
    static VALUE create(NodeList reader);
    static VALUE size(VALUE self);
    static VALUE get(VALUE self, VALUE index);

    static VALUE Class;
  };
}
