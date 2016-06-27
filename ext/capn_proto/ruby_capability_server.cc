#include "ruby_capn_proto.h"
#include "call_context.h"
#include "ruby_capability_server.h"
#include <ruby/thread.h>
#include "util.h"

namespace capnp {
  kj::Promise<void> RubyCapabilityServer::call(InterfaceSchema::Method method, CallContext<DynamicStruct, DynamicStruct> context) {
    // just a dummy c++ server that calls methods on a passed ruby server.
    // or that is my intention anyway
    callPacket packet;
    packet.methodName = method.getProto().getName().cStr();
    packet.rb_context = ruby_capn_proto::CallContext::create(context);
    packet.rb_server = this->server;
    rb_thread_call_with_gvl(this->rbCall, &packet);
    return kj::READY_NOW;
  }

  void * RubyCapabilityServer::rbCall(void * p){
    auto * packet = (callPacket*) p;
    rb_funcall( packet->rb_server, rb_intern( packet->methodName ), 1, packet->rb_context );
  }
}
