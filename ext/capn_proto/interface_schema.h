#ifndef INTERFACE_SCHEMA_H
#define INTERFACE_SCHEMA_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class InterfaceSchema {
  public:
    using WrappedType = capnp::InterfaceSchema;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType schema, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    // commented methods below don't are strictly needed.
    //static VALUE getMethodByName(VALUE self, VALUE name);
    //static VALUE getMethods(VALUE self);
    static VALUE find_method_by_name(VALUE self, VALUE name);
    

    static VALUE Class;
  };
}


#endif /* STRUCT_SCHEMA_H */
