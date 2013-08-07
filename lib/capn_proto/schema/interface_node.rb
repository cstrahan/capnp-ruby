module CapnProto
  module Schema
    module InterfaceNode
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

      module Method
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end


          def get_code_order()
            @reader.get_uint16(0)
          end


          def get_required_param_count()
            @reader.get_uint16(0)
          end


        end
        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end

        module Param
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
end
