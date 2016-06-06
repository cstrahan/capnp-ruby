#include "ruby_capn_proto.h"
#include "dynamic_value_reader.h"
#include "dynamic_list_reader.h"
#include "dynamic_struct_reader.h"
#include "dynamic_object_reader.h"
#include "capability_client.h"

namespace ruby_capn_proto {
  VALUE DynamicValueReader::to_ruby(capnp::DynamicValue::Reader value, VALUE parent) {
    switch (value.getType())
    {
      case capnp::DynamicValue::CAPABILITY:
        return Qnil;//CapabilityClient::fromRaw(value.as<capnp::DynamicCapability>());
      case capnp::DynamicValue::BOOL:
        return value.as<bool>() ? Qtrue : Qfalse;
      case capnp::DynamicValue::INT:
        return INT2NUM(value.as<int64_t>());
      case capnp::DynamicValue::UINT:
        return UINT2NUM(value.as<uint64_t>());
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
        return DynamicListReader::create(value.as<capnp::DynamicList>(), parent);
      case capnp::DynamicValue::STRUCT:
        return DynamicStructReader::create(value.as<capnp::DynamicStruct>(), parent);
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
      case capnp::DynamicValue::ANY_POINTER:
        return DynamicObjectReader::create(value.as<capnp::AnyPointer>(), parent);
      case capnp::DynamicValue::VOID:
        return Qnil;
      case capnp::DynamicValue::UNKNOWN:
      default:
        return Qnil;
    }
  }
}
