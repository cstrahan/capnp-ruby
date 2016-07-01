#ifndef EZRPC_CAPABILITY_CLIENT_H
#define EXRPC_CAPABILITY_CLIENT_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class EzRpcCapabilityClient {
  public:
    using WrappedType = capnp::EzRpcClient;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE self, VALUE dir, VALUE schema);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE make_dynamic(VALUE self);
    static VALUE Class;
  };
}


#endif /* EZRPC_CAPABILITY_CLIENT_H */
