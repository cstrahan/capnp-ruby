#ifndef UTIL_H
#define UTIL_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Util {
  public:
    static kj::Array<kj::String> toStringArray(VALUE array_of_strings);
    static kj::String toString(VALUE string);
    static bool isNegative(VALUE rb_obj);

    static VALUE toRubyString(kj::StringPtr string);
  };
}

#endif /* UTIL_H */
