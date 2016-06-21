#include "ruby_capn_proto.h"
#include "call_context.h"
#include "dynamic_struct_reader.h"
#include "dynamic_struct_builder.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::CallContext<capnp::DynamicStruct, capnp::DynamicStruct>;
  VALUE CallContext::Class;

  void CallContext::Init() {
    ClassBuilder("CallContext" , rb_cObject).
      defineAlloc(&alloc).
      defineMethod("getParams" , &getParams).
      defineMethod("releaseParams" , &releaseParams).
      defineMethod("getResults" , &getResults).
      defineMethod("initResults" , &initResults).
      defineMethod("setResults" , &setResults).
      store(&Class);
  }

  void CallContext::free(WrappedType* p) {
    p->~CallContext();
    ruby_xfree(p);
  }

  VALUE CallContext::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* CallContext::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE CallContext::create(WrappedType context) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped_context = unwrap(rb_obj);
    *wrapped_context = kj::mv(context);
    return rb_obj;
  }

  VALUE CallContext::getParams(VALUE self) {
    return DynamicStructReader::create(unwrap(self)->getParams(),Qnil);
  }

  VALUE CallContext::releaseParams(VALUE self) {
    unwrap(self)->releaseParams();
    return Qtrue;
  }

  VALUE CallContext::getResults(VALUE self) {
    return DynamicStructBuilder::create(unwrap(self)->getResults(), Qnil, Qtrue);
  }

  VALUE CallContext::initResults(VALUE self) {
    return DynamicStructBuilder::create(unwrap(self)->initResults(), Qnil, Qtrue );
  }

  VALUE CallContext::setResults(VALUE self, VALUE structReader) {
    // maybe check the type of structReader?
    unwrap(self)->setResults( *DynamicStructReader::unwrap(structReader) );
    return Qtrue;
  }
}
