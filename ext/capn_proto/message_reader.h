#ifndef MESSAGE_READER_H
#define MESSAGE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class MessageReader {
  public:
    using WrappedType = capnp::MessageReader;
    static void Init();
    static WrappedType* unwrap(VALUE self);

    static VALUE Class;
  };
}

#endif /* MESSAGE_READER_H */
