#include "ruby_capn_proto.h"
#include "EzRpc_server.h"
#include "ruby_capability_server.h"
#include "interface_schema.h"
#include "exception.h"
#include "class_builder.h"
#include <ruby/thread.h>
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::EzRpcServer;
  VALUE EzRpcCapabilityServer::Class;

  void EzRpcCapabilityServer::Init() {
    ClassBuilder("EzRpcServer", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("run" , &process).
      defineMethod("initialize" , &create).
      store(&Class);
  }

  void EzRpcCapabilityServer::free(WrappedType* p) {
    ruby_xfree(p);
  }

  VALUE EzRpcCapabilityServer::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* EzRpcCapabilityServer::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE EzRpcCapabilityServer::create(VALUE self, VALUE rb_capServer, VALUE dir) {

    VALUE interschema = rb_iv_get(rb_capServer,"@schema");
    auto schema = InterfaceSchema::unwrap(interschema);

    WrappedType* rb_self = unwrap(self);
    new (rb_self) capnp::EzRpcServer( kj::heap<capnp::RubyCapabilityServer>(*schema, rb_capServer) , Util::toString(dir) );

    return self;
  }

  VALUE EzRpcCapabilityServer::process(VALUE self){
    try{
      loopCall l;
      auto server = unwrap(self);
      auto to_fulfill = kj::heap<kj::PromiseFulfillerPair<void>>(kj::newPromiseAndFulfiller<void>());
      l.waitscope = &server->getWaitScope();
      l.promisepair = to_fulfill.get();
      rb_thread_call_without_gvl(loopServer, &l, stopLoopServer , l.promisepair);
    }catch ( kj::Exception t ){
      Exception::raise(t);
    }
    return Qtrue;
  }

  void * EzRpcCapabilityServer::loopServer(void * p){
    try {
      auto* loopcall = (loopCall*) p;
      loopcall->promisepair->promise.wait(*(loopcall->waitscope));
    }catch( kj::Exception t ){
      //adquire the lock to raise a ruby exception
      rb_thread_call_with_gvl(&Exception::raise,&t);
    }
  }

  void EzRpcCapabilityServer::stopLoopServer(void *p){
    try {
      auto* promisefulfiller = (kj::PromiseFulfillerPair<void>*) p;
      promisefulfiller->fulfiller->fulfill();
    }catch( kj::Exception t ){
      Exception::raise(t);
    }
  }
}
