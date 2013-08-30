require File.expand_path('../lib/capn_proto/version', __FILE__)

Gem::Specification.new do |s|
  s.name = 'capn_proto'
  s.version = CapnProto::VERSION

  s.description = s.summary = "Cap'n Proto for ruby"

  s.homepage = 'http://github.com/cstrahan/ruby-capn_proto'

  s.authors = ['Charles Strahan']
  s.email = ['charles.c.strahan@gmail.com']

  s.add_development_dependency 'rspec', '2.14.1'
  s.add_development_dependency 'rake'
  s.add_development_dependency 'rake-compiler', '0.7.6'

  s.add_development_dependency 'awesome_print'
  s.add_development_dependency 'interactive_editor'

  s.extensions = ['ext/extconf.rb']
  s.require_paths = ['lib']

  s.files = `git ls-files`.split("\n")
end
