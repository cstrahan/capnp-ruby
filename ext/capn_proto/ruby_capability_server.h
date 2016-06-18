namespace capnp {
  class RubyCapabilityServer : public DynamicCapability::Server {
  public:
  RubyCapabilityServer(InterfaceSchema interface): DynamicCapability::Server(interface) {}
  kj::Promise<void> call(InterfaceSchema::Method method, CallContext<DynamicStruct, DynamicStruct> context) override;  
  }
}
