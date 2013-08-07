module CapnProto
  module Schema
    module EnumNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_enumerants()
          EnumNode::Enumerant::List::Reader.new(@reader.get_list_field(0, nil)
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Enumerant
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_name()
            get_text_field(0, "")
          end

          def get_code_order()
            @reader.get_uint16(0)
          end

          def get_annotations()
            Annotation::List::Reader.new(@reader.get_list_field(1, nil)
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
end
