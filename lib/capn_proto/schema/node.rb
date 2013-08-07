module CapnProto
  module Schema
    module Node
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_id()
          @reader.get_uint64(0)
        end

        def get_display_name()
          get_text_field(0, "")
        end

        def get_display_name_prefix_length()
          @reader.get_uint32(0)
        end

        def get_scope_id()
          @reader.get_uint64(0)
        end

        def get_nested_nodes()
          Node::NestedNode::List::Reader.new(@reader.get_list_field(1, nil)
        end

        def get_annotations()
          Annotation::List::Reader.new(@reader.get_list_field(2, nil)
        end

        def get_body()
          Body::Reader.new(@reader.get_struct_field(16, nil)
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module NestedNode
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_name()
            get_text_field(0, "")
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

      module Body
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          FILE_NODE = 0
          STRUCT_NODE = 1
          ENUM_NODE = 2
          INTERFACE_NODE = 3
          CONST_NODE = 4
          ANNOTATION_NODE = 5

          def which(struct_reader)
          end

          def get_file_node()
            FileNode::Reader.new(@reader.get_struct_field(3, nil)
          end

          def get_struct_node()
            StructNode::Reader.new(@reader.get_struct_field(3, nil)
          end

          def get_enum_node()
            EnumNode::Reader.new(@reader.get_struct_field(3, nil)
          end

          def get_interface_node()
            InterfaceNode::Reader.new(@reader.get_struct_field(3, nil)
          end

          def get_const_node()
            ConstNode::Reader.new(@reader.get_struct_field(3, nil)
          end

          def get_annotation_node()
            AnnotationNode::Reader.new(@reader.get_struct_field(3, nil)
          end
        end
      end
    end
  end
end
