require './lib/one_signal/capn_proto/version'
GEMSPEC = eval(File.read('one_signal-capn_proto.gemspec'))

require 'rubygems/package_task'
Gem::PackageTask.new(GEMSPEC) do |pkg|
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('capn_proto', GEMSPEC) do |ext|
  ext.ext_dir = 'ext/one_signal/capn_proto'
  ext.lib_dir = 'lib/one_signal/capn_proto'
  ext.source_pattern = "*.{cc,h}"
end

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec) do |config|
end

task :default => [:compile, :spec]

Rake::Task["clean"].clear
desc "Clean build artifacts"
task :clean do
  rm_r "tmp" rescue nil
  rm_r "pkg" rescue nil
  rm "lib/one_signal/capn_proto/capn_proto.bundle" rescue nil
end

desc "Tag commit, push to repo, then push to RubyGems"
task :release => [:clean, :compile, :spec, :gem]  do
  tag = "v#{OneSignal::CapnProto::VERSION}"
  sh "git tag #{tag}"
  sh "git push origin #{tag}"
  sh "gem push pkg/one_signal-capn_proto-#{OneSignal::CapnProto::VERSION}.gem"
end

desc "Open an irb console"
task :console do
  $: << File.expand_path("../lib", __FILE__)
  require 'irb'
  require 'one_signal/capn_proto'
  ARGV.clear
  IRB.start
end
