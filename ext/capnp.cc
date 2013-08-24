#include <iostream>

#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include <capnp/serialize.h>
#include <capnp/serialize-packed.h>
#include <capnp/message.h>
#include <capnp/schema-parser.h>

using namespace Rice;
using namespace capnp;

template<>
word* from_ruby<word*>(Object x)
{
  return (word*)NUM2SIZET(x.value());
}

// template<>
// kj::ArrayPtr<const kj::StringPtr> from_ruby<kj::ArrayPtr<const kj::StringPtr>>(Object x)
// {
  // // ::capnp::SchemaParser parser;
  // ::kj::ArrayPtr< ::kj::StringPtr> imports;
  // // parser.parseDiskFile("test", "schema.capnp", imports);
// }

extern "C" {
  void Init_capn_proto_ext() {
    Module capnp = define_module("CapnProto");


    // ::capnp::SchemaParser parser;
    // ::kj::ArrayPtr< ::kj::StringPtr> imports;
    // parser.parseDiskFile("test", "schema.capnp", imports);

    auto arrayPtr =
      capnp.define_class<kj::ArrayPtr<word>>("ArrayPtr")
           .define_constructor(Constructor<kj::ArrayPtr<word>, word*, size_t>(),
               (Arg("ptr"), Arg("size")))
           .define_method("size", &kj::ArrayPtr<word>::size);

      // ParsedSchema parseDiskFile(kj::StringPtr displayName, kj::StringPtr diskPath,
                                       // kj::ArrayPtr<const kj::StringPtr> importPath);

    // auto parsedSchema =
      // capnp.define_class<capnp::ParsedSchema>("ParsedSchema")
           // .define_constructor(Constructor<capnp::ParsedSchema>())
           // .define_method("parse_disk_file", &capnp::SchemaParser::parseDiskFile);

    auto schemaParser =
      capnp.define_class<capnp::SchemaParser>("SchemaParser")
           .define_constructor(Constructor<capnp::SchemaParser>())
           .define_method("parse_disk_file", &capnp::SchemaParser::parseDiskFile);
  }
}
