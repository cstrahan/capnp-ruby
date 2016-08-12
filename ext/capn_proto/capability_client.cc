#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "dynamic_capability_client.h"
#include "exception.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::Capability::Client;
  VALUE CapabilityClient::Class;

  void CapabilityClient::Init() {
    ClassBuilder("CapabilityClient", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("to_dynamic" , &to_dynamic).
      store(&Class);
  }

  void CapabilityClient::free(WrappedType* p) {
    p->~Client();
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

  VALUE CapabilityClient::create(WrappedType native_client ) {

    VALUE self = alloc(Class);
    WrappedType* rb_self = unwrap(self);
    new (rb_self) capnp::Capability::Client(native_client);

    return self;
  }

  VALUE CapabilityClient::to_dynamic(VALUE self, VALUE schema){
    return DynamicCapabilityClient::create(self,schema);
  }

}
