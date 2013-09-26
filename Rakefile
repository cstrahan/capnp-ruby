require 'capn_proto/version'
GEMSPEC = eval(File.read('capn_proto.gemspec'))

require 'rubygems/package_task'
Gem::PackageTask.new(GEMSPEC) do |pkg|
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('capn_proto', GEMSPEC) do |ext|
  ext.ext_dir = 'ext/capn_proto'
  ext.lib_dir = 'lib/capn_proto'
  ext.source_pattern = "*.{cc,h}"
end

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec) do |config|
end

task :default => [:compile, :spec]

Rake::Task["clean"].clear
task :clean do
  rm_r "tmp" rescue nil
  rm_r "pkg" rescue nil
  rm "lib/capn_proto/capn_proto.bundle" rescue nil
end

task :release => [:clean, :compile, :spec, :gem]  do
  tag = "v#{CapnProto::VERSION}"
  sh "git tag #{tag}"
  sh "git push origin #{tag}"
  sh "gem push pkg/capn_proto-#{CapnProto::VERSION}.gem"
end

task :console do
  $: << File.expand_path("../lib", __FILE__)
  require 'irb'
  require 'capn_proto'
  ARGV.clear
  IRB.start
end
