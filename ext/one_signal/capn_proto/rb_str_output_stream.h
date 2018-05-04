#ifndef RB_STR_OUTPUT_STREAM_H
#define RB_STR_OUTPUT_STREAM_H

#include "ruby_capn_proto.h"
#include "kj/io.h"

namespace ruby_capn_proto
{
  class RbStrOutputStream : public kj::OutputStream {
      // An OutputStream wrapping string buffer

    public:
      explicit RbStrOutputStream(VALUE str) : str(str) {}
      KJ_DISALLOW_COPY(RbStrOutputStream);
      ~RbStrOutputStream() noexcept(false);

      void write(const void *buffer, size_t size) override;

    private:
      VALUE str;
  };
}

#endif /* RB_STR_OUTPUT_STREAM_H */
