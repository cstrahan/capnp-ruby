#include "ruby_capn_proto.h"

namespace capnp {
  class RubyCapabilityServer : public DynamicCapability::Server {
  private:
    VALUE server;
  public:
    RubyCapabilityServer( InterfaceSchema interface, VALUE server ): DynamicCapability::Server(interface) { this->server = server; }
    kj::Promise<void> call( InterfaceSchema::Method method, CallContext<DynamicStruct, DynamicStruct> context );
  };
}
