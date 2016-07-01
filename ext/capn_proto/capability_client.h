#ifndef CAPABILITY_CLIENT_H
#define CAPABILITY_CLIENT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class CapabilityClient {
  public:
    using WrappedType = capnp::Capability::Client;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType native_client);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE to_dynamic(VALUE self, VALUE schema);
    static VALUE Class;
  };
}


#endif /* CAPABILITY_CLIENT_H */
