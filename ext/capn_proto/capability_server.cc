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
      defineMethod("process" , &process).
      defineMethod("initialize" , &create).
      store(&Class);
  }

  void CapabilityServer::free(WrappedType* p) {
    //p->~EzRpcServer(); to be fixed soon
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

    return self;
  }

  VALUE CapabilityServer::process(VALUE self){
    auto server = unwrap(self);
    rb_thread_call_without_gvl(loopServer, &(server->getWaitScope()), RUBY_UBF_IO , 0);
    return Qtrue;
  }

  void * CapabilityServer::loopServer(void * p){
    auto* waitScope = (kj::WaitScope*) p;
    kj::NEVER_DONE.wait(*waitScope);
  }

}
