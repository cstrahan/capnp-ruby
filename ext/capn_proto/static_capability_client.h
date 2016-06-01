#ifndef STATIC_CAPABILITY_CLIENT_H
#define STATIC_CAPABILITY_CLIENT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class StaticCapabilityClient {
  public:
    using WrappedType = capnp::Capability::Client;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType* client);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE Class;
  };
}


#endif /* STATIC_CAPABILITY_CLIENT_H */
