#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class Exception {
  public:
    using WrappedType = kj::Exception;
    static void Init();
    static VALUE create(WrappedType schema);

    static VALUE Class;
  };
}


#endif /* EXCEPTION_H */
