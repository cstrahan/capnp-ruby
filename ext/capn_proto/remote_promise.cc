#include "ruby_capn_proto.h"
#include "remote_promise.h"
#include "dynamic_value_builder.h"
#include "dynamic_struct_builder.h"
#include "dynamic_struct_reader.h"
#include "capability_client.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::RemotePromise<capnp::DynamicStruct>;
  VALUE RemotePromise::Class;

  void RemotePromise::Init() {
    // this have to be an object
    ClassBuilder("RemotePromise", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("request_and_send" , &request_and_send).
      defineMethod("[]" , &get).
      defineMethod("wait" , &wait).
      store(&Class);
  }

  void RemotePromise::free(WrappedType* p) {
    // todo fix
    printf("Free has been called\n" );
  }

  VALUE RemotePromise::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* RemotePromise::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE RemotePromise::create(WrappedType& remote_promise, VALUE client) {

    VALUE rb_obj = alloc(Class);
    WrappedType* rb_promise = unwrap(rb_obj);
    new (rb_promise) WrappedType(kj::mv(remote_promise));


    //store the client
    rb_iv_set(rb_obj,"client",client);
    return rb_obj;
  }

  VALUE RemotePromise::request_and_send(VALUE self, VALUE method, VALUE data){
    //to do
    return Qfalse;
  }

  VALUE RemotePromise::get(VALUE self, VALUE data){
    //to do
    return Qfalse;
  }

  VALUE RemotePromise::wait(VALUE self){
    VALUE client = rb_iv_get(self,"client");
    auto& waitscope = CapabilityClient::unwrap(client)->getWaitScope();
    capnp::DynamicStruct::Reader reader = unwrap(self)->wait(waitscope);
    return DynamicStructReader::create(reader,Qnil);
  }

}
