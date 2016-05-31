#ifndef ezrpc_client_H
#define ezrpc_client_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  // this class is only for communication between CapabilityClient and Request.
  // you don't need to use this.
  class EzrpcClient {
  public:
    using WrappedType = capnp::EzRpcClient;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType* client);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE Class;
  };
}


#endif /* ezrpc_client_H */
