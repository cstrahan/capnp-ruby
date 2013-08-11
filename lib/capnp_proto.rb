require 'capn_proto/list'

module CapnProto
  module Data
    class Reader
      def initialize(pointer, size)
        @ptr  = pointer
        @size = size
      end

      def size
        @size
      end

      def [](index)
        @ptr.get_uchar(index)
      end

      def start
        @ptr
      end

      def slice(offset, length)
        fail "not implemented"
      end

      def ==(other)
        return false unless size == other.size
      end

    end
  end

  module Text
    class Reader < Data::Reader
      def to_s
      end
    end
  end
end
