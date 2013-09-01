#include "ruby_capn_proto.h"
#include "field_list.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::StructSchema::FieldList;
  VALUE FieldList::Class;

  void FieldList::Init() {
    ClassBuilder("FieldList", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("size", &size).
      defineMethod("[]", &get).
      store(&Class);
  }

  void FieldList::free(WrappedType* p) {
    p->~FieldList();
    ruby_xfree(p);
  }

  VALUE FieldList::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* FieldList::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE FieldList::create(WrappedType schema) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_schema = unwrap(rb_obj);
    *wrapped_schema = kj::mv(schema);

    return rb_obj;
  }

  VALUE FieldList::get(VALUE self, VALUE index) {
    auto idx = FIX2INT(index);
    auto list = *unwrap(self);
    return Qnil;
    // return Field::create(list[idx]);
  }

  VALUE FieldList::size(VALUE self) {
    return INT2FIX(unwrap(self)->size());
  }
}
