#ifndef INTERFACE_METHOD_SCHEMA_H
#define INTERFACE_METHOD_SCHEMA_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class InterfaceMethod {
  public:
    using WrappedType = capnp::InterfaceSchema::Method;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType method);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    // no methods...
    static VALUE Class;
  };
}


#endif /* INTERFACE_METHOD_SCHEMA_H */
