#ifndef DYNAMIC_STRUCT_READER_H
#define DYNAMIC_STRUCT_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicStructReader {
  public:
    using WrappedType = capnp::DynamicStruct::Reader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE which(VALUE self);
    static VALUE get(VALUE self, VALUE name);

    static VALUE Class;
  private:
    static VALUE _get(VALUE self, VALUE name);
  };
}


#endif /* DYNAMIC_STRUCT_READER_H */
