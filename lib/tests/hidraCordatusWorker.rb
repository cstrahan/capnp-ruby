require './capn_proto.rb'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class WorkerServer
  def put23(context)
    puts "put23 called"
    context.getResults['taskProcessed']['dataint'] = 23
    context.getResults['taskProcessed']['madeBy'] = "made by worker"
    puts "put23 dispatched"
  end
end


#make a request to master to be a worker
master_interface = Hydra::Master.schema
worker_interface = Hydra::Worker.schema
wantToWork_method = Hydra::Master.method? 'wantToWork'
ezclient = CapnProto::EzRpcClient.new("127.0.0.1:3456",master_interface)
client = ezclient.client

workerServer = CapnProto::CapabilityServer.new(WorkerServer.new,worker_interface,"*:3434")

hired = false
while !hired
  p workerServer
  request = client.request(wantToWork_method)
  request.workerInterface(workerServer)
  p request
  result = request.send.wait(ezclient)
  hired = result['hired']
  puts "hired = #{hired}"
end


puts "listening for work on 3434"
workerServer.process
