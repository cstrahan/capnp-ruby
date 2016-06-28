#ifndef CAPABILITY_SERVER_H
#define CAPABILITY_SERVER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {

  typedef struct _loopCall{
    kj::WaitScope* waitscope;
    kj::PromiseFulfillerPair<void>* promisepair;
  } loopCall;

  class CapabilityServer {
  public:
    using WrappedType = capnp::EzRpcServer;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE self, VALUE rb_server, VALUE schema , VALUE dir);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE process(VALUE self);
    static void * loopServer(void* p);
    static void stopLoopServer(void* p);
    static VALUE Class;
  };
}


#endif /* CAPABILITY_SERVER_H */
