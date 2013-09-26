#include "ruby_capn_proto.h"
#include "parsed_schema.h"
#include "schema_parser.h"
#include "schema_node_reader.h"
#include "struct_schema.h"
#include "nested_node_reader.h"
#include "list_nested_node_reader.h"
#include "dynamic_struct_reader.h"
#include "dynamic_list_reader.h"
#include "stream_fd_message_reader.h"
#include "dynamic_object_reader.h"
#include "message_reader.h"
#include "exception.h"
#include "field_list.h"

extern "C" {
  void Init_init();
}

using namespace ruby_capn_proto;

extern "C" {
  void Init_capn_proto() {
    SchemaParser::Init();
    SchemaNodeReader::Init();
    ParsedSchema::Init();
    StructSchema::Init();
    MessageReader::Init();
    ListNestedNodeReader::Init();
    NestedNodeReader::Init();
    DynamicStructReader::Init();
    DynamicListReader::Init();
    StreamFdMessageReader::Init();
    FieldList::Init();
    DynamicObjectReader::Init();
    Exception::Init();
  }
}
