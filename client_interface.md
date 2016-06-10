#using plain native extension objects
``` ruby
interface_schema = Calculator::Calculator.schema
evalMethod = Calculator::Calculator.method? 'evaluate'
readMethod = Calculator::Calculator::Value.method? 'read'

client = CapnProto::CapabilityClient.new('127.0.0.1:1337' , interface_schema)

request = client.request_and_send(evalMethod,[['expression','literal',3]])
sol = request.request_and_send('value',readMethod,[]).wait
p sol['value']
# => 3.0
```
for normal requests request_and_send only takes 2 arguments. the first arg is the
method to call and the second is a list of lists to set the parameters.   
expression.literal = 3 is translated to [['expression','literal',3]].   

pipeline Requests takes 3 arguments. the first being the interface returned from the
pipeline the second the method to call and the last one a list of lists to set
parameters.

#usage using Request
the request object is just a easier way to use the request_and_send method above.
``` ruby
interface_schema = Calculator::Calculator.schema
readMethod = Calculator::Calculator::Value.method? 'read'

client = CapnProto::Client.new('127.0.0.1:1337', interface_schema)
evalRequest = client.evaluateRequest
# this sets method to 'evaluate'
evalRequest.expression.literal(3) #set expression literal to 3
# [['expression','literal',3]]

pipelineRequest = evalRequest.send
#calls .request_and_send with evaluate and [['expression','literal',3]]

response = pipelineRequest.send('value',readMethod).wait
#calls .request_and_send with value, readMethod, [[]]
```
if you like to be more verbose
``` ruby
#you can change
evalRequest = client.evaluateRequest
# to
evalRequest = client.request
evalRequest.method = Calculator::Calculator.method? 'evaluate'

#or you can change
response = pipelineRequest.send('value',readMethod).wait
# to
pipelineRequest.get('value').method = Calculator::Calculator::Value.method? 'read'
#.get() sets the first argument of the pipelined version of request_and_send 
response = pipelineRequest.send.wait
