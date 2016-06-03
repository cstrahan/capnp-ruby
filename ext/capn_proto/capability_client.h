#ifndef CAPABILITY_CLIENT_H
#define CAPABILITY_CLIENT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class CapabilityClient {
  public:
    using WrappedType = capnp::EzRpcClient;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE self, VALUE dir, VALUE schema);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static capnp::DynamicCapability::Client make_dynamic(VALUE self);
    static VALUE get_schema(VALUE self);
    static VALUE request_and_send(VALUE self, VALUE method, VALUE data);
    static VALUE Class;
  };
}


#endif /* CAPABILITY_CLIENT_H */
