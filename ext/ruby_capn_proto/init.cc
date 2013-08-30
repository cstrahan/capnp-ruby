#include "ruby_capn_proto.h"
// #include "schema.h"
#include "schema_parser.h"

extern "C" {
  void Init_init();
}

using namespace ruby_capn_proto;

extern "C" {
  void Init_init() {
    SchemaParser::Init();
  }
}
