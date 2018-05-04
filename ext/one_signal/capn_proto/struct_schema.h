#ifndef STRUCT_SCHEMA_H
#define STRUCT_SCHEMA_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class StructSchema {
  public:
    using WrappedType = capnp::StructSchema;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType schema, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE field_names(VALUE self);
    static VALUE fields(VALUE self);

    static VALUE Class;
  };
}


#endif /* STRUCT_SCHEMA_H */
