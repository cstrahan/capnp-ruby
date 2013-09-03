#include "ruby_capn_proto.h"
#include "nested_node_reader.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::schema::Node::NestedNode::Reader;
  VALUE NestedNodeReader::Class;

  void NestedNodeReader::Init() {
    ClassBuilder("NestedNodeReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("name", &name).
      store(&Class);
  }

  VALUE NestedNodeReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  VALUE NestedNodeReader::create(WrappedType reader) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);
    return rb_obj;
  }

  void NestedNodeReader::free(WrappedType* p) {
    p->~Reader();
    ruby_xfree(p);
  }

  WrappedType* NestedNodeReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE NestedNodeReader::name(VALUE self) {
    return Util::toRubyString(unwrap(self)->getName());
  }
}
