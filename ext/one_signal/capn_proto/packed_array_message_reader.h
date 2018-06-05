#ifndef PACKED_ARRAY_MESSAGE_READER_H
#define PACKED_ARRAY_MESSAGE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class PackedArrayMessageReader {
  public:
    using WrappedType = capnp::PackedMessageReader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE initialize(VALUE klass, VALUE io);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get_root(VALUE self, VALUE schema);

    static VALUE Class;
  };
}

#endif /* PACKED_ARRAY_MESSAGE_READER_H */
