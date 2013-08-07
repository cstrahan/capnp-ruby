module CapnProto
  module Schema
    module AnnotationNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_type()
          Type::Reader.new(@reader.get_struct_field(0, nil)
        end

        def get_targets_file()
          @reader.get_uint8(0) & 1 == 1
        end

        def get_targets_const()
          @reader.get_uint8(0) & 2 == 2
        end

        def get_targets_enum()
          @reader.get_uint8(0) & 4 == 4
        end

        def get_targets_enumerant()
          @reader.get_uint8(0) & 8 == 8
        end

        def get_targets_struct()
          @reader.get_uint8(0) & 16 == 16
        end

        def get_targets_field()
          @reader.get_uint8(0) & 32 == 32
        end

        def get_targets_union()
          @reader.get_uint8(0) & 64 == 64
        end

        def get_targets_interface()
          @reader.get_uint8(0) & 128 == 128
        end

        def get_targets_method()
          @reader.get_uint8(1) & 1 == 1
        end

        def get_targets_param()
          @reader.get_uint8(1) & 2 == 2
        end

        def get_targets_annotation()
          @reader.get_uint8(1) & 4 == 4
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end
    end
  end
end
