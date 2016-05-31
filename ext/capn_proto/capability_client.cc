#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "ezrpc_client.h"
#include "request.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicCapability::Client;
  VALUE CapabilityClient::Class;

  void CapabilityClient::Init() {
    // this have to be an object
    ClassBuilder("CapabilityClient", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("newRequest" , &newRequest).
      defineMethod("initialize" , &create).
      store(&Class);
  }

  void CapabilityClient::free(WrappedType* p) {
    // todo fix
    //p->~CapabilityClient();
    ruby_xfree(p);
  }

  VALUE CapabilityClient::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* CapabilityClient::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE CapabilityClient::create(VALUE self, VALUE dir, VALUE interschema) {
    // todo check if dir is a ruby string

    // we need that InterfaceSchema
    capnp::InterfaceSchema* capnInterfaceSchema = InterfaceSchema::unwrap(interschema);

    // use it to create a DynamicCapability using ezrpc
    capnp::EzRpcClient client(Util::toString(dir));
    capnp::Capability::Client capclient = client.getMain();
    capnp::DynamicCapability::Client dynclient = capclient.castAs<capnp::DynamicCapability>(*capnInterfaceSchema);

    // store it in ruby
    VALUE rb_obj = alloc(Class);
    WrappedType* rubycapclient = unwrap(rb_obj);
    *rubycapclient = dynclient;

    //store the client
    VALUE rb_client = EzrpcClient::create(&client);
    rb_iv_set(rb_obj,"client",rb_client);

    return rb_obj; // returns a object of CapabilityClient containing a DynamicCapability::client
  }

  VALUE CapabilityClient::newRequest(VALUE self, VALUE method){
    // todo
    // get the stored client
    VALUE rb_client = rb_iv_get(self,"client");
    capnp::Request<capnp::DynamicStruct, capnp::DynamicStruct> dorequest = unwrap(self)->newRequest(*InterfaceMethod::unwrap(method));
    return Request::create(&dorequest, rb_client);
  }

}
