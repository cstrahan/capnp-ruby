require './capn_proto.rb'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class WorkerServer
  def work(context)
    context.getResults['taskProcessed']['dataint'] = 23
    context.getResults['taskProcessed']['madeBy'] = "made by worker"
  end
end


#make a request to master to be a worker
master_interface = Hydra::Master.schema
worker_interface = Hydra::Worker.schema
client = CapnProto::Client.new("127.0.0.1:3456",master_interface)

hired = false
while !hired
  request = client.wantToWorkRequest
  #bug found. WIP
  #source of the bug: RemotePromise::setParam in remote_promise.cc
  request.ipOfWorker("127.0.0.1:5555")
  #bug found. WIP
  hired = request.send.wait['hired']
  puts "hired = #{hired}"
  sleep(2)
end

thread = Thread.new do
  workerServer = CapnProto::CapabilityServer.new(workerServer.new,worker_interface,"*:5555")
  puts "listening for work on 5555"
  workerServer.process
end

thread.join
