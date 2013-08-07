module CapnProto
  module Schema
    module StructNode
      class Reader
        def initialize(struct_reader)
          @reader = struct_reader
        end

        def get_data_section_word_size()
          @reader.get_uint16(0)
        end

        def get_pointer_section_size()
          @reader.get_uint16(0)
        end

        def get_preferred_list_encoding()
          @reader.get_enum_field(0
        end

        def get_members()
          StructNode::Member::List::Reader.new(@reader.get_list_field(0, nil)
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
            get_text_field(0, "")
          end

          def get_ordinal()
            @reader.get_uint16(0)
          end

          def get_code_order()
            @reader.get_uint16(0)
          end

          def get_annotations()
            Annotation::List::Reader.new(@reader.get_list_field(1, nil)
          end

          def get_body()
            Body::Reader.new(@reader.get_struct_field(4, nil)
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

            def which(struct_reader)
            end

            def get_field_member()
              StructNode::Field::Reader.new(@reader.get_struct_field(2, nil)
            end

            def get_union_member()
              StructNode::Union::Reader.new(@reader.get_struct_field(2, nil)
            end

            def get_group_member()
              StructNode::Group::Reader.new(@reader.get_struct_field(2, nil)
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
            Type::Reader.new(@reader.get_struct_field(0, nil)
          end

          def get_default_value()
            Value::Reader.new(@reader.get_struct_field(1, nil)
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
            StructNode::Member::List::Reader.new(@reader.get_list_field(0, nil)
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
            StructNode::Member::List::Reader.new(@reader.get_list_field(0, nil)
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
