#ifndef CONTEXT_H
#define CONTEXT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class CallContext {
  public:
    using WrappedType = capnp::CallContext<capnp::DynamicStruct, capnp::DynamicStruct>;
    static void create(WrappedType context);
    static WrappedType* unwrap(VALUE self);
    static VALUE getParams(VALUE self);
    static VALUE releaseParams(VALUE self);
    static VALUE getResults(VALUE self);
    static VALUE initResults(VALUE self);
    static VALUE setResults(VALUE self, VALUE structBuilder);

    static VALUE Class;
  };
}

#endif /* CONTEXT_H */
