require "rubygems"
require "rake/extensiontask"

Rake::Task[:test].prerequisites << :compile

# spec = Gem::Specification.load('fast_containers.gemspec')
# Rake::ExtensionTask.new('fast_containers', spec)
# 
Rake::ExtensionTask.new "fast_containers" do |ext|
  ext.lib_dir = "lib/fast_containers"
end
