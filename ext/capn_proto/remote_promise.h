#ifndef REMOTE_PROMISE_H
#define REMOTE_PROMISE_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  typedef struct _waitpacket {
    capnp::EzRpcClient* client;
    capnp::RemotePromise<capnp::DynamicStruct>* prom;
    capnp::Response<capnp::DynamicStruct>* response;
  } waitpacket;

  class RemotePromise {
  public:
    using WrappedType = capnp::RemotePromise<capnp::DynamicStruct>;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType& promise, VALUE client);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE request_and_send(VALUE self, VALUE struct_name, VALUE method, VALUE data);
    static void setParam(capnp::Request<capnp::DynamicStruct, capnp::DynamicStruct>* request, VALUE arrays);
    static VALUE wait(VALUE self);
    static void * waitIntern(void * p);
    static VALUE Class;
  };
}


#endif /* REMOTE_PROMISE_H */
