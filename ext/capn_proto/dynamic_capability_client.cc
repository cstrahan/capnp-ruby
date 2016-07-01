#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "dynamic_capability_client.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "dynamic_value_builder.h"
#include "dynamic_struct_builder.h"
#include "remote_promise.h"
#include "exception.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicCapability::Client;
  VALUE DynamicCapabilityClient::Class;

  void DynamicCapabilityClient::Init() {
    ClassBuilder("DynamicCapabilityClient", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("request_and_send" , &request_and_send).
      defineMethod("schema", &get_schema).
      store(&Class);
  }

  void DynamicCapabilityClient::free(WrappedType* p) {
    p->~Client(); 
    ruby_xfree(p);
  }

  VALUE DynamicCapabilityClient::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* DynamicCapabilityClient::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicCapabilityClient::create(VALUE client, VALUE interschema) {

    VALUE self = alloc(Class);
    WrappedType* rb_self = unwrap(self);
    auto dyncap = CapabilityClient::unwrap(client)->castAs<capnp::DynamicCapability>(*InterfaceSchema::unwrap(interschema));
    new (rb_self) capnp::DynamicCapability::Client(dyncap);

    rb_iv_set(self, "schema", interschema);

    return self;
  }

  VALUE DynamicCapabilityClient::request_and_send(VALUE self , VALUE rb_method , VALUE arrays){
    // have, a method and a list of lists each list containing a value to set
    // return, a remote promise.
    // Data must be a array of arrays
    // arrays must be like ['expression','literal','3']
    // this will set in the expression param literal = 3
    try{
      auto* method = InterfaceMethod::unwrap(rb_method);
      auto  request = unwrap(self)->newRequest(*method);

      RemotePromise::setParam(&request,arrays);

      capnp::RemotePromise<capnp::DynamicStruct> r = request.send();
      return RemotePromise::create(r);
    }catch(kj::Exception e){
      Exception::raise(e);
    }
  }

  VALUE DynamicCapabilityClient::get_schema(VALUE self){
    return rb_iv_get(self,"schema");
  }

}
