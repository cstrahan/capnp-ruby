#include "ruby_capn_proto.h"
#include "EzRpc_client.h"
#include "capability_client.h"
#include "dynamic_capability_client.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::EzRpcClient;
  VALUE EzRpcCapabilityClient::Class;

  void EzRpcCapabilityClient::Init() {
    ClassBuilder("EzRpcClient", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("client", &make_dynamic).
      defineMethod("initialize" , &create).
      store(&Class);
  }

  void EzRpcCapabilityClient::free(WrappedType* p) {
    ruby_xfree(p);
  }

  VALUE EzRpcCapabilityClient::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* EzRpcCapabilityClient::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE EzRpcCapabilityClient::create(VALUE self, VALUE dir, VALUE interschema) {

    WrappedType* rb_self = unwrap(self);
    new (rb_self) capnp::EzRpcClient(Util::toString(dir));

    //store the InterfaceSchema
    rb_iv_set(self,"schema",interschema);

    return self;
  }

  VALUE EzRpcCapabilityClient::make_dynamic(VALUE self){
    VALUE rb_schema = rb_iv_get(self,"schema");
    VALUE rb_cap = CapabilityClient::create(unwrap(self)->getMain());
    return DynamicCapabilityClient::create(rb_cap,rb_schema);
  }

}
