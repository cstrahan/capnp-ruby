module CapnProto
  module Schema
    module StructNode
      def self.bytes
        8
      end

      def self.pointers
        1
      end

      class Reader
        def initialize(reader)
          @reader = reader
        end

        def get_data_section_word_size()
          @builder.get_u_int16(0)
        end

        def get_pointer_section_size()
          @builder.get_u_int16(0)
        end


      end
      class Builder
        def initialize(builder)
          @builder = builder
        end
      end

      module Member
        def self.bytes
          8
        end

        def self.pointers
          3
        end

        class Reader
          def initialize(reader)
            @reader = reader
          end


          def get_ordinal()
            @builder.get_u_int16(0)
          end

          def get_code_order()
            @builder.get_u_int16(0)
          end


        end
        class Builder
          def initialize(builder)
            @builder = builder
          end
        end
      end

      module Field
        def self.bytes
          4
        end

        def self.pointers
          2
        end

        class Reader
          def initialize(reader)
            @reader = reader
          end

          def get_offset()
            @builder.get_u_int32(0)
          end


        end
        class Builder
          def initialize(builder)
            @builder = builder
          end
        end
      end

      module Union
        def self.bytes
          4
        end

        def self.pointers
          1
        end

        class Reader
          def initialize(reader)
            @reader = reader
          end

          def get_discriminant_offset()
            @builder.get_u_int32(0)
          end

        end
        class Builder
          def initialize(builder)
            @builder = builder
          end
        end
      end

      module Group
        def self.bytes
          0
        end

        def self.pointers
          1
        end

        class Reader
          def initialize(reader)
            @reader = reader
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
end
