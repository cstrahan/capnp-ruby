module CapnProto
  module Schema
    module AnnotationNode
      def self.bytes
        2
      end

      def self.pointers
        1
      end

      class Reader
        def initialize(reader)
          @reader = reader
        end


        def get_targets_file()
          @builder.get_uchar(0) & 1 == 1
        end

        def get_targets_const()
          @builder.get_uchar(0) & 2 == 2
        end

        def get_targets_enum()
          @builder.get_uchar(0) & 4 == 4
        end

        def get_targets_enumerant()
          @builder.get_uchar(0) & 8 == 8
        end

        def get_targets_struct()
          @builder.get_uchar(0) & 16 == 16
        end

        def get_targets_field()
          @builder.get_uchar(0) & 32 == 32
        end

        def get_targets_union()
          @builder.get_uchar(0) & 64 == 64
        end

        def get_targets_interface()
          @builder.get_uchar(0) & 128 == 128
        end

        def get_targets_method()
          @builder.get_uchar(1) & 1 == 1
        end

        def get_targets_param()
          @builder.get_uchar(1) & 2 == 2
        end

        def get_targets_annotation()
          @builder.get_uchar(1) & 4 == 4
        end
      end
      class Builder
        def initialize(builder)
          @builder = builder
        end
      end
    end
  end
end
