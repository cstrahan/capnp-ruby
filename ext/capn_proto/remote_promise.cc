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
    // having some problems pipelining request because i can't get the 'client'
    // of the RemotePromise.
    //auto new_request = unwrap(self)->newRequest(*unwrap(method));
    //setParam(&new_request,data);
    //create(new_request.send());
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

  void RemotePromise::setParam(capnp::Request<capnp::DynamicStruct, capnp::DynamicStruct>* request, VALUE arys){
    VALUE mainIter = rb_ary_pop(arys); // mainIter is now a array
    while(mainIter != Qnil ){

      VALUE val = rb_ary_pop(mainIter);    // value to assign
      VALUE last = rb_ary_pop(mainIter);   // name of the field to assign to val
      VALUE temp = rb_ary_shift(mainIter); // just a to iterate

      capnp::DynamicStruct::Builder builder = NULL;

      // follow the nodes indicated by the array
      while( temp != Qnil && temp != last){
        builder = *DynamicStructBuilder::unwrap(DynamicValueBuilder::to_ruby(request->get(Util::toString(temp)),Qnil));
        temp = rb_ary_shift(mainIter);
      }

      // when arrived to last node make the assignation
      VALUE rb_struct = DynamicStructBuilder::create(builder,Qnil,Qfalse);
      DynamicStructBuilder::set(rb_struct,last,val);

      mainIter = rb_ary_pop(arys);
    }
  }

}
