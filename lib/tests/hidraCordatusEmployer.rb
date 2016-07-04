require './capn_proto.rb'
require 'minitest/autorun'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class Employer < Minitest::Test
  def test_push_a_ton_of_tasks
    employer_schema =   Hydra::Employer.schema
    get_worker_method = Hydra::Employer.method! 'getWorker'
    put23method =       Hydra::Worker.method!   'put23'

    ezclient = CapnProto::EzRpcClient.new("127.0.0.1:1337",employer_schema)
    client = ezclient.client

    100.times do

      #set up the request
      request = client.request(get_worker_method)
      pipelinedRequest = request.send
      pipelinedRequest.get('worker').method = put23method
      pipelinedRequest.taskToProcess.dataint(0)

      #get the results
      results = pipelinedRequest.send.wait(ezclient)
      p results.taskProcessed.dataint
      p results.taskProcessed.madeBy

      assert results.taskProcessed.dataint == 23
    end
  end
end
