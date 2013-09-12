require 'mkmf'
require File.expand_path("../cxx_compiler", __FILE__)

compiler = CXXCompiler.new(ENV.to_hash)
unless compiler.has_cxx11_compiler_support?
  abort "*** A compiler with support for C++11 language features is required."
end
unless compiler.has_cxx11_library_support?
  abort "*** A C++ library with support for C++11 features is required."
end

if enable_config('debug')
  CONFIG['CFLAGS'] += " -O0 -ggdb3"
else
  $CPPFLAGS += " -DNDEBUG"
end

CONFIG['CXX'] = ENV['CXX'] if ENV['CXX']
CONFIG['CXXFLAGS'] += " #{ENV['CXXFLAGS']}" if ENV['CXXFLAGS']
CONFIG['CXXFLAGS'] += " #{compiler.std_flag} #{compiler.stdlib_flag}"

$LDFLAGS += " -lcapnpc"
$LDFLAGS += " -lcapnp"
$LDFLAGS += " -lkj"

create_makefile('capn_proto/capn_proto')

# HACK ATTACK
# def inreplace(path, search, replace)
  # contents = File.read(path)
  # contents.gsub!(search, replace)
  # File.open(path, "w") do |f|
    # f.write(contents)
  # end
# end

# inreplace("Makefile", "V = 0", "V = 1")
# inreplace("Makefile", "-O3", "-O0")
# inreplace("Makefile", "ECHO = $(ECHO1:0=@echo)", "ECHO = @echo")
