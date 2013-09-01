#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class MessageReader {
  public:
    using WrappedType = capnp::MessageReader;
    static void Init();
    static WrappedType* unwrap(VALUE self);
    static VALUE get_root(VALUE name, VALUE schema);

    static VALUE Class;
  };
}
