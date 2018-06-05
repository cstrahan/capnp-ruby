#include "ruby_capn_proto.h"
#include "message_reader.h"
#include "packed_fd_message_reader.h"
#include "struct_schema.h"
#include "dynamic_struct_reader.h"
#include "class_builder.h"
#include "exception.h"

namespace ruby_capn_proto
{
using WrappedType = capnp::PackedFdMessageReader;
VALUE PackedFdMessageReader::Class;

void PackedFdMessageReader::Init()
{
  ClassBuilder("PackedFdMessageReader", MessageReader::Class)
    .defineAlloc(&alloc)
    .defineMethod("initialize", &initialize)
    .defineMethod("get_root", &get_root).store(&Class);
}

VALUE PackedFdMessageReader::alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
}

VALUE PackedFdMessageReader::initialize(VALUE self, VALUE rb_io)
{
  VALUE rb_fileno = rb_funcall(rb_io, rb_intern("fileno"), 0);
  auto fileno = FIX2INT(rb_fileno);
  WrappedType *p = unwrap(self);

  try
  {
    new (p) WrappedType(fileno);
  }
  catch (kj::Exception ex)
  {
    return Exception::raise(ex);
  }

  return Qnil;
}

void PackedFdMessageReader::free(WrappedType *p)
{
  p->~PackedFdMessageReader();
  ruby_xfree(p);
}

WrappedType *PackedFdMessageReader::unwrap(VALUE self)
{
  WrappedType *p;
  Data_Get_Struct(self, WrappedType, p);
  return p;
}

VALUE PackedFdMessageReader::get_root(VALUE self, VALUE rb_schema)
{
  if (rb_respond_to(rb_schema, rb_intern("schema")))
  {
    rb_schema = rb_funcall(rb_schema, rb_intern("schema"), 0);
  }

  auto schema = *StructSchema::unwrap(rb_schema);
  auto reader = unwrap(self)->getRoot<capnp::DynamicStruct>(schema);
  return DynamicStructReader::create(reader, self);
}
} // namespace ruby_capn_proto
