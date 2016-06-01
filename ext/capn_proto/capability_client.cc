#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "static_capability_client.h"
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
    printf("Free has been called\n" );
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
    //having serious problems here
    // both Ezrpc client and StaticCapabilityClient may not be needed and deleted
    // in the future.
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
    *rubycapclient = kj::mv(dynclient); // segfault
    //VALUE rb_obj = Data_Wrap_Struct(Class,NULL,free,&dynclient);

    //store the client
    //VALUE rb_client = EzrpcClient::create(&client);
    //rb_iv_set(rb_obj,"client",rb_client);
    //store the capabilit::client
    VALUE rb_capability_client = StaticCapabilityClient::create(&capclient);
    rb_iv_set(rb_obj,"capclient",rb_capability_client);
    //unwrap(rb_obj)->getSchema().getProto(); things like this works here
    //return rb_client; // returns a object of CapabilityClient containing a DynamicCapability::client
    return rb_obj;
  }

  VALUE CapabilityClient::newRequest(VALUE self , VALUE method){
    // todo
    // get the stored client
    capnp::InterfaceSchema::Method* unwraped_method = InterfaceMethod::unwrap(method);
    capnp::DynamicCapability::Client* client = unwrap(self);
    //client->getSchema().getProto();
    //unwrap(self)->getSchema().getProto(); but not work here
    //auto dorequest = unwrap(self)->newRequest("evaluate");
    VALUE rb_client = rb_iv_get(self,"client");
    //return Request::create(&dorequest, rb_client);
    return Qfalse;
  }

}
