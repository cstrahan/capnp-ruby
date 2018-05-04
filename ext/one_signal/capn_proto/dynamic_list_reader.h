#ifndef DYNAMIC_LIST_READER_H
#define DYNAMIC_LIST_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicListReader {
  public:
    using WrappedType = capnp::DynamicList::Reader;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE which(VALUE self);
    static VALUE get(VALUE self, VALUE index);
    static VALUE size(VALUE self);

    static VALUE Class;
  private:
    static VALUE _get(VALUE self, VALUE index);
  };
}

#endif /* DYNAMIC_LIST_READER_H */
