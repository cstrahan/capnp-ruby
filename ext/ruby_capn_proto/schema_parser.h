#ifndef SCHEMA_PARSER_H
#define SCHEMA_PARSER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class SchemaParser {
  public:
    static void Init();
    static VALUE parse_disk_file(VALUE self, VALUE display_name, VALUE disk_path, VALUE import_path);
    static VALUE initialize(VALUE klass);
    static VALUE alloc(VALUE klass);
    static void free(SchemaParser* p);
    static capnp::SchemaParser* unwrap(VALUE self);

    static VALUE Class;
  };
}

#endif /* SCHEMA_PARSER_H */
