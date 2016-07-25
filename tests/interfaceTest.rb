require "minitest/autorun"
require "capn_proto"

# to be runned from lib, ex: fvieira@ashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('calculator.capnp')
end

class TestInterface < Minitest::Test
  def setup
    #none
  end

  def test_Interface_got_loaded
    assert Calculator::Calculator.schema
  end

  def test_Interface_method_works
    assert Calculator::Calculator.method?('evaluate')
  end

  def test_Interface_method_returns_false
    assert_equal(Calculator::Calculator.method?('garbage') , false)
  end

  def test_nested_interface_works
    assert(Calculator::Calculator::Function.schema)
  end

  def test_nested_interface_method_works
    assert Calculator::Calculator::Function.method?('call')
  end
end
