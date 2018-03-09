#ifndef DYNAMIC_STRUCT_BUILDER_H
#define DYNAMIC_STRUCT_BUILDER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class DynamicStructBuilder {
  public:
    using WrappedType = capnp::DynamicStruct::Builder;
    static void Init();
    static VALUE alloc(VALUE klass);
    static VALUE create(WrappedType reader, VALUE parent, bool is_root);
    static void free(WrappedType* p);
    static WrappedType* unwrap(VALUE self);
    static VALUE which(VALUE self);
    static VALUE get(VALUE self, VALUE rb_name);
    static VALUE set(VALUE self, VALUE rb_name, VALUE rb_obj);

    static VALUE init(VALUE self, VALUE rb_name, VALUE rb_obj);
    static VALUE init(int argc, VALUE* argv, VALUE self);

    static VALUE write(VALUE self, VALUE file);
    static VALUE writePacked(VALUE self, VALUE file);
    static VALUE to_bytes(VALUE self);

    static VALUE Class;
  private:
    static VALUE _get(VALUE self, VALUE name);
    static VALUE _set(VALUE self, VALUE rb_name, VALUE rb_obj);

    static VALUE _init(VALUE self, VALUE rb_name, VALUE rb_count, int argc);
  };
}

#endif
