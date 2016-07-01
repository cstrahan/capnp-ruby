#ifndef DYNAMIC_CAPABILITY_CLIENT_H
#define DYNAMIC_CAPABILITY_CLIENT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicCapabilityClient {
  public:
    using WrappedType = capnp::DynamicCapability::Client;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE capclient, VALUE schema);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get_schema(VALUE self);
    static VALUE request_and_send(VALUE self, VALUE method, VALUE data);
    static VALUE Class;
  };
}


#endif /* DYNAMIC_CAPABILITY_CLIENT_H */
