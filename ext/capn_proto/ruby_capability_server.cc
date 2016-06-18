#include "ruby_capn_proto.h"
#include "context.h"
#include "ruby_capability_server.h"
#include "util.h"

namespace capnp {
  capnp::RubyCapabilityServer::call(InterfaceSchema::Method method, CallContext<DynamicStruct, DynamicStruct> context) override {
    char* method_name = method.getProto.getName();
    VALUE rb_method_name = rb_str_new(method_name.begin(), method_name.size());
    VALUE rb_context = ruby_capn_proto::context::create(context);
    rb_eval("self."+method_name);

  }
}
