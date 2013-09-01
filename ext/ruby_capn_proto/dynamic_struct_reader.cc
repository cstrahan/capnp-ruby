#include "ruby_capn_proto.h"
#include "dynamic_struct_reader.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::DynamicStruct::Reader;
  VALUE DynamicStructReader::Class;

  void DynamicStructReader::Init() {
    ClassBuilder("DynamicStructReader", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("which", &which).
      store(&Class);
  }

  void DynamicStructReader::free(WrappedType* p) {
    p->~Reader();
    ruby_xfree(p);
  }

  VALUE DynamicStructReader::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* DynamicStructReader::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE DynamicStructReader::create(WrappedType reader) {
    VALUE rb_obj = alloc(Class);
    WrappedType* wrapped = unwrap(rb_obj);
    *wrapped = kj::mv(reader);

    return rb_obj;
  }

  VALUE toRuby(capnp::DynamicValue::Reader value, VALUE parent) {
    switch (value.getType())
    {
      case capnp::DynamicValue::BOOL:
        return value.as<bool>() ? Qtrue : Qfalse;
      case capnp::DynamicValue::INT:
        return INT2FIX(value.as<int64_t>());
      case capnp::DynamicValue::UINT:
        return INT2FIX(value.as<uint64_t>());
      case capnp::DynamicValue::FLOAT:
        return rb_float_new(value.as<double>());
      case capnp::DynamicValue::TEXT:
        {
          auto text = value.as<capnp::Text>();
          return rb_str_new(text.begin(), text.size());
        }
      case capnp::DynamicValue::DATA:
        {
          auto data = value.as<capnp::Data>();
          return rb_str_new((const char*)data.begin(), data.size());
        }
      case capnp::DynamicValue::LIST:
        // return DynamicListReader::create(value.as<capnp::List>(), parent);
        return Qnil;
      case capnp::DynamicValue::STRUCT:
        return DynamicStructReader::create(value.as<capnp::DynamicStruct>());
      case capnp::DynamicValue::ENUM:
        {
          auto enumerant_maybe = value.as<capnp::DynamicEnum>().getEnumerant();
          KJ_IF_MAYBE(enumerant, enumerant_maybe) {
            auto name = enumerant->getProto().getName();
            return rb_str_new(name.begin(), name.size());
          } else {
            return Qnil;
          }
        }
      case capnp::DynamicValue::VOID:
        return Qnil;
      case capnp::DynamicValue::UNKNOWN:
      default:
        return Qnil;
    }
  }

  VALUE DynamicStructReader::which(VALUE self) {
    auto schema_maybe = unwrap(self)->which();
    KJ_IF_MAYBE(schema, schema_maybe) {
      auto name = schema->getProto().getName();
      return rb_str_new(name.begin(), name.size());
    } else {
      // throw std::invalid_argument("member was null");
      return Qnil;
    }
  }
}
