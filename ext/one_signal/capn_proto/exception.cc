#include "ruby_capn_proto.h"
#include "exception.h"
#include "class_builder.h"
#include "util.h"

// VALUE rb_eException;
// VALUE rb_eStandardError;
// VALUE rb_eRuntimeError;

namespace ruby_capn_proto {
  using WrappedType = kj::Exception;
  VALUE Exception::Class;

  void Exception::Init() {
    ClassBuilder("Exception", rb_eException).
      store(&Class);
  }

  VALUE Exception::create(WrappedType exception) {
    VALUE msg = Util::toRubyString(exception.getDescription());
    VALUE rb_exception = rb_funcall(Class, rb_intern("new"), 1, msg);

    return rb_exception;
  }

  VALUE Exception::raise(WrappedType exception) {
    rb_exc_raise(create(exception));
    return Qnil;
  }
}
