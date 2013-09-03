#include "util.h"

namespace ruby_capn_proto {
  kj::Array<kj::String> Util::toStringArray(VALUE rb_array) {
    auto len = RARRAY_LEN(rb_array);
    auto array = kj::heapArray<kj::String>(len);
    for (int i=0; i < len; i++) {
      auto rb_str = rb_ary_entry(rb_array, i);
      array[i] = toString(rb_str);
    }

    return array;
  }

  kj::String Util::toString(VALUE rb_string) {
    auto rb_val = StringValue(rb_string);
    auto str = RSTRING_PTR(rb_val);
    auto len = RSTRING_LEN(rb_val);
    return kj::heapString(str, len);
  }

  VALUE Util::toRubyString(kj::StringPtr string) {
    return rb_str_new(string.begin(), string.size());
  }
}
