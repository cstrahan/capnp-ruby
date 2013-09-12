require 'shellwords'
require 'tmpdir'

# Discovers support for C++11 features,
# and any required CXXFLAGS for such features.
class CXXCompiler
  CXX_COMPILER_FEATURES = <<-CODE
    template <typename T>
    struct check
    {
      static_assert(sizeof(int) <= sizeof(T), "not big enough");
    };

    typedef check<check<bool>> right_angle_brackets;

    int a;
    decltype(a) b;

    typedef check<int> check_type;
    check_type c;
    check_type&& cr = static_cast<check_type&&>(c);

    #ifdef __has_include
    #if __has_include(<type_traits>)
    #include <type_traits>
    #endif
    #endif
  CODE

  CXX_LIBRARY_FEATURES = <<-CODE
    #include <initializer_list>
    #include <unordered_map>
    #include <atomic>
    #include <thread>
  CODE

  # The environment variables (e.g. CXX, CXXFLAGS).
  def initialize(env)
    @env = env.dup
  end

  # True if support for C++11 was detected, false otherwise.
  def has_cxx11_compiler_support?
    !!std_flag
  end

  # True if support for C++11 libraries was detected, false otherwise.
  def has_cxx11_library_support?
    !!stdlib_flag
  end

  # The required std flag (e.g. '-std=c++11'),
  # empty string if unecessary given the current environment and/or compiler,
  # or nil in the case where the compiler has no support.
  def std_flag
    test_compiler_flags(@env)
    @std_flag
  end

  # The required stdlib flag (e.g. '-stdlib=libc++'),
  # empty string if unecessary given the current environment and/or compiler,
  # or nil in the case where the compiler has no support.
  def stdlib_flag
    test_compiler_flags(@env)
    @stdlib_flag
  end

  private

  # Detect any required flags.
  def test_compiler_flags(env)
    return if @tested
    @tested = true

    cxxflags = (env['CXXFLAGS'] || '')
    env = env.dup

    flags = ['', '-std=gnu++11', '-std=gnu++0x', '-std=c++11', '-std=c++0x']
    @std_flag = flags.detect do |flag|
      env['CXXFLAGS'] = [cxxflags, flag].join(' ')
      compile(CXX_COMPILER_FEATURES, env)
    end

    return unless @std_flag

    env = env.dup
    flags = ['', '-stdlib=libc++']
    @stdlib_flag = flags.detect do |flag|
      env['CXXFLAGS'] = [cxxflags, std_flag, flag].join(' ')
      compile(CXX_LIBRARY_FEATURES, env)
    end
  end

  # Compile a snippet of C++, returning true or false to indicate
  # success.
  def compile(code, env)
    Dir.mktmpdir do |dir|
      Dir.chdir(dir) do
        File.open("test.cc", "w") {|f| f.write(code)}
        system("#{env['CXX'].shellescape} #{env['CXXFLAGS']} -c test.cc >/dev/null 2>&1")
      end
    end
  end
end

if $0 == __FILE__
  compiler = CXXCompiler.new(ENV.to_hash)

  puts "CXX      = #{ENV['CXX']}"
  puts "CXXFLAGS = #{[ENV['CXXFLAGS'], compiler.std_flag, compiler.stdlib_flag].join(' ')}"
  puts ""
  puts "Has C++11 compiler support?"
  puts "  #{compiler.has_cxx11_compiler_support? ? 'YES' : 'NO'}"
  puts ""
  puts "Has C++11 library support?"
  puts "  #{compiler.has_cxx11_library_support? ? 'YES' : 'NO'}"
end
