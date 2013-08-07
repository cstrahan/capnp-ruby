module CapnProto
  module Schema
    module CodeGeneratorRequest
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_nodes()
          Node::List::Reader.new(@reader.get_list_field(0, nil)
        end

        def get_requested_files()
          Int64::List::Reader.new(@reader.get_list_field(1, nil)
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
