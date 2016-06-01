require 'mkmf'
require File.expand_path("../cxx_compiler", __FILE__)

compiler = CXXCompiler.new({'CXX' => CONFIG['CXX']}.merge(ENV.to_hash))
unless compiler.has_cxx11_compiler_support?
  abort "*** A compiler with support for C++11 language features is required."
end
unless compiler.has_cxx11_library_support?
  abort "*** A C++ library with support for C++11 features is required."
end

$CXXFLAGS = ' -std=c++11 ' #added by fvieira in order to compile in his computer

CONFIG['CXX']      = ENV['CXX'] || CONFIG['CXX']
CONFIG['CXXFLAGS'] = [(ENV['CXXFLAGS'] || CONFIG['CXXFLAGS']),
                      compiler.std_flag,
                      compiler.stdlib_flag].join(' ')

if enable_config('debug')
  CONFIG['CFLAGS'] += " -O0 -ggdb3"
else
  $CPPFLAGS += " -DNDEBUG"
end

$LDFLAGS += " -lcapnpc"
$LDFLAGS += " -lcapnp"
$LDFLAGS += " -lkj"
$LDFLAGS += " -lcapnp-rpc"
$LDFLAGS += " -lkj-async"


create_makefile('capn_proto/capn_proto')
