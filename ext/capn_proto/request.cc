#include "ruby_capn_proto.h"
#include "request.h"
#include "dynamic_struct_builder.h"
#include "dynamic_struct_reader.h"
#include "ezrpc_client.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::Request<capnp::DynamicStruct,capnp::DynamicStruct>;
  VALUE Request::Class;

  void Request::Init() {
    ClassBuilder("Request", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("send" , &send).
      defineMethod("builder", &builder).
      store(&Class);
  }

  void Request::free(WrappedType* p) {
    // todo fix
    ruby_xfree(p);
  }

  VALUE Request::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* Request::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE Request::create(WrappedType* request, VALUE client) {

    VALUE rb_obj = alloc(Class);
    WrappedType* rubyRequest = unwrap(rb_obj);
    rubyRequest = request;

    rb_iv_set(rb_obj, "client", client);

    return rb_obj;
  }

  VALUE Request::send(VALUE self){
    //to be optimized
    // unlock GIL here
    VALUE client;
    client = rb_iv_get(self,"client");
    capnp::Response<capnp::DynamicStruct> response = unwrap(self)->send().wait(EzrpcClient::unwrap(client)->getWaitScope());
    // lock GIL here
    return DynamicStructReader::create(response,Qnil);
  }

  // returns a DynamicStructBuilder to set up the arguments of the request.
  VALUE Request::builder(VALUE self){
    return DynamicStructBuilder::create(*unwrap(self),Qnil,Qnil);
  }

}
