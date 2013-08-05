module CapnProto
  module Schema
    module FileNode
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

      module Import
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

          def get_id()
            @builder.get_u_int64(0)
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
