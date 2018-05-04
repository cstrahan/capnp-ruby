#include "ruby_capn_proto.h"
#include "struct_schema.h"
#include "field_list.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::StructSchema;
  VALUE StructSchema::Class;

  void StructSchema::Init() {
    ClassBuilder("StructSchema", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("field_names", &field_names).
      defineMethod("fields", &fields).
      store(&Class);
  }

  void StructSchema::free(WrappedType* p) {
    p->~StructSchema();
    ruby_xfree(p);
  }

  VALUE StructSchema::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* StructSchema::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE StructSchema::create(WrappedType schema, VALUE parent) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_schema = unwrap(rb_obj);
    *wrapped_schema = kj::mv(schema);

    rb_iv_set(rb_obj, "parent", parent);

    return rb_obj;
  }

  VALUE StructSchema::field_names(VALUE self) {
    auto field_list = unwrap(self)->getFields();
    auto size = field_list.size();
    auto rb_array = rb_ary_new2(size);
    for (int i=0; i<size; i++) {
      auto name = field_list[i].getProto().getName();
      rb_ary_push(rb_array, rb_str_new(name.begin(), name.size()));
    }

    return rb_array;
  }

  VALUE StructSchema::fields(VALUE self) {
    return FieldList::create(unwrap(self)->getFields());
  }
}
