module CapnProto
  module Schema
    module Annotation
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
  end
end
