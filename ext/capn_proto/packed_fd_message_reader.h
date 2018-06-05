#ifndef PACKED_FD_MESSAGE_READER_H
#define PACKED_FD_MESSAGE_READER_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto
{
class PackedFdMessageReader
{
public:
  using WrappedType = capnp::PackedFdMessageReader;
  static void Init();
  static VALUE alloc(VALUE klass);
  static VALUE initialize(VALUE klass, VALUE io);
  static void free(WrappedType *p);
  static WrappedType *unwrap(VALUE self);
  static VALUE get_root(VALUE self, VALUE schema);

  static VALUE Class;
};
} // namespace ruby_capn_proto

#endif /* PACKED_FD_MESSAGE_READER_H */
