module CapnProto
  module Schema
    module Type
      def self.bytes
        16
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
