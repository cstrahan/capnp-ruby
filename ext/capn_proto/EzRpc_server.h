#ifndef EZRPC_CAPABILITY_SERVER_H
#define EZRPC_CAPABILITY_SERVER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {

  typedef struct _loopCall{
    kj::WaitScope* waitscope;
    kj::PromiseFulfillerPair<void>* promisepair;
  } loopCall;

  class EzRpcCapabilityServer {
  public:
    using WrappedType = capnp::EzRpcServer;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE self, VALUE rb_server, VALUE dir);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE process(VALUE self);
    static void * loopServer(void* p);
    static void stopLoopServer(void* p);
    // schema and rb_server to make new RubyCapabilityServer on the fly
    static capnp::InterfaceSchema* schema(VALUE self);
    static VALUE rb_server(VALUE self);
    static VALUE Class;
  };
}


#endif /* EZRPC_CAPABILITY_SERVER_H */
