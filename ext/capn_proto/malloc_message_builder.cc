#include "ruby_capn_proto.h"
#include "malloc_message_builder.h"
#include "message_builder.h"
#include "struct_schema.h"
#include "dynamic_struct_builder.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::MallocMessageBuilder;
  VALUE MallocMessageBuilder::Class;

  void MallocMessageBuilder::Init() {
    ClassBuilder("MallocMessageBuilder", MessageBuilder::Class).
      defineAlloc(&alloc).
      defineMethod("initialize", &initialize).
      defineMethod("init_root", &init_root).
      // defineMethod("get_root", &get_root).
      store(&Class);
  }

  VALUE MallocMessageBuilder::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  VALUE MallocMessageBuilder::initialize(VALUE self) {
    WrappedType* p = unwrap(self);
    new (p) WrappedType();
    return Qnil;
  }

  void MallocMessageBuilder::free(WrappedType* p) {
    p->~MallocMessageBuilder();
    ruby_xfree(p);
  }

  WrappedType* MallocMessageBuilder::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE MallocMessageBuilder::init_root(VALUE self, VALUE rb_schema) {
    if (rb_respond_to(rb_schema, rb_intern("schema"))) {
      rb_schema = rb_funcall(rb_schema, rb_intern("schema"), 0);
    }

    auto schema = *StructSchema::unwrap(rb_schema);
    auto builder = unwrap(self)->initRoot<capnp::DynamicStruct>(schema);
    return DynamicStructBuilder::create(builder, self, true);
  }
}
