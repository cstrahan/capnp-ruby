#ifndef DYNAMIC_VALUE_BUILDER_H
#define DYNAMIC_VALUE_BUILDER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicValueBuilder {
  public:
    static VALUE to_ruby(capnp::DynamicValue::Builder value, VALUE parent);
  };
}

#endif /* DYNAMIC_VALUE_BUILDER_H */
