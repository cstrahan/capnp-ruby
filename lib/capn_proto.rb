require 'capn_proto/init'

module CapnProto
  ListNestedNodeReader.class_eval do
    include Enumerable
    def each
      (0...size).each do |n|
        yield self[n]
      end
    end
  end
end
