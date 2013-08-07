module CapnProto
  module Schema
    module Value
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

      end
      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Body
        def get_bool_value()
          @reader.get_uint8(8) & 1 == 1
        end
        def get_int8_value()
          @reader.get_int8(0)
        end
        def get_int16_value()
          @reader.get_int16(0)
        end
        def get_int32_value()
          @reader.get_int32(0)
        end
        def get_int64_value()
          @reader.get_int64(0)
        end
        def get_uint8_value()
          @reader.get_uint8(0)
        end
        def get_uint16_value()
          @reader.get_uint16(0)
        end
        def get_uint32_value()
          @reader.get_uint32(0)
        end
        def get_uint64_value()
          @reader.get_uint64(0)
        end
        def get_float32_value()
          @reader.get_float32(0)
        end
        def get_float64_value()
          @reader.get_float64(0)
        end
        def get_enum_value()
          @reader.get_uint16(0)
        end
      end
    end
  end
end
