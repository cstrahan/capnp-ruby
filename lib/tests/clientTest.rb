require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieira@ashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end

class TestInterface < Minitest::Test

  def setup
    #none
  end

  def test_make_a_client
    @interface_schema = Calculator::Calculator.schema
    @client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , @interface_schema)
    assert @client
  end

  def test_make_a_request
    @interface_schema = Calculator::Calculator.schema
    @evalMethod = Calculator::Calculator.method? 'evaluate'
    @client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , @interface_schema)
    @request = @client.newRequest(@client,@evalMethod)
    assert @request
  end

  def test_set_parameter_of_request
    @interface_schema = Calculator::Calculator.schema
    @evalMethod = Calculator::Calculator.method? 'evaluate'
    @client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , @interface_schema)
    @request = @client.newRequest(@evalMethod)
    assert @request['expresion']['literal']= '123'
  end

  def test_send_request
    @interface_schema = Calculator::Calculator.schema
    @evalMethod = Calculator::Calculator.method? 'evaluate'
    @client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , @interface_schema)
    @request = @client.newRequest(@evalMethod)
    @response = @request.send
    assert @response
  end

  def test_response_is_correct
    skip
  end
end
