require "minitest/autorun"
require "capn_proto"

# install the gem before running the tests

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('calculator.capnp')
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
