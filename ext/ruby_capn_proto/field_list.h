#ifndef FIELD_LIST_H
#define FIELD_LIST_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class FieldList {
  public:
    using WrappedType = capnp::StructSchema::FieldList;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType schema);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get(VALUE self, VALUE name);
    static VALUE size(VALUE self);

    static VALUE Class;
  };
}


#endif /* FIELD_LIST_H */
