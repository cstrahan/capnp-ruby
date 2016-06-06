require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieiraashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end
interface_schema = Calculator::Calculator.schema
evalMethod = Calculator::Calculator.method? 'evaluate'
client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)

class TestInterface < Minitest::Test

  def setup
    #none
  end

  def test_make_a_client
    interface_schema = Calculator::Calculator.schema
    client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)
    assert client
  end

  def test_make_a_request
    interface_schema = Calculator::Calculator.schema
    evalMethod = Calculator::Calculator.method? 'evaluate'
    client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)
    readMethod = Calculator::Calculator::Value.method? 'read'
    request = client.request_and_send(evalMethod,[['expression','literal',3]])
    sol = request.request_and_send('value',readMethod,[]).wait
    p "THE VALUE OF REQUEST IS #{sol['value']}"
    assert request
    assert sol
  end

  def test_set_parameter_of_request
    skip
    interface_schema = Calculator::Calculator.schema
    evalMethod = Calculator::Calculator.method? 'evaluate'
    client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)
    request = client.newRequest(evalMethod)
    assert request['expresion']['literal']= '123'
  end

  def test_send_request
    skip
    interface_schema = Calculator::Calculator.schema
    evalMethod = Calculator::Calculator.method? 'evaluate'
    client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)
    request = client.newRequest(evalMethod)
    response = request.send
    assert response
  end

  def test_response_is_correct
    skip
  end
end
