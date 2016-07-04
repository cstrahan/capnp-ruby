[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/cstrahan/capnp-ruby/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

![Cap'n Proto][logo]

# ON DEVELOPMENT
i changed some configs and parameters in order to develop this binding more easily.
Don't try to use this for production. And if you want to contribute you will have to change some things.
In this state this binding shouldn't be gemified. Wait till i finish working on the RPC and i will gemify this and clean my 'mess'.

# Ruby Edition

This here is a [Ruby][ruby] wrapper for the official C++ implementation of [Cap'n Proto][capnp].

[![Build Status][travis-badge]][travis-link]

# Installing

First [install libcapnp][libcapnp-install], then install the gem:

```bash
gem install capn_proto --pre
```

The native extension for this gem requires a C++ compiler with C++11 features, so use the same C++ compiler and flags that you used to compile libcapnp (e.g. `CXX` and `CXXFLAGS`). As an OSX user, having followed the [instructions for installing libcapnp on OSX][libcapnp-install], the correct incantation is as follows:

```bash
CXX=$HOME/clang-3.2/bin/clang++ gem install capn_proto --pre
```



# Structs Example

```ruby
require 'capn_proto'

module AddressBook extend CapnProto::SchemaLoader
  load_schema("addressbook.capnp")
end

def write_address_book(file)
  addresses = AddressBook::AddressBook.new_message
  people = addresses.initPeople(2)

  alice = people[0]
  alice.id = 123
  alice.name = 'Alice'
  alice.email = 'alice@example.com'
  alice_phones = alice.initPhones(1)
  alice_phones[0].number = "555-1212"
  alice_phones[0].type = 'mobile'
  alice.employment.school = "MIT"

  bob = people[1]
  bob.id = 456
  bob.name = 'Bob'
  bob.email = 'bob@example.com'
  bob_phones = bob.initPhones(2)
  bob_phones[0].number = "555-4567"
  bob_phones[0].type = 'home'
  bob_phones[1].number = "555-7654"
  bob_phones[1].type = 'work'
  bob.employment.unemployed = nil

  addresses.write(file)
end

def print_address_book(file)
  addresses = AddressBook::AddressBook.read_from(file)

  addresses.people.each do |person|
    puts "#{person.name} : #{person.email}"

    person.phones.each do |phone|
      puts "#{phone.type} : #{phone.number}"
    end

    if person.employment.unemployed?
      puts "unemployed"
    if person.employment.employer?
      puts "employer: #{person.employment.employer}"
    if person.employment.school?
      puts "student at: #{person.employment.school}"
    if person.employment.selfEmployed?
      puts "self employed"
    end
  end
end

if __FILE__ == $0
  file = File.open("addressbook.bin", "wb")
  write_address_book(file)

  file = File.open("addressbook.bin", "rb")
  print_address_book(file)
end
```
# RPC Client Example    
note, both the client example and the server example can be found in lib/tests as a minitest.
```ruby

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

employer_schema =   Hydra::Employer.schema
get_worker_method = Hydra::Employer.method! 'getWorker'
put23method =       Hydra::Worker.method!   'put23'

ezclient = CapnProto::EzRpcClient.new("127.0.0.1:1337",employer_schema)
client = ezclient.client

# set up the request
# note that there is truly 2 requests, one to get the worker interface, other to call put23
request = client.request(get_worker_method)
pipelinedRequest = request.send
# end of request to get the worker interface, begin of request put23
pipelinedRequest.get('worker').method = put23method
pipelinedRequest.taskToProcess.dataint(0)
# end of request put23

results = pipelinedRequest.send.wait(ezclient)
# note that ezclient is used as a waitscope
puts results.taskProcessed.dataint
puts results.taskProcessed.madeBy
```

# RPC server Example
CapnProto::Server is a hybrid between EzRpcServer and DynamicCapability::Server
```ruby

module Hydra extend CapnProto::SchemaLoader
  load_schema('./tests/hidraCordatus.capnp')
end

class WorkerServer < CapnProto::Server
  def initialize(i)
    @madeBy = "made by worker ##{i}"
    super(Hydra::Worker.schema, "")
    # super takes the InterfaceSchema served and a bind direction
    # as WorkerServer is used only to be passed around
    # by the Employer server the bind direction
    # should be ""
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
```
the results of running the server/client pair is :
```
23
"made by worker #1"
23
"made by worker #2"
23
"made by worker #3"
23
...
```

# Status

What's implemented:
- Schema parsing/loading
- Message reading
  - From byte string
  - From file descriptor
- Message writing
  - To byte string
  - To file descriptor
- RPC
  - loading InterfaceSchema and InterfaceSchema::Method
  - RPC client
  - RPC server

What's to come:
- More reading/writing mechanisms:
  - Packing/unpacking
- Extensive test coverage
- Proper support for [JRuby][jruby]
- A best RPC
  - no more exceptions at control-c [WIP]

[logo]: https://raw.github.com/cstrahan/capnp-ruby/master/media/captain_proto_small.png "Cap'n Proto"
[ruby]: http://www.ruby-lang.org/ "Ruby"
[capnp]: http://kentonv.github.io/capnproto/ "Cap'n Proto"
[jruby]: http://jruby.org/ "JRuby"
[libcapnp-install]: http://kentonv.github.io/capnproto/install.html "Installing Cap'n Proto"
[mit-license]: http://opensource.org/licenses/MIT "MIT License"

[travis-link]: https://travis-ci.org/cstrahan/capnp-ruby
[travis-badge]: https://travis-ci.org/cstrahan/capnp-ruby.png?branch=master
