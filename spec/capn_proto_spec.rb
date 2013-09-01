require 'capn_proto'

ADDRESSBOOK_SCHEMA = File.expand_path("../addressbook.capnp", __FILE__);

def walk_schema(schema, level)
  padding = "#{" "*(level*2)}"
  node = schema.get_proto
  nested_nodes = node.nested_nodes

  nested_nodes.each do |nested_node|
    puts "#{padding}NODE: " << nested_node.name
    walk_schema(schema.get_nested(nested_node.name), level+1)
  end

  struct = schema.as_struct if node.struct?
  if struct
    struct.field_names.each do |field_name|
      puts "#{padding}FIELD: " << field_name
    end
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
