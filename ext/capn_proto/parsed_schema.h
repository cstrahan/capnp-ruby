#ifndef PARSED_SCHEMA_H
#define PARSED_SCHEMA_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class ParsedSchema {
  public:
    using WrappedType = capnp::ParsedSchema;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType schema, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get_proto(VALUE self);
    static VALUE get_nested(VALUE self, VALUE name);
    static VALUE as_struct(VALUE self);
    static VALUE as_interface(VALUE self);

    static VALUE Class;
  };
}

#endif /* PARSED_SCHEMA_H */
