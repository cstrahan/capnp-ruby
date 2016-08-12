#include "ruby_capn_proto.h"
#include "remote_promise.h"
#include "dynamic_value_builder.h"
#include "dynamic_struct_builder.h"
#include "dynamic_struct_reader.h"
#include "EzRpc_client.h"
#include "interface_method.h"
#include "exception.h"
#include "class_builder.h"
#include <ruby/thread.h>
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::RemotePromise<capnp::DynamicStruct>;
  VALUE RemotePromise::Class;

  void RemotePromise::Init() {

    ClassBuilder("RemotePromise", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("request_and_send" , &request_and_send).
      defineMethod("wait" , &wait).
      store(&Class);
  }

  void RemotePromise::free(WrappedType* p) {
    p->~RemotePromise();
    ruby_xfree(p);
  }

  VALUE RemotePromise::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* RemotePromise::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE RemotePromise::create(WrappedType& remote_promise) {

    VALUE rb_obj = alloc(Class);
    WrappedType* rb_promise = unwrap(rb_obj);
    new (rb_promise) WrappedType(kj::mv(remote_promise));

    return rb_obj;
  }

  VALUE RemotePromise::request_and_send(VALUE self, VALUE name_struct, VALUE method, VALUE data){
    VALUE rb_client = rb_iv_get(self,"client");
    try{
      auto pipelinedClient = unwrap(self)->get(Util::toString(name_struct)).releaseAs<capnp::DynamicCapability>();
      auto request = pipelinedClient.newRequest(*InterfaceMethod::unwrap(method));
      setParam(&request,data);
      auto promise = request.send();
      VALUE new_remote_promise = create(promise);
      return new_remote_promise;
    }catch( kj::Exception t){
      Exception::raise(t);
    }
  }

  VALUE RemotePromise::wait(VALUE self, VALUE ezrpclient){
    VALUE client = ezrpclient;

    waitpacket p;
    p.prom = unwrap(self);
    p.client = EzRpcCapabilityClient::unwrap(client);
    p.response = NULL;

    // call waitIntern releasing the GIL
    rb_thread_call_without_gvl(waitIntern, &p, RUBY_UBF_IO , 0);
    return DynamicStructReader::create(*p.response,Qnil);
  }

  void * RemotePromise::waitIntern(void * p){
    try {
      waitpacket* pkt = (waitpacket*) p;
      auto& waitscope = pkt->client->getWaitScope();
      pkt->response = new capnp::Response<capnp::DynamicStruct>(pkt->prom->wait(waitscope));
    }catch(kj::Exception t){
      // adquire the lock to raise an exception on ruby
      rb_thread_call_with_gvl(&Exception::raise,&t);
    }
  }

  void RemotePromise::setParam(capnp::Request<capnp::DynamicStruct, capnp::DynamicStruct>* request, VALUE arys){
    VALUE mainIter = rb_ary_pop(arys); // mainIter is now a array
    while(mainIter != Qnil ){

      VALUE val = rb_ary_pop(mainIter);    // value to assign
      VALUE last = rb_ary_pop(mainIter);   // name of the field to assign to val
      VALUE temp = rb_ary_shift(mainIter); // just to iterate

      capnp::DynamicStruct::Builder builder = *request;

      // follow the nodes indicated by the array
      while( temp != Qnil && temp != last){
        try{
          builder = *DynamicStructBuilder::unwrap(DynamicValueBuilder::to_ruby(request->get(Util::toString(temp)),Qnil));
          temp = rb_ary_shift(mainIter);
        }catch(kj::Exception t){
          Exception::raise(t);
        }
      }

      // when arrived to last node make the assignation
      VALUE rb_struct = DynamicStructBuilder::create(builder,Qnil,Qfalse);
      DynamicStructBuilder::set(rb_struct,last,val);

      mainIter = rb_ary_pop(arys);
    }
  }

}
