require './capn_proto.rb'
require 'minitest/autorun'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class Employer < Minitest::Test
  def test_push_a_ton_of_tasks
    employer_schema = Hydra::Employer.schema
    get_worker_method = Hydra::Employer.method? 'getWorker'
    ezclient = CapnProto::EzRpcClient.new("127.0.0.1:1337",employer_schema)
    client = ezclient.client
    put23method = Hydra::Worker.method? 'put23'

    100.times do

      #set up the request
      request = client.request(get_worker_method)
      workerCap = request.send.wait(ezclient)['worker']
      p workerCap
      puts "get a capability worker"
      request = workerCap.request(put23method)
      request.taskToProcess.dataint(0)
      puts 'request setted. ready to fire'
      puts 'firing'
      results = request.send.wait(ezclient)
      puts 'fired'


      #get the results
      results = pipelinedRequest.send.wait(ezclient)
      p results['taskRecv']['dataint']
      p results['taskRecv']['madeBy']


      assert results['taskRecv']['dataint'] == 23
    end
  end
end
