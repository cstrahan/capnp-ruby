#ifndef STREAM_FD_MESSAGE_READER_H
#define STREAM_FD_MESSAGE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class StreamFdMessageReader {
  public:
    using WrappedType = capnp::StreamFdMessageReader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE initialize(VALUE klass, VALUE io);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE get_root(VALUE name, VALUE schema);

    static VALUE Class;
  };
}

#endif /* STREAM_FD_MESSAGE_READER_H */
