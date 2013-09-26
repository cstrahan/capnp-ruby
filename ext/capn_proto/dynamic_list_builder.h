#ifndef DYNAMIC_LIST_BUILDER_H
#define DYNAMIC_LIST_BUILDER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicListBuilder {
  public:
    using WrappedType = capnp::DynamicList::Builder;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader, VALUE parent);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE which(VALUE self);
    static VALUE get(VALUE self, VALUE index);
    static VALUE set(VALUE self, VALUE index, VALUE rb_obj);
    static VALUE size(VALUE self);

    static VALUE Class;
  private:
    static VALUE _get(VALUE self, VALUE index);
    static VALUE _set(VALUE self, VALUE index, VALUE rb_obj);
  };
}

#endif /* DYNAMIC_LIST_BUILDER_H */
