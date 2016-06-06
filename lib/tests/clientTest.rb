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

  def test_make_a_request_using_hard_interface
    interface_schema = Calculator::Calculator.schema
    evalMethod = Calculator::Calculator.method? 'evaluate'
    client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)
    readMethod = Calculator::Calculator::Value.method? 'read'
    request = client.request_and_send(evalMethod,[['expression','literal',3]])
    sol = request.request_and_send('value',readMethod,[]).wait
    p "THE VALUE OF REQUEST IS #{sol['value']}"
    assert request
    assert sol['value'] == 3
  end

  def test_make_a_request_using_good_interface
    interface_schema = Calculator::Calculator.schema
    evalMethod = Calculator::Calculator.method? 'evaluate'
    readMethod = Calculator::Calculator::Value.method? 'read'

    client = CapnProto::Client.new('127.0.0.1:1337', interface_schema)
    evalRequest = client.request
    evalRequest.expression.literal(3) #set expression literal to 3
    pipelineRequest = evalRequest.send(evalMethod)
    response = pipelineRequest.send('value',readMethod).wait
    p "THE VALUE OF REQUEST IS #{response['value']}"
    assert response['value'] == 3

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
