module CapnProto
  module Schema
    module InterfaceNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_methods()
          InterfaceNode::Method::List::Reader.new(@reader.get_list_field(0, nil)
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Method
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

          def get_params()
            InterfaceNode::Method::Param::List::Reader.new(@reader.get_list_field(1, nil)
          end

          def get_required_param_count()
            @reader.get_uint16(0)
          end

          def get_return_type()
            Type::Reader.new(@reader.get_struct_field(2, nil)
          end

          def get_annotations()
            Annotation::List::Reader.new(@reader.get_list_field(3, nil)
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end

        module Param
          class Reader
            def initialize(struct_reader)
              @reader = struct_reader
            end

            def get_name()
              get_text_field(0, "")
            end

            def get_type()
              Type::Reader.new(@reader.get_struct_field(1, nil)
            end

            def get_default_value()
              Value::Reader.new(@reader.get_struct_field(2, nil)
            end

            def get_annotations()
              Annotation::List::Reader.new(@reader.get_list_field(3, nil)
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
end
