require './capn_proto.rb'

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class MasterServer
  def initialize
    @workers = []
    @currentWorker = 0
    @schema = Hydra::Worker.schema
  end

  def wantToWork(context)
    @workers << context.getParams['workerInterface']
    p @workers
    context.getResults['hired'] = true;
    puts "new worker hired"
  end

  def getWorker
    
    @currentWorker += 1
    w = @workers[ @currentWorker % @workers.size ]
    p w
    return w
  end
end

class EmployerServer
  def initialize(masterServer)
    @worker_pool = masterServer
  end

  def getWorker(context)
    puts "getWorker called"
    context.getResults['worker'] = @worker_pool.getWorker
    puts "getWorker dispatched"
  end

end

threads = []

master_interface = Hydra::Master.schema
employer_interface = Hydra::Employer.schema

ms = MasterServer.new
es = EmployerServer.new(ms)

threads << Thread.new do
  msserver = CapnProto::CapabilityServer.new(ms,master_interface,"*:3456")
  puts "serving MasterServer on 3456..."
  msserver.process
end

threads << Thread.new do
  esserver = CapnProto::CapabilityServer.new(es,employer_interface,"*:1337")
  puts "serving EmployerServer on 1337..."
  esserver.process
end

threads.map { |thread| thread.join }
