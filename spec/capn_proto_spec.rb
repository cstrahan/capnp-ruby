require 'capn_proto'

ADDRESSBOOK_SCHEMA = File.expand_path("../addressbook.capnp", __FILE__);

def walk_schema(schema, level)
  node_reader = schema.get_proto
  nodes = node_reader.nested_nodes
  nodes.each do |n|
    puts "#{" "*(level*2)}NAME: " << n.name
    walk_schema(schema.get_nested(n.name), level+1)
  end
end

describe CapnProto do
  it "works" do
    imports = []
    parser = CapnProto::SchemaParser.new
    schema = parser.parse_disk_file(
      "addressbook",
      ADDRESSBOOK_SCHEMA,
      imports);

    walk_schema(schema, 0)
  end
end
