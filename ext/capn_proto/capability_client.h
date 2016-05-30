#ifndef CAPABILITY_CLIENT_H
#define CAPABILITY_CLIENT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class CapabilityClient {
  public:
    using WrappedType = capnp::DynamicCapability::Client;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE dir, VALUE schema);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE newRequest(VALUE self, VALUE method);
    static VALUE Class;
  };
}


#endif /* CAPABILITY_CLIENT_H */
