#include "ruby_capn_proto.h"
#include "class_builder.h"

namespace ruby_capn_proto {

  VALUE defineClass(const char *name, VALUE superclass = rb_cObject) {
    VALUE CapnProto = rb_define_module("CapnProto");
    VALUE klass = rb_define_class_under(CapnProto, name, superclass);
    // rb_funcall(klass, rb_intern("private_class_method"), 1, rb_str_new2("new"));
    return klass;
  }

  ClassBuilder::ClassBuilder(const char* name, VALUE superclass) {
    this->value = defineClass(name, superclass);
  }
  ClassBuilder::ClassBuilder(const char* name, const char* supername) {
    VALUE superclass = defineClass(supername);
    this->value = defineClass(name, superclass);
  }

  ClassBuilder& ClassBuilder::defineAlloc(VALUE (*impl)(VALUE)) {
    rb_define_alloc_func(this->value, (VALUE (*)(VALUE))impl);
    return *this;
  }

  ClassBuilder& ClassBuilder::defineConst(const char* name, VALUE value) {
    rb_define_const(this->value, name, value);
    return *this;
  }

  ClassBuilder& ClassBuilder::defineMethod(const char* name, VALUE (*impl)(int, VALUE*, VALUE)) {
    rb_define_method(this->value, name, (VALUE (*)(...))impl, -1);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineMethod(const char* name, VALUE (*impl)(VALUE)) {
    rb_define_method(this->value, name, (VALUE (*)(...))impl, 0);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineMethod(const char* name, VALUE (*impl)(VALUE, VALUE)) {
    rb_define_method(this->value, name, (VALUE (*)(...))impl, 1);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE)) {
    rb_define_method(this->value, name, (VALUE (*)(...))impl, 2);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE, VALUE)) {
    rb_define_method(this->value, name, (VALUE (*)(...))impl, 3);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineSingletonMethod(const char* name, VALUE (*impl)(int, VALUE*, VALUE)) {
    rb_define_singleton_method(this->value, name, (VALUE (*)(...))impl, -1);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineSingletonMethod(const char* name, VALUE (*impl)(VALUE)) {
    rb_define_singleton_method(this->value, name, (VALUE (*)(...))impl, 0);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineSingletonMethod(const char* name, VALUE (*impl)(VALUE, VALUE)) {
    rb_define_singleton_method(this->value, name, (VALUE (*)(...))impl, 1);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineSingletonMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE)) {
    rb_define_singleton_method(this->value, name, (VALUE (*)(...))impl, 2);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineSingletonMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE, VALUE)) {
    rb_define_singleton_method(this->value, name, (VALUE (*)(...))impl, 3);
    return *this;
  }
  ClassBuilder& ClassBuilder::defineEnumConst(const char* name, int value) {
    rb_define_const(this->value, name, INT2FIX(value));
    return *this;
  }
  ClassBuilder& ClassBuilder::store(VALUE* storage) {
    rb_gc_register_address(storage);
    *storage = this->value;
    return *this;
  }
}
