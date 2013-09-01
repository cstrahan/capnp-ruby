#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicStructReader {
  public:
    using WrappedType = capnp::DynamicStruct::Reader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE which(VALUE self);

    static VALUE Class;
  };
}

