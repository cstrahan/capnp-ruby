#ifndef FLAT_ARRAY_MESSAGE_READER_H
#define FLAT_ARRAY_MESSAGE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class FlatArrayMessageReader {
  public:
    using WrappedType = capnp::FlatArrayMessageReader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE initialize(VALUE klass, VALUE io);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get_root(VALUE self, VALUE schema);

    static VALUE Class;
  };
}

#endif /* FLAT_ARRAY_MESSAGE_READER_H */
