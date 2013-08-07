module CapnProto
  module Schema
    module Node
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_id()
          @reader.get_uint64(0)
        end


        def get_display_name_prefix_length()
          @reader.get_uint32(0)
        end




      end
      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module NestedNode
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end


          def get_id()
            @reader.get_uint64(0)
          end
        end
        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end

      module Body
      end
    end
  end
end
