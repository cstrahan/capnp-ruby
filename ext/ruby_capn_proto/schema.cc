#include "ruby_capn_proto.h"
#include "schema.h"
#include "class_builder.h"

namespace ruby_capn_proto {
  VALUE Schema::Class;

  void Schema::Init() {
    ClassBuilder("Schema", rb_cObject);
  }
}
