module CapnProto
  module Schema
    module CodeGeneratorRequest
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
