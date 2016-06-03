#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "dynamic_value_builder.h"
#include "dynamic_struct_builder.h"
#include "remote_promise.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::EzRpcClient;
  VALUE CapabilityClient::Class;

  void CapabilityClient::Init() {
    // this have to be an object
    ClassBuilder("CapabilityClient", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("schema", &get_schema).
      defineMethod("request_and_send" , &request_and_send).
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

    WrappedType* rb_self = unwrap(self);
    new (rb_self) capnp::EzRpcClient(Util::toString(dir));

    //store the InterfaceSchema
    rb_iv_set(self,"schema",interschema);

    return self;
  }

  VALUE CapabilityClient::get_schema(VALUE self){
    return rb_iv_get(self,"schema");
  }

  capnp::DynamicCapability::Client CapabilityClient::make_dynamic(VALUE self){
    VALUE rb_schema = rb_iv_get(self,"schema");

    capnp::Capability::Client capclient = unwrap(self)->getMain();
    return capclient.castAs<capnp::DynamicCapability>(*InterfaceSchema::unwrap(rb_schema));
  }

  VALUE CapabilityClient::request_and_send(VALUE self , VALUE rb_method , VALUE arrays){
    //have, a method and a list of lists each list containing a value to set
    //return, a remote promise.
    // Data must be a array of arrays
    // arrays must be like ['expression','literal','3']
    // this will set in the expression param literal = 3
    auto* method = InterfaceMethod::unwrap(rb_method);
    auto  request = make_dynamic(self).newRequest(*method);

    RemotePromise::setParam(&request,arrays);

    capnp::RemotePromise<capnp::DynamicStruct> r = request.send();
    return RemotePromise::create(r,self);
    //return Qfalse;
  }

}
