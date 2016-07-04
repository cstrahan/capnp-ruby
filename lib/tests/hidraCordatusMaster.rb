require './capn_proto.rb'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class WorkerServer < CapnProto::Server
  def initialize(i)
    @madeBy = "made by worker ##{i}"
    super(Hydra::Worker.schema, "")
    #as WorkerServer is used only to be passed around
    #by the Employer server the bind direction
    #should be ""
  end

  def put23(context)
    puts "put23 called"
    n = context.getParams.taskToProcess.dataint
    context.getResults.taskProcessed.dataint = n + 23
    context.getResults.taskProcessed.madeBy = @madeBy
    puts "put23 dispatched"
  end
end

class EmployerServer < CapnProto::Server
  def initialize(wp)
    @worker_pool = wp
    @currentWorker = 0
    super(Hydra::Employer.schema, "*:1337")
  end

  def get_a_Worker
    @currentWorker += 1
    @worker_pool[@currentWorker % @worker_pool.size]
  end

  def getWorker(context)
    puts "getWorker called"
    context.getResults.worker = get_a_Worker.raw
    puts "getWorker dispatched"
  end

end

workers = []
10.times do |i|
  workers << WorkerServer.new(i)
end




Thread.new do
  es = EmployerServer.new(workers)
  puts "serving EmployerServer on 1337..."
  es.run
end.join
