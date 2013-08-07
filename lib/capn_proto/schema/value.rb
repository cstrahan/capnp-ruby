module CapnProto
  module Schema
    module Value
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_body()
          Body::Reader.new(@reader.get_struct_field(0, nil)
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Body
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          VOID_VALUE = 9
          BOOL_VALUE = 1
          INT8_VALUE = 2
          INT16_VALUE = 3
          INT32_VALUE = 4
          INT64_VALUE = 5
          UINT8_VALUE = 6
          UINT16_VALUE = 7
          UINT32_VALUE = 8
          UINT64_VALUE = 0
          FLOAT32_VALUE = 10
          FLOAT64_VALUE = 11
          TEXT_VALUE = 12
          DATA_VALUE = 13
          LIST_VALUE = 14
          ENUM_VALUE = 15
          STRUCT_VALUE = 16
          INTERFACE_VALUE = 17
          OBJECT_VALUE = 18

          def which(struct_reader)
          end


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

          def get_text_value()
            get_text_field(0, "")
          end



          def get_enum_value()
            @reader.get_uint16(0)
          end



        end
      end
    end
  end
end
