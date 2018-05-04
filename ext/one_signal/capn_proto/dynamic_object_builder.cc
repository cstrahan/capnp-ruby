#include "ruby_capn_proto.h"
#include "dynamic_object_builder.h"
#include "dynamic_struct_builder.h"
#include "struct_schema.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::AnyPointer::Builder;
  VALUE DynamicObjectBuilder::Class;

  void DynamicObjectBuilder::Init() {
    ClassBuilder("DynamicObjectBuilder", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("as_struct", &as_struct).
      store(&Class);
  }

  void DynamicObjectBuilder::free(WrappedType* p) {
    p->~Builder();
    ruby_xfree(p);
  }

  VALUE DynamicObjectBuilder::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* DynamicObjectBuilder::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicObjectBuilder::create(WrappedType reader, VALUE parent) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);

    rb_iv_set(rb_obj, "parent", parent);

    return rb_obj;
  }

  VALUE DynamicObjectBuilder::as_struct(VALUE self, VALUE rb_schema) {
    if (rb_respond_to(rb_schema, rb_intern("schema"))) {
      rb_schema = rb_funcall(rb_schema, rb_intern("schema"), 0);
    }

    auto reader = *unwrap(self);
    auto schema = *StructSchema::unwrap(rb_schema);

    return DynamicStructBuilder::create(
      reader.getAs<capnp::DynamicStruct>(schema),
      self,
      false);
  }
}
