#include "ruby_capn_proto.h"

#include "exception.h"

#include "schema_parser.h"
#include "parsed_schema.h"
#include "struct_schema.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "schema_node_reader.h"
#include "nested_node_reader.h"
#include "list_nested_node_reader.h"
#include "field_list.h"

#include "message_reader.h"
#include "message_builder.h"
#include "stream_fd_message_reader.h"
#include "malloc_message_builder.h"
#include "flat_array_message_reader.h"

#include "dynamic_struct_reader.h"
#include "dynamic_struct_builder.h"
#include "dynamic_list_reader.h"
#include "dynamic_list_builder.h"
#include "dynamic_object_reader.h"
#include "dynamic_object_builder.h"

using namespace ruby_capn_proto;

extern "C" {
  void Init_capn_proto() {
    Exception::Init();

    SchemaParser::Init();
    ParsedSchema::Init();
    StructSchema::Init();
    InterfaceSchema::Init();
    InterfaceMethod::Init();
    SchemaNodeReader::Init();
    NestedNodeReader::Init();
    ListNestedNodeReader::Init();
    FieldList::Init();

    MessageReader::Init();
    MessageBuilder::Init();
    StreamFdMessageReader::Init();
    MallocMessageBuilder::Init();
    FlatArrayMessageReader::Init();

    DynamicStructReader::Init();
    DynamicStructBuilder::Init();
    DynamicListReader::Init();
    DynamicListBuilder::Init();
    DynamicObjectReader::Init();
    DynamicObjectBuilder::Init();
  }
}
