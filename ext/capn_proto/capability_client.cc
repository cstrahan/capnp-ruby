#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "interface_schema.h"
#include "interface_method.h"
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

  VALUE CapabilityClient::create(VALUE dir, VALUE interschema) {
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

    return rb_obj; // returns a object of CapabilityClient containing a DynamicCapability::client
  }

  VALUE CapabilityClient::newRequest(VALUE self, VALUE method){
    // todo
    auto request = unwrap(self)->newRequest(*InterfaceMethod::unwrap(method));
    return Request::create(request);
  }

}
