module CapnProto
  module Schema
    module StructNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_data_section_word_size()
          @reader.get_uint16(0)
        end

        def get_pointer_section_size()
          @reader.get_uint16(0)
        end


      end
      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Member
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end


          def get_ordinal()
            @reader.get_uint16(0)
          end

          def get_code_order()
            @reader.get_uint16(0)
          end


        end
        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end

        module Body
        end
      end

      module Field
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_offset()
            @reader.get_uint32(0)
          end


        end
        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end

      module Union
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_discriminant_offset()
            @reader.get_uint32(0)
          end

        end
        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end

      module Group
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
      end
    end
  end
end
