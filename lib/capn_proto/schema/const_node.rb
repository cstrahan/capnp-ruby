module CapnProto
  module Schema
    module ConstNode
      def self.bytes
        0
      end

      def self.pointers
        2
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
