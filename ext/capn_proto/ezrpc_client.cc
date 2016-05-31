#include "ruby_capn_proto.h"
#include "ezrpc_client.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::EzRpcClient;
  VALUE EzrpcClient::Class;

  void EzrpcClient::Init() {
    ClassBuilder("EzrpcClient", rb_cObject).
      defineAlloc(&alloc).
      store(&Class);
  }

  void EzrpcClient::free(WrappedType* p) {
    // todo fix
    ruby_xfree(p);
  }

  VALUE EzrpcClient::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* EzrpcClient::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE EzrpcClient::create(WrappedType* client) {

    VALUE rb_obj = alloc(Class);
    WrappedType* rubyezrpcClient = unwrap(rb_obj);
    rubyezrpcClient = client;

    return rb_obj;
  }

}
