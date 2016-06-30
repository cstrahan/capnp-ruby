require './capn_proto.rb'
require 'minitest/autorun'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class Employer < Minitest::Test
  def test_push_a_ton_of_tasks
    employer_schema = Hydra::Employer.schema
    client = CapnProto::Client.new("127.0.0.1:1337",employer_schema)

    put23method = Hydra::Worker.method? 'put23'
    100.times do

      #set up the request
      request = client.getWorkerRequest
      pipelinedRequest = request.send
      pipelinedRequest.get('worker').method = put23method
      pipelinedRequest.taskToProcess.dataint(0)


      #get the results
      results = pipelinedRequest.send.wait
      p results['taskRecv']['dataint']
      p results['taskRecv']['madeBy']


      assert results['taskRecv']['dataint'] == 23
    end
  end
end
