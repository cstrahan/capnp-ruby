#include "ruby_capn_proto.h"
#include "dynamic_list_reader.h"
#include "dynamic_value_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicList::Reader;
  VALUE DynamicListReader::Class;

  void DynamicListReader::Init() {
    ClassBuilder("DynamicListReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("[]", &get).
      defineMethod("size", &size).
      store(&Class);
  }

  VALUE DynamicListReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  void DynamicListReader::free(WrappedType* p) {
    p->~Reader();
    ruby_xfree(p);
  }

  WrappedType* DynamicListReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicListReader::create(WrappedType reader, VALUE parent) {
    auto rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);

    return rb_obj;
  }

  VALUE DynamicListReader::size(VALUE self) {
    return INT2FIX(unwrap(self)->size());
  }

  VALUE DynamicListReader::get(VALUE self, VALUE rb_index) {
    auto reader = *unwrap(self);
    auto index = FIX2INT(rb_index);
    auto size = reader.size();

    return DynamicValueReader::to_ruby(reader[index], self);
  }
}
