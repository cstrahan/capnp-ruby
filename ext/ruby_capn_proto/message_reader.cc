#include "ruby_capn_proto.h"
#include "message_reader.h"
#include "class_builder.h"
#include "struct_schema.h"
#include "dynamic_struct_reader.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::MessageReader;
  VALUE MessageReader::Class;

  void MessageReader::Init() {
    ClassBuilder("MessageReader", rb_cObject).
      store(&Class);
  }

  // XXX
  // I wanted to use inheritance here for #get_root,
  // but this segfaults unless I reinterpret_cast to the right
  // subclass of capnp::MessageReader. Whish I know more about
  // the C++ object model :(...
  // Worst case scenario, I could probably use tempalates...
  // If only I had experience with them.

  WrappedType* MessageReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }
}
