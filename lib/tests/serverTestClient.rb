require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieiraashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end

class ServerTestClient < Minitest::Test
  def test_doRead
    readMethod = Calculator::Calculator::Value.method? 'read'
    schema = Calculator::Calculator::Value.schema
    ezclient = CapnProto::EzRpcClient.new("127.0.0.1:4645", schema)
    client = ezclient.client
    100.times do
      results = client.request(readMethod).send.wait(ezclient)
      p results['value']
      assert results['value'] == 19
    end
  end
end
