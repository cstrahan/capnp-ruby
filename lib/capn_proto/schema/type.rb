module CapnProto
  module Schema
    module Type
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

      module Body
        def get_enum_type()
          @reader.get_uint64(0)
        end
        def get_struct_type()
          @reader.get_uint64(0)
        end
        def get_interface_type()
          @reader.get_uint64(0)
        end
      end
    end
  end
end
