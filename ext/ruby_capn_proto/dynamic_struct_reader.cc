#include "ruby_capn_proto.h"
#include "dynamic_struct_reader.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicStruct::Reader;
  VALUE DynamicStructReader::Class;

  void DynamicStructReader::Init() {
    ClassBuilder("DynamicStructReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("which", &which).
      store(&Class);
  }

  void DynamicStructReader::free(WrappedType* p) {
    p->~Reader();
    ruby_xfree(p);
  }

  VALUE DynamicStructReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* DynamicStructReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicStructReader::create(WrappedType reader) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);

    return rb_obj;
  }

  VALUE DynamicStructReader::which(VALUE self) {
    auto schema_maybe = unwrap(self)->which();
    KJ_IF_MAYBE(schema, schema_maybe) {
      auto name = schema->getProto().getName();
      return rb_str_new(name.begin(), name.size());
    } else {
      // throw std::invalid_argument("member was null");
      return Qnil;
    }
  }
}
