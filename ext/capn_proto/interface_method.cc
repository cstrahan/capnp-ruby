#include "ruby_capn_proto.h"
#include "interface_method.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::InterfaceSchema::Method;
  VALUE InterfaceMethod::Class;

  void InterfaceMethod::Init() {
    ClassBuilder("InterfaceMethod", rb_cObject).
      defineAlloc(&alloc).
      // no methods...
      store(&Class);
  }

  void InterfaceMethod::free(WrappedType* p) {
    //p->~Method();
    ruby_xfree(p);
  }

  VALUE InterfaceMethod::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* InterfaceMethod::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE InterfaceMethod::create(WrappedType method) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_method = unwrap(rb_obj);
    *wrapped_method = kj::mv(method);
    return rb_obj;
  }
}
