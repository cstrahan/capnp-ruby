module CapnProto
  module Schema
    module EnumNode
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

      module Enumerant
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
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
      end
    end
  end
end
