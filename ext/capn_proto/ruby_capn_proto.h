#ifndef RUBY_CAPN_PROTO_H
#define RUBY_CAPN_PROTO_H

#include <iostream>
#include <vector>

#include <kj/common.h>
#include <kj/array.h>

#include <capnp/serialize.h>
#include <capnp/serialize-packed.h>
#include <capnp/message.h>
#include <capnp/schema-parser.h>
#include <capnp/schema.h>
#include <capnp/message.h>
#include <capnp/dynamic.h>

#include <ruby.h>
#ifdef __
#undef __
#endif
#ifdef HAVE_RUBY_ENCODING_H
#include "ruby/encoding.h"
#endif

#if defined(RUBY_METHOD_FUNC)
# undef RUBY_METHOD_FUNC
# if RUBY_VERSION_CODE <= 166
    extern "C" typedef VALUE (*RUBY_METHOD_FUNC)();
# else
    extern "C" typedef VALUE (*RUBY_METHOD_FUNC)(ANYARGS);
# endif
#endif

namespace ruby_capn_proto {
}

#endif /* RUBY_CAPN_PROTO_H */
