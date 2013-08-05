module CapnProto
  module Schema
    module InterfaceNode
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

      module Method
        def self.bytes
          4
        end

        def self.pointers
          4
        end

        class Reader
          def initialize(reader)
            @reader = reader
          end


          def get_code_order()
            @builder.get_u_int16(0)
          end


          def get_required_param_count()
            @builder.get_u_int16(0)
          end


        end
        class Builder
          def initialize(builder)
            @builder = builder
          end
        end

        module Param
          def self.bytes
            0
          end

          def self.pointers
            4
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
end
