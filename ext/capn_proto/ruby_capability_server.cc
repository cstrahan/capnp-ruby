#include "ruby_capn_proto.h"
#include "call_context.h"
#include "ruby_capability_server.h"
#include "util.h"

namespace capnp {
  kj::Promise<void> capnp::RubyCapabilityServer::call(InterfaceSchema::Method method, CallContext<DynamicStruct, DynamicStruct> context) {
    // just a dummy c++ server that calls methods on a passed ruby server.
    // or that is my intention anyway

    auto method_name = method.getProto().getName();
    VALUE rb_context = ruby_capn_proto::CallContext::create(context);
    rb_funcall( this->server, rb_intern( method_name.cStr() ), rb_context );
    return kj::READY_NOW;
  }
}
