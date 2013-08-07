module CapnProto
  module Schema
    module Type
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

          VOID_TYPE = 0
          BOOL_TYPE = 1
          INT8_TYPE = 2
          INT16_TYPE = 3
          INT32_TYPE = 4
          INT64_TYPE = 5
          UINT8_TYPE = 6
          UINT16_TYPE = 7
          UINT32_TYPE = 8
          UINT64_TYPE = 9
          FLOAT32_TYPE = 10
          FLOAT64_TYPE = 11
          TEXT_TYPE = 12
          DATA_TYPE = 13
          LIST_TYPE = 14
          ENUM_TYPE = 15
          STRUCT_TYPE = 16
          INTERFACE_TYPE = 17
          OBJECT_TYPE = 18

          def which(struct_reader)
          end















          def get_list_type()
            Type::Reader.new(@reader.get_struct_field(0, nil)
          end

          def get_enum_type()
            @reader.get_uint64(0)
          end

          def get_struct_type()
            @reader.get_uint64(0)
          end

          def get_interface_type()
            @reader.get_uint64(0)
          end

        end
      end
    end
  end
end
