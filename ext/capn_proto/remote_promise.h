#ifndef REMOTE_PROMISE_H
#define REMOTE_PROMISE_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class RemotePromise {
  public:
    using WrappedType = capnp::RemotePromise<capnp::DynamicStruct>;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType& promise, VALUE client);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get(VALUE self, VALUE data);
    static VALUE request_and_send(VALUE self, VALUE method, VALUE data);
    static VALUE wait(VALUE self);
    static VALUE Class;
  };
}


#endif /* REMOTE_PROMISE_H */
