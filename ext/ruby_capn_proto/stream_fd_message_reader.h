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
    static VALUE get_nested_nodes(VALUE self);
    static VALUE is_struct(VALUE self);
    static VALUE is_enum(VALUE self);

    static VALUE Class;
  };
}
