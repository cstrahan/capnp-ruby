#include "ruby_capn_proto.h"

namespace capnp {
  // helper struct to use rb_thread_call_with_gvl
  typedef struct _callPacket {
    const char* methodName;
    VALUE rb_context;
    VALUE rb_server;
  } callPacket;

  class RubyCapabilityServer : public DynamicCapability::Server {

  private:
    VALUE server;

  public:
    RubyCapabilityServer( InterfaceSchema interface, VALUE server ): DynamicCapability::Server(interface) { this->server = server; }
    kj::Promise<void> call( InterfaceSchema::Method method, CallContext<DynamicStruct, DynamicStruct> context );
    static void * rbCall(void * p); // to be called with rb_thread_call_with_gvl
  };
}
