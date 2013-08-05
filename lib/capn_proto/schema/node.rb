module CapnProto
  module Schema
    module Node
      def self.bytes
        24
      end

      def self.pointers
        4
      end

      class Reader
        def initialize(reader)
          @reader = reader
        end

        def get_id()
          @builder.get_u_int64(0)
        end


        def get_display_name_prefix_length()
          @builder.get_u_int32(0)
        end




      end
      class Builder
        def initialize(builder)
          @builder = builder
        end
      end

      module NestedNode
        def self.bytes
          8
        end

        def self.pointers
          1
        end

        class Reader
          def initialize(reader)
            @reader = reader
          end


          def get_id()
            @builder.get_u_int64(0)
          end
        end
        class Builder
          def initialize(builder)
            @builder = builder
          end
        end
      end
    end
  end
end
