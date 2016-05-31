require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieira@ashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end

class TestInterface < Minitest::Test
  @interface_schema
  @evalMethod
  @client
  @request
  @response

  def setup
    #none
  end

  def test_Interface_got_loaded
    @interface_schema = Calculator::Calculator.schema
    assert @interface_schema
  end

  def test_Interface_method_works
    assert Calculator::Calculator.method?('evaluate')
    @evalMethod = Calculator::Calculator.method? 'evaluate'
  end


  def test_make_a_client
    @interface_schema = Calculator::Calculator.schema
    @client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , @interface_schema)
    assert @client
  end

  def test_make_a_request
    @request = @client.newRequest(@evalMethod)
    assert @request
  end

  def test_set_parameter_of_request
    assert @request['expresion']['literal']= '123'
  end

  def test_send_request
    @response = @request.send
    assert @response
  end

  def test_response_is_correct
    skip
  end
end
