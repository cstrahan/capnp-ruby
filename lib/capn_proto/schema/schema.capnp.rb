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
          @reader.get_text_field(0, "")
        end

        def get_display_name_prefix_length()
          @reader.get_uint32(20)
        end

        def get_scope_id()
          @reader.get_uint64(8)
        end

        def get_nested_nodes()
          Node::NestedNode::List::Reader.new(@reader.get_list_field(1, nil))
        end

        def get_annotations()
          Annotation::List::Reader.new(@reader.get_list_field(2, nil))
        end

        def get_body()
          Body::Reader.new(@reader)
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
            @reader.get_text_field(0, "")
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

          def which
            @reader.get_uin16(16)
          end

          def get_file_node()
            FileNode::Reader.new(@reader.get_struct_field(3, nil))
          end

          def get_struct_node()
            StructNode::Reader.new(@reader.get_struct_field(3, nil))
          end

          def get_enum_node()
            EnumNode::Reader.new(@reader.get_struct_field(3, nil))
          end

          def get_interface_node()
            InterfaceNode::Reader.new(@reader.get_struct_field(3, nil))
          end

          def get_const_node()
            ConstNode::Reader.new(@reader.get_struct_field(3, nil))
          end

          def get_annotation_node()
            AnnotationNode::Reader.new(@reader.get_struct_field(3, nil))
          end
        end
      end
    end
    module Type
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_body()
          Body::Reader.new(@reader)
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Body
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          VOID_TYPE = 0
          BOOL_TYPE = 1
          INT8_TYPE = 2
          INT16_TYPE = 3
          INT32_TYPE = 4
          INT64_TYPE = 5
          UINT8_TYPE = 6
          UINT16_TYPE = 7
          UINT32_TYPE = 8
          UINT64_TYPE = 9
          FLOAT32_TYPE = 10
          FLOAT64_TYPE = 11
          TEXT_TYPE = 12
          DATA_TYPE = 13
          LIST_TYPE = 14
          ENUM_TYPE = 15
          STRUCT_TYPE = 16
          INTERFACE_TYPE = 17
          OBJECT_TYPE = 18

          def which
            @reader.get_uin16(0)
          end

          def get_void_type()
            nil
          end

          def get_bool_type()
            nil
          end

          def get_int8_type()
            nil
          end

          def get_int16_type()
            nil
          end

          def get_int32_type()
            nil
          end

          def get_int64_type()
            nil
          end

          def get_uint8_type()
            nil
          end

          def get_uint16_type()
            nil
          end

          def get_uint32_type()
            nil
          end

          def get_uint64_type()
            nil
          end

          def get_float32_type()
            nil
          end

          def get_float64_type()
            nil
          end

          def get_text_type()
            nil
          end

          def get_data_type()
            nil
          end

          def get_list_type()
            Type::Reader.new(@reader.get_struct_field(0, nil))
          end

          def get_enum_type()
            @reader.get_uint64(8)
          end

          def get_struct_type()
            @reader.get_uint64(8)
          end

          def get_interface_type()
            @reader.get_uint64(8)
          end

          def get_object_type()
            nil
          end
        end
      end
    end
    module Value
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_body()
          Body::Reader.new(@reader)
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Body
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          VOID_VALUE = 9
          BOOL_VALUE = 1
          INT8_VALUE = 2
          INT16_VALUE = 3
          INT32_VALUE = 4
          INT64_VALUE = 5
          UINT8_VALUE = 6
          UINT16_VALUE = 7
          UINT32_VALUE = 8
          UINT64_VALUE = 0
          FLOAT32_VALUE = 10
          FLOAT64_VALUE = 11
          TEXT_VALUE = 12
          DATA_VALUE = 13
          LIST_VALUE = 14
          ENUM_VALUE = 15
          STRUCT_VALUE = 16
          INTERFACE_VALUE = 17
          OBJECT_VALUE = 18

          def which
            @reader.get_uin16(0)
          end

          def get_void_value()
            nil
          end

          def get_bool_value()
            @reader.get_uint8(8) & 1 == 1
          end

          def get_int8_value()
            @reader.get_int8(8)
          end

          def get_int16_value()
            @reader.get_int16(8)
          end

          def get_int32_value()
            @reader.get_int32(8)
          end

          def get_int64_value()
            @reader.get_int64(8)
          end

          def get_uint8_value()
            @reader.get_uint8(8)
          end

          def get_uint16_value()
            @reader.get_uint16(8)
          end

          def get_uint32_value()
            @reader.get_uint32(8)
          end

          def get_uint64_value()
            @reader.get_uint64(8)
          end

          def get_float32_value()
            @reader.get_float32(8)
          end

          def get_float64_value()
            @reader.get_float64(8)
          end

          def get_text_value()
            @reader.get_text_field(0, "")
          end



          def get_enum_value()
            @reader.get_uint16(8)
          end


          def get_interface_value()
            nil
          end

        end
      end
    end
    module Annotation
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_id()
          @reader.get_uint64(0)
        end

        def get_value()
          Value::Reader.new(@reader.get_struct_field(0, nil))
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end
    end
    module FileNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_imports()
          FileNode::Import::List::Reader.new(@reader.get_list_field(0, nil))
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Import
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_id()
            @reader.get_uint64(0)
          end

          def get_name()
            @reader.get_text_field(0, "")
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end
    end
    module ElementSize
      EMPTY  = 0
      BIT  = 1
      BYTE  = 2
      TWO_BYTES  = 3
      FOUR_BYTES  = 4
      EIGHT_BYTES  = 5
      POINTER  = 6
      INLINE_COMPOSITE  = 7
    end
    module StructNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_data_section_word_size()
          @reader.get_uint16(0)
        end

        def get_pointer_section_size()
          @reader.get_uint16(2)
        end

        def get_preferred_list_encoding()
          @reader.get_uint16(4)
        end

        def get_members()
          StructNode::Member::List::Reader.new(@reader.get_list_field(0, nil))
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end

      module Member
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_name()
            @reader.get_text_field(0, "")
          end

          def get_ordinal()
            @reader.get_uint16(0)
          end

          def get_code_order()
            @reader.get_uint16(2)
          end

          def get_annotations()
            Annotation::List::Reader.new(@reader.get_list_field(1, nil))
          end

          def get_body()
            Body::Reader.new(@reader)
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end

        module Body
          class Reader
            def initialize(struct_reader)
              @reader = struct_reader
            end

            FIELD_MEMBER = 0
            UNION_MEMBER = 1
            GROUP_MEMBER = 2

            def which
              @reader.get_uin16(4)
            end

            def get_field_member()
              StructNode::Field::Reader.new(@reader.get_struct_field(2, nil))
            end

            def get_union_member()
              StructNode::Union::Reader.new(@reader.get_struct_field(2, nil))
            end

            def get_group_member()
              StructNode::Group::Reader.new(@reader.get_struct_field(2, nil))
            end
          end
        end
      end

      module Field
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_offset()
            @reader.get_uint32(0)
          end

          def get_type()
            Type::Reader.new(@reader.get_struct_field(0, nil))
          end

          def get_default_value()
            Value::Reader.new(@reader.get_struct_field(1, nil))
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end

      module Union
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_discriminant_offset()
            @reader.get_uint32(0)
          end

          def get_members()
            StructNode::Member::List::Reader.new(@reader.get_list_field(0, nil))
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end

      module Group
        class Reader
          def initialize(struct_reader)
            @reader = struct_reader
          end

          def get_members()
            StructNode::Member::List::Reader.new(@reader.get_list_field(0, nil))
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end
    end
    module EnumNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_enumerants()
          EnumNode::Enumerant::List::Reader.new(@reader.get_list_field(0, nil))
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
            @reader.get_text_field(0, "")
          end

          def get_code_order()
            @reader.get_uint16(0)
          end

          def get_annotations()
            Annotation::List::Reader.new(@reader.get_list_field(1, nil))
          end
        end

        class Builder
          def initialize(struct_builder)
            @builder = struct_builder
          end
        end
      end
    end
    module InterfaceNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_methods()
          InterfaceNode::Method::List::Reader.new(@reader.get_list_field(0, nil))
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
            @reader.get_text_field(0, "")
          end

          def get_code_order()
            @reader.get_uint16(0)
          end

          def get_params()
            InterfaceNode::Method::Param::List::Reader.new(@reader.get_list_field(1, nil))
          end

          def get_required_param_count()
            @reader.get_uint16(2)
          end

          def get_return_type()
            Type::Reader.new(@reader.get_struct_field(2, nil))
          end

          def get_annotations()
            Annotation::List::Reader.new(@reader.get_list_field(3, nil))
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
              @reader.get_text_field(0, "")
            end

            def get_type()
              Type::Reader.new(@reader.get_struct_field(1, nil))
            end

            def get_default_value()
              Value::Reader.new(@reader.get_struct_field(2, nil))
            end

            def get_annotations()
              Annotation::List::Reader.new(@reader.get_list_field(3, nil))
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
    module ConstNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_type()
          Type::Reader.new(@reader.get_struct_field(0, nil))
        end

        def get_value()
          Value::Reader.new(@reader.get_struct_field(1, nil))
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end
    end
    module AnnotationNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_type()
          Type::Reader.new(@reader.get_struct_field(0, nil))
        end

        def get_targets_file()
          @reader.get_uint8(0) & 1 == 1
        end

        def get_targets_const()
          @reader.get_uint8(0) & 2 == 2
        end

        def get_targets_enum()
          @reader.get_uint8(0) & 4 == 4
        end

        def get_targets_enumerant()
          @reader.get_uint8(0) & 8 == 8
        end

        def get_targets_struct()
          @reader.get_uint8(0) & 16 == 16
        end

        def get_targets_field()
          @reader.get_uint8(0) & 32 == 32
        end

        def get_targets_union()
          @reader.get_uint8(0) & 64 == 64
        end

        def get_targets_interface()
          @reader.get_uint8(0) & 128 == 128
        end

        def get_targets_method()
          @reader.get_uint8(1) & 1 == 1
        end

        def get_targets_param()
          @reader.get_uint8(1) & 2 == 2
        end

        def get_targets_annotation()
          @reader.get_uint8(1) & 4 == 4
        end
      end

      class Builder
        def initialize(struct_builder)
          @builder = struct_builder
        end
      end
    end
    module CodeGeneratorRequest
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_nodes()
          Node::List::Reader.new(@reader.get_list_field(0, nil))
        end

        def get_requested_files()
          Int64::List::Reader.new(@reader.get_list_field(1, nil))
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
