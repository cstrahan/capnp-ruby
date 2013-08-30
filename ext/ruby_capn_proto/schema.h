#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Schema {
  public:
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(capnp::ParsedSchema schema);
    static void free(capnp::ParsedSchema* p);
    static capnp::ParsedSchema* unwrap(VALUE self);

    static VALUE Class;
  };
}
