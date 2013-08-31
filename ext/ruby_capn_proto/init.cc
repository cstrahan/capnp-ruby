#include "ruby_capn_proto.h"
#include "schema.h"
#include "schema_parser.h"
#include "schema_node_reader.h"
#include "list_nested_node_reader.h"

extern "C" {
  void Init_init();
}

using namespace ruby_capn_proto;

extern "C" {
  void Init_init() {
    SchemaParser::Init();
    Schema::Init();
    SchemaNodeReader::Init();
    ListNestedNodeReader::Init();
  }
}
