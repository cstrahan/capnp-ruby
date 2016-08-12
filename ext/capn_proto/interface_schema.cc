#include "ruby_capn_proto.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::InterfaceSchema;
  VALUE InterfaceSchema::Class;

  void InterfaceSchema::Init() {
    ClassBuilder("InterfaceSchema", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("find_method_by_name" , &find_method_by_name).
      store(&Class);
  }

  void InterfaceSchema::free(WrappedType* p) {
    p->~InterfaceSchema();
    ruby_xfree(p);
  }

  VALUE InterfaceSchema::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* InterfaceSchema::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE InterfaceSchema::create(WrappedType schema, VALUE parent) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_schema = unwrap(rb_obj);
    *wrapped_schema = kj::mv(schema);

    rb_iv_set(rb_obj, "parent", parent);

    return rb_obj;
  }

  VALUE InterfaceSchema::find_method_by_name(VALUE self, VALUE name){
    capnp::InterfaceSchema::Method value;
    KJ_IF_MAYBE(value, unwrap(self)->findMethodByName(Util::toString(name))) {
      return InterfaceMethod::create(*value);
    } else {
      return Qfalse;
    }
  }
}
