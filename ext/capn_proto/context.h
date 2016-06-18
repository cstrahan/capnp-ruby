#ifndef CONTEXT_H
#define CONTEXT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Context {
  public:
    using WrappedType = capnp::CallContext;
    static void create(WrappedType context);
    static WrappedType* unwrap(VALUE self);
    static VALUE getParams();
    static VALUE releaseParams();
    static VALUE getResults();
    static VALUE initResults();
    static VALUE setResults(VALUE structBuilder);

    static VALUE Class;
  };
}

#endif /* CONTEXT_H */
