#include "ruby_capn_proto.h"
#include "capability_server.h"
#include "ruby_capability_server.h"
#include "interface_schema.h"
#include "exception.h"
#include "class_builder.h"
#include <ruby/thread.h>
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::EzRpcServer;
  VALUE CapabilityServer::Class;

  void CapabilityServer::Init() {
    ClassBuilder("CapabilityServer", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("run" , &process).
      defineMethod("initialize" , &create).
      store(&Class);
  }

  void CapabilityServer::free(WrappedType* p) {
    ruby_xfree(p);
  }

  VALUE CapabilityServer::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* CapabilityServer::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE CapabilityServer::create(VALUE self, VALUE rb_server, VALUE interschema, VALUE dir) {

    auto schema = InterfaceSchema::unwrap(interschema);

    WrappedType* rb_self = unwrap(self);
    new (rb_self) capnp::EzRpcServer( kj::heap<capnp::RubyCapabilityServer>(*schema, rb_server) , Util::toString(dir) );
    //TODO if the capserver is just meant to be passed away by the main capserver
    // dont construct a EzrpcServer
    rb_iv_set(self,"rb_server",rb_server);
    rb_iv_set(self,"schema",interschema);

    return self;
  }

  VALUE CapabilityServer::process(VALUE self){
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

  void * CapabilityServer::loopServer(void * p){
    try {
      auto* loopcall = (loopCall*) p;
      loopcall->promisepair->promise.wait(*(loopcall->waitscope));
    }catch( kj::Exception t ){
      //adquire the lock to raise a ruby exception
      rb_thread_call_with_gvl(&Exception::raise,&t);
    }
  }

  void CapabilityServer::stopLoopServer(void *p){
    try {
      auto* promisefulfiller = (kj::PromiseFulfillerPair<void>*) p;
      promisefulfiller->fulfiller->fulfill();
    }catch( kj::Exception t ){
      Exception::raise(t);
    }
  }

  VALUE CapabilityServer::rb_server(VALUE self){
    return rb_iv_get(self,"rb_server");
  }

  capnp::InterfaceSchema* CapabilityServer::schema(VALUE self){
    return InterfaceSchema::unwrap(rb_iv_get(self,"schema"));
  }

}
