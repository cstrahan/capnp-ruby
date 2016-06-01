#include "ruby_capn_proto.h"
#include "static_capability_client.h"
#include "class_builder.h"
#include "util.h"


namespace ruby_capn_proto {
  using WrappedType = capnp::Capability::Client;
  VALUE StaticCapabilityClient::Class;

  void StaticCapabilityClient::Init() {
    ClassBuilder("StaticCapabilityClient", rb_cObject).
      defineAlloc(&alloc).
      store(&Class);
  }

  void StaticCapabilityClient::free(WrappedType* p) {
    //todo fix
    ruby_xfree(p);
  }

  VALUE StaticCapabilityClient::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* StaticCapabilityClient::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE StaticCapabilityClient::create(WrappedType* client) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_client = unwrap(rb_obj);
    *wrapped_client = kj::mv(*client);

    return rb_obj;
  }

}
