#include "ruby_capn_proto.h"
#include "parsed_schema.h"
#include "schema_parser.h"
#include "schema_node_reader.h"
#include "struct_schema.h"
#include "nested_node_reader.h"
#include "list_nested_node_reader.h"
#include "field_list.h"
#include "message_reader.h"

extern "C" {
  void Init_init();
}

using namespace ruby_capn_proto;

extern "C" {
  void Init_init() {
    SchemaParser::Init();
    SchemaNodeReader::Init();
    ParsedSchema::Init();
    StructSchema::Init();
    MessageReader::Init();
    ListNestedNodeReader::Init();
    NestedNodeReader::Init();
    FieldList::Init();
  }
}
