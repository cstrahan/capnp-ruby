module CapnProto
  module PrimitiveList
    class Reader
      def initialize(list_reader)
        @reader = list_reader
      end

      def size
        @reader.size
      end
    end
  end
end
