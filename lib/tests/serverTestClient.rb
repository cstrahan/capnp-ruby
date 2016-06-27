require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieiraashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end

class ServerTestClient < Minitest::Test
  def test_doRead
    schema = Calculator::Calculator::Value.schema
    client = CapnProto::Client.new("127.0.0.1:4645", schema)
    100.times do
      request = client.readRequest
      results = request.send.wait
      p results['value']
    end
  end
end
