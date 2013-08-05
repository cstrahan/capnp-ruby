module CapnProto
  module Schema
    module EnumNode
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

      module Enumerant
        def self.bytes
          2
        end

        def self.pointers
          2
        end

        class Reader
          def initialize(reader)
            @reader = reader
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
    end
  end
end
