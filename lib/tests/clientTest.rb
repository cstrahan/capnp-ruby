require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieiraashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end

class ClientTest < Minitest::Test

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
    readMethod = Calculator::Calculator::Value.method? 'read'

    client = CapnProto::Client.new('127.0.0.1:1337', interface_schema)
    10.times do #to test if the binding can handle multiple requests
      evalRequest = client.evaluateRequest
      evalRequest.expression.literal(3) #set expression literal to 3
      pipelineRequest = evalRequest.send
      pipelineRequest.get('value').method = readMethod
      response = pipelineRequest.send().wait
      p "THE VALUE OF REQUEST IS #{response['value']}"
      assert response['value'] == 3
    end
  end

  def test_make_a_request_using_short_interface
    interface_schema = Calculator::Calculator.schema
    readMethod = Calculator::Calculator::Value.method? 'read'

    client = CapnProto::Client.new('127.0.0.1:1337', interface_schema)
    evalRequest = client.evaluateRequest
    evalRequest.expression.literal(3) #set expression literal to 3
    pipelineRequest = evalRequest.send

    response = pipelineRequest.send('value',readMethod).wait
    p "THE VALUE OF REQUEST IS #{response['value']}"
    assert response['value'] == 3
  end
end
