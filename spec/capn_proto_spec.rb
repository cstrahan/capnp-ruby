require 'capn_proto'

describe CapnProto do
  it "works" do
    addressbook_schema = File.expand_path("../addressbook.capnp", __FILE__);
    imports = []
    parser = CapnProto::SchemaParser.new
    parser.parse_disk_file(
      "addressbook",
      addressbook_schema,
      imports);
  end
end
