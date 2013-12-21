#ifndef DYNAMIC_OBJECT_BUILDER_H
#define DYNAMIC_OBJECT_BUILDER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicObjectBuilder {
  public:
    using WrappedType = capnp::AnyPointer::Builder;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE as_struct(VALUE self, VALUE name);

    static VALUE Class;
  };
}


#endif
