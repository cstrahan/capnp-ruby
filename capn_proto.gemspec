require File.expand_path('../lib/capn_proto/version', __FILE__)

Gem::Specification.new do |s|
  s.name = 'capn_proto'
  s.version = CapnProto::VERSION

  s.description =s.summary = "Cap'n Proto for ruby"

  s.homepage = 'http://github.com/cstrahan/ruby-capn_proto'

  s.authors = ['Charles Strahan']
  s.email = ['charles.c.strahan@gmail.com']

  s.add_development_dependency 'rspec', '2.14.1'

  s.require_paths = ['lib']

  s.files = `git ls-files`.split("\n")
end
