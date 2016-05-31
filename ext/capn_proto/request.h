#ifndef REQUEST_H
#define REQUEST_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Request {
  public:
    using WrappedType = capnp::Request<capnp::DynamicStruct, capnp::DynamicStruct>;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType* r, VALUE client);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE send(VALUE self);
    static VALUE builder(VALUE self);
    static VALUE Class;
  };
}


#endif /* REQUEST_H */
