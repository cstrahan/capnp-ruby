GEMSPEC = eval(File.read('capn_proto.gemspec'))

require 'rubygems/package_task'
Gem::PackageTask.new(GEMSPEC) do |pkg|
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('init', GEMSPEC) do |ext|
  ext.ext_dir = 'ext/ruby_capn_proto'
  ext.lib_dir = 'lib/capn_proto'
  ext.source_pattern = "*.{cc,h}"
end
task :build => [:clean_build, :compile]

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec) do |config|
end
task :default => [:build, :spec]

task :clean_build do
  rm_r "tmp" rescue nil
  # rm_r "lib/capn_proto_ext.bundle" rescue nil
end

task :console do
  $: << File.expand_path("../lib", __FILE__)
  require 'irb'
  ARGV.clear
  IRB.start
end
