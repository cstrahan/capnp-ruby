#include "ruby_capn_proto.h"
#include "schema_parser.h"
#include "parsed_schema.h"
#include "exception.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  VALUE SchemaParser::Class;
  using WrappedType = capnp::SchemaParser;

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
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* SchemaParser::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE SchemaParser::initialize(VALUE self) {
    WrappedType* p = unwrap(self);
    new (p) WrappedType();

    return Qnil;
  }

  VALUE SchemaParser::parse_disk_file(VALUE self, VALUE rb_display_name, VALUE rb_disk_path, VALUE rb_import_path) {
    try {

      auto imports = Util::toStringArray(rb_import_path);
      auto importsPtrs = KJ_MAP(s, imports) -> kj::StringPtr { return s; };

      auto display_name = Util::toString(rb_display_name);
      auto schema = unwrap(self)->parseDiskFile(
          display_name,
          StringValueCStr(rb_disk_path),
          importsPtrs
          );
      return ParsedSchema::create(schema, self);

    }catch ( kj::Exception t ){
      Exception::raise(t);
      return Qnil;
    }
  }
}
