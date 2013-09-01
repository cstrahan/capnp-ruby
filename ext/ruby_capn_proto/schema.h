#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Schema {
  public:
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(VALUE parent, capnp::ParsedSchema schema);
    static void free(capnp::ParsedSchema* p);
    static capnp::ParsedSchema* unwrap(VALUE self);
    static VALUE get_proto(VALUE self);
    static VALUE get_nested(VALUE self, VALUE name);
    static VALUE as_struct(VALUE self, VALUE name);

    static VALUE Class;
  };
}
