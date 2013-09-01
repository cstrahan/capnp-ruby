#include "ruby_capn_proto.h"
#include "schema_parser.h"
#include "schema.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  VALUE SchemaParser::Class;

  void SchemaParser::Init() {
    ClassBuilder("SchemaParser", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("initialize", &initialize).
      defineMethod("parse_disk_file", &parse_disk_file).
      store(&Class);
  }

  void SchemaParser::free(SchemaParser* p) {
    p->~SchemaParser();
    ruby_xfree(p);
  }

  VALUE SchemaParser::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(capnp::SchemaParser)));
  }

  capnp::SchemaParser* SchemaParser::unwrap(VALUE self) {
    capnp::SchemaParser* p;
    Data_Get_Struct(self, capnp::SchemaParser, p);
    return p;
  }

  VALUE SchemaParser::initialize(VALUE self) {
    capnp::SchemaParser* p = unwrap(self);
    new (p) capnp::SchemaParser();

    return Qnil;
  }

  VALUE SchemaParser::parse_disk_file(VALUE self, VALUE rb_display_name, VALUE rb_disk_path, VALUE rb_import_path) {
    // auto imports = kj::Array<kj::StringPtr>(0);
    auto imports = Util::toStringArray(rb_import_path);
    auto importsPtrs = KJ_MAP(s, imports) -> kj::StringPtr { return s; };

    auto display_name = StringValueCStr(rb_display_name);
    auto schema = unwrap(self)->parseDiskFile(
        display_name,
        StringValueCStr(rb_disk_path),
        importsPtrs
        );
    return Schema::create(self, schema);
  }
}
