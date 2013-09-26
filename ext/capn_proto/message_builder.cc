#include "ruby_capn_proto.h"
#include "message_builder.h"
#include "class_builder.h"
#include "struct_schema.h"
#include "dynamic_struct_reader.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::MessageBuilder;
  VALUE MessageBuilder::Class;

  void MessageBuilder::Init() {
    ClassBuilder("MessageBuilder", rb_cObject).
      store(&Class);
  }

  WrappedType* MessageBuilder::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }
}
