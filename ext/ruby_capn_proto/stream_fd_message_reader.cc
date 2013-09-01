#include "ruby_capn_proto.h"
#include "message_reader.h"
#include "stream_fd_message_reader.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::StreamFdMessageReader;
  VALUE StreamFdMessageReader::Class;

  void StreamFdMessageReader::Init() {
    ClassBuilder("StreamFdMessageReader", MessageReader::Class).
      defineAlloc(&alloc).
      defineMethod("initialize", &initialize).
      store(&Class);
  }

  VALUE StreamFdMessageReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  VALUE StreamFdMessageReader::initialize(VALUE self, VALUE rb_io) {
    VALUE rb_fileno = rb_funcall(rb_io, rb_intern("fileno"), 0);
    auto fileno = FIX2INT(rb_fileno);
    WrappedType* p = unwrap(self);
    new (p) WrappedType(fileno);

    return Qnil;
  }

  void StreamFdMessageReader::free(WrappedType* p) {
    p->~StreamFdMessageReader();
    ruby_xfree(p);
  }

  WrappedType* StreamFdMessageReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }
}
