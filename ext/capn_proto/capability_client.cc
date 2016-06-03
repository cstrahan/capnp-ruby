#include "ruby_capn_proto.h"
#include "capability_client.h"
#include "interface_schema.h"
#include "interface_method.h"
#include "dynamic_value_builder.h"
#include "dynamic_struct_builder.h"
#include "remote_promise.h"
#include "class_builder.h"
#include "util.h"

namespace ruby_capn_proto {
  using WrappedType = capnp::EzRpcClient;
  VALUE CapabilityClient::Class;

  void CapabilityClient::Init() {
    // this have to be an object
    ClassBuilder("CapabilityClient", rb_cObject).
      defineAlloc(&alloc).
      defineMethod("request_and_send" , &request_and_send).
      defineMethod("initialize" , &create).
      store(&Class);
  }

  void CapabilityClient::free(WrappedType* p) {
    // todo fix
    printf("Free has been called\n" );
  }

  VALUE CapabilityClient::alloc(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, free, ruby_xmalloc(sizeof(WrappedType)));
  }

  WrappedType* CapabilityClient::unwrap(VALUE self) {
    WrappedType* p;
    Data_Get_Struct(self, WrappedType, p);
    return p;
  }

  VALUE CapabilityClient::create(VALUE self, VALUE dir, VALUE interschema) {

    WrappedType* rb_self = unwrap(self);
    new (rb_self) capnp::EzRpcClient(Util::toString(dir));

    //store the InterfaceSchema
    rb_iv_set(self,"schema",interschema);

    return self;
  }

  capnp::DynamicCapability::Client CapabilityClient::make_dynamic(VALUE self){
    VALUE rb_schema = rb_iv_get(self,"schema");

    capnp::Capability::Client capclient = unwrap(self)->getMain();
    return capclient.castAs<capnp::DynamicCapability>(*InterfaceSchema::unwrap(rb_schema));
  }

  VALUE CapabilityClient::request_and_send(VALUE self , VALUE rb_method , VALUE arrays){
    //have, a method and a list of lists each list containing a value to set
    //return, a remote promise.
    // Data must be a array of arrays
    // arrays must be like ['expression','literal','3']
    // this will set in the expression param literal = 3
    auto* method = InterfaceMethod::unwrap(rb_method);
    auto  request = make_dynamic(self).newRequest(*method);

    VALUE mainIter = rb_ary_pop(arrays); // mainIter is now a array
    while(mainIter != Qnil ){

      VALUE val = rb_ary_pop(mainIter);    // value to assign
      VALUE last = rb_ary_pop(mainIter);   // name of the field to assign to val
      VALUE temp = rb_ary_shift(mainIter); // just a to iterate

      capnp::DynamicStruct::Builder builder = NULL;

      // follow the nodes indicated by the array
      while( temp != Qnil && temp != last){
        builder = *DynamicStructBuilder::unwrap(DynamicValueBuilder::to_ruby(request.get(Util::toString(temp)),Qnil));
        temp = rb_ary_shift(mainIter);
      }

      // when arrived to last node make the assignation
      VALUE rb_struct = DynamicStructBuilder::create(builder,Qnil,Qfalse);
      DynamicStructBuilder::set(rb_struct,last,val);

      mainIter = rb_ary_pop(arrays);
    }

    capnp::RemotePromise<capnp::DynamicStruct> r = request.send();
    return RemotePromise::create(r,self);
    //return Qfalse;
  }

}
