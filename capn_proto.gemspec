require File.expand_path('../lib/capn_proto/version', __FILE__)

Gem::Specification.new do |s|
  s.name = 'capn_proto'
  s.version = CapnProto::VERSION

  s.summary = "Cap'n Proto (libcapnp) bindings for Ruby."

  s.description =
    "This gem wraps the official C++ implementation of Cap'n Proto " \
    "(libcapnp). " \
    "From the Cap'n Proto documentation: " \
    "\"Cap'n Proto is an insanely fast data interchange format and " \
    "capability-based RPC system. Think JSON, except binary. " \
    "Or think Protocol Buffers, except faster.\""

  s.homepage = 'https://github.com/cstrahan/capnp-ruby'

  s.authors = ['Charles Strahan']
  s.email = ['charles.c.strahan@gmail.com']

  s.add_development_dependency 'rspec', '2.14.1'
  s.add_development_dependency 'rake'
  s.add_development_dependency 'rake-compiler', '0.7.6'

  s.add_development_dependency 'awesome_print'
  s.add_development_dependency 'interactive_editor'

  s.extensions = ['ext/capn_proto/extconf.rb']
  s.require_paths = ['lib']

  s.files = `git ls-files`.split("\n")
end
