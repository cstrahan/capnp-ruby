require 'mkmf'

if enable_config('debug')
  CONFIG['CFLAGS'] += " -O0 -ggdb3"
else
  $CPPFLAGS += " -DNDEBUG"
end

CONFIG['CXX'] = ENV['CXX'] if ENV['CXX']
CONFIG['CXXFLAGS'] += " #{ENV['CXXFLAGS']}" if ENV['CXXFLAGS']

$LDFLAGS += " -lcapnpc"
$LDFLAGS += " -lcapnp"
$LDFLAGS += " -lkj"

create_makefile('ruby_capn_proto/init')

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
