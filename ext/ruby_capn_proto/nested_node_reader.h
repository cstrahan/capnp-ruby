#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class NestedNodeReader {
  public:
    using WrappedType = capnp::schema::Node::NestedNode::Reader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE name(VALUE self);

    static VALUE Class;
  };
}
