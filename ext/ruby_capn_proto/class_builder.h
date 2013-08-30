#include "ruby_capn_proto.h"

namespace ruby_capn_proto {
  class ClassBuilder {
  public:
    ClassBuilder() {};
    ClassBuilder(const char* name, VALUE superclass = rb_cObject);
    ClassBuilder(const char* name, const char* supername);
    ClassBuilder& defineAlloc(VALUE (*impl)(VALUE));
    ClassBuilder& defineConst(const char* name, VALUE value);
    ClassBuilder& defineMethod(const char* name, VALUE (*impl)(int, VALUE*, VALUE));
    ClassBuilder& defineMethod(const char* name, VALUE (*impl)(VALUE));
    ClassBuilder& defineMethod(const char* name, VALUE (*impl)(VALUE, VALUE));
    ClassBuilder& defineMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE));
    ClassBuilder& defineMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE, VALUE));
    ClassBuilder& defineSingletonMethod(const char* name, VALUE (*impl)(int, VALUE*, VALUE));
    ClassBuilder& defineSingletonMethod(const char* name, VALUE (*impl)(VALUE));
    ClassBuilder& defineSingletonMethod(const char* name, VALUE (*impl)(VALUE, VALUE));
    ClassBuilder& defineSingletonMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE));
    ClassBuilder& defineSingletonMethod(const char* name, VALUE (*impl)(VALUE, VALUE, VALUE, VALUE));
    ClassBuilder& defineEnumConst(const char* name, int value);
    ClassBuilder& store(VALUE* storage);
    inline operator VALUE() {return this->value;}
  protected:
    VALUE value;
  };

  template <VALUE(* f)(int, VALUE*, VALUE)>
  VALUE handleExceptions(int argc, VALUE* argv, VALUE self)
  {
    try {
      return f(argc, argv, self);
    } catch (...) {
      rb_raise(rb_eRuntimeError, "caught unkown error");
    }
  }

  template <VALUE(* f)(VALUE)>
  VALUE handleExceptions(VALUE self)
  {
    return f(self);
  }

  template <VALUE(* f)(VALUE, VALUE)>
  VALUE handleExceptions(VALUE self, VALUE arg1)
  {
    return f(self, arg1);
  }

  template <VALUE(* f)(VALUE, VALUE, VALUE)>
  VALUE handleExceptions(VALUE self, VALUE arg1, VALUE arg2)
  {
    return f(self, arg1, arg2);
  }

  template <VALUE(* f)(VALUE, VALUE, VALUE, VALUE)>
  VALUE handleExceptions(VALUE self, VALUE arg2, VALUE arg1, VALUE arg3)
  {
    return f(self, arg1, arg2, arg3);
  }

  template <VALUE(* f)(VALUE, VALUE, VALUE, VALUE, VALUE)>
  VALUE handleExceptions(VALUE self, VALUE arg2, VALUE arg1, VALUE arg3, VALUE arg4)
  {
    return f(self, arg1, arg2, arg3, arg4);
  }
}
