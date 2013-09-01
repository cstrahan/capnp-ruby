require 'capn_proto'

ADDRESSBOOK_SCHEMA = File.expand_path("../addressbook.capnp", __FILE__)

module AddressBook extend CapnProto::SchemaLoader
  load_schema(ADDRESSBOOK_SCHEMA)
end

describe Example do
  it "works" do
    AddressBook::AddressBook
  end
end
