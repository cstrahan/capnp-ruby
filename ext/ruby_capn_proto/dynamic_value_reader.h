#ifndef DYNAMIC_VALUE_READER_H
#define DYNAMIC_VALUE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicValueReader {
  public:
    static VALUE to_ruby(capnp::DynamicValue::Reader value, VALUE parent);
  };
}

#endif /* DYNAMIC_VALUE_READER_H */
