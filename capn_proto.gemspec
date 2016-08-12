require File.expand_path('../lib/capn_proto/version', __FILE__)

Gem::Specification.new do |s|
  s.name = 'capn_proto-rpc'
  s.license = 'MIT'

  s.version = CapnProto::VERSION
  s.required_ruby_version = '>= 2.0'

  s.summary = "Cap'n Proto (libcapnp) bindings for Ruby."

  s.description =
    "This gem wraps the official C++ implementation of Cap'n Proto " \
    "(libcapnp). " \
    "From the Cap'n Proto documentation: " \
    "\"Cap'n Proto is an insanely fast data interchange format and " \
    "capability-based RPC system. Think JSON, except binary. " \
    "Or think Protocol Buffers, except faster.\" " \
    "This is a extended version of the original gem Capnproto which adds RPC support visit the homepage to view usage"

  s.homepage = 'https://github.com/nemoNoboru/capnp-ruby'

  s.authors = ['Charles Strahan','Felipe Vieira']
  s.email = ['charles.c.strahan@gmail.com','felipetavres@gmail.com']

  s.add_development_dependency 'rspec', '2.14.1'
  s.add_development_dependency 'rake' , '~> 0'
  s.add_development_dependency 'rake-compiler', '0.7.6'

  s.add_development_dependency 'awesome_print', '~> 0'
  s.add_development_dependency 'interactive_editor', '~> 0'

  s.extensions = ['ext/capn_proto/extconf.rb']
  s.require_paths = ['lib']

  s.files = `git ls-files`.split("\n")
end
