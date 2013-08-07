module CapnProto
  module Schema
    module ConstNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_type()
          Type::Reader.new(@reader.get_struct_field(0, nil)
        end

        def get_value()
          Value::Reader.new(@reader.get_struct_field(1, nil)
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
