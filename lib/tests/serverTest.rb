require "minitest/autorun"
require "./capn_proto.rb"

# to be runned from lib, ex: fvieiraashpool:~/capnp-ruby/lib$ ruby -Ilib:test tests/interfaceTest.rb
# only for dev purposes.

module Calculator extend CapnProto::SchemaLoader
  Calculator::load_schema('./tests/calculator.capnp')
end

class RubyServerReader
  def read(context)
    results_struct = context.getResults
    puts "getting results..OK"
    results_struct['value'] = 19.0
    puts "setting value...OK"
  end
end


class ServerTest < Minitest::Test
  def test_processRead
    interface = Calculator::Calculator::Value.schema
    server = CapnProto::CapabilityServer.new(RubyServerReader.new, interface, "*:4645")
    puts "listening on :4545"
    server.process
    puts "hello"
  end
end
