#ifndef REQUEST_H
#define REQUEST_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Request {
  public:
    using WrappedType = capnp::Request;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE request);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    // to think
    //static VALUE somenthing(VALUE self);
    static VALUE Class;
  };
}


#endif /* STRUCT_SCHEMA_H */
