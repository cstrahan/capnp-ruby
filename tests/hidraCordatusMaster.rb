require 'capn_proto'

module Hydra extend CapnProto::SchemaLoader
  load_schema('hidraCordatus.capnp')
end

class WorkerServer < CapnProto::CapabilityServer
  def initialize(i)
    @madeBy = "made by worker ##{i}"
    super(Hydra::Worker.schema)
  end

  def put23(context)
    puts "put23 called"
    n = context.getParams.taskToProcess.dataint
    context.getResults.taskProcessed.dataint = n + 23
    context.getResults.taskProcessed.madeBy = @madeBy
    puts "put23 dispatched"
  end
end

class EmployerServer < CapnProto::CapabilityServer
  def initialize(wp)
    @worker_pool = wp
    @currentWorker = 0
    super(Hydra::Employer.schema)
  end

  def get_a_Worker
    @currentWorker += 1
    @worker_pool[@currentWorker % @worker_pool.size]
  end

  def getWorker(context)
    puts "getWorker called"
    context.getResults.worker = get_a_Worker
    puts "getWorker dispatched"
  end

end


workers = []
10.times do |i|
  workers << WorkerServer.new(i)
end


e = CapnProto::EzRpcServer.new(EmployerServer.new(workers), "*:1337")
puts "serving EmployerServer on 1337..."
e.run
