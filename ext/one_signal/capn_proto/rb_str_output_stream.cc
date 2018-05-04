#include "ruby_capn_proto.h"
#include "rb_str_output_stream.h"

namespace ruby_capn_proto {
  RbStrOutputStream::~RbStrOutputStream() noexcept(false) {}

  void RbStrOutputStream::write(const void *buffer, size_t size)
  {
    const char *pos = reinterpret_cast<const char *>(buffer);
    rb_str_cat(str, pos, size);
  }
}
