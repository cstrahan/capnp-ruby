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

task :console do
  $: << File.expand_path("../lib", __FILE__)
  require 'irb'
  require 'capn_proto'
  ARGV.clear
  IRB.start
end
