require "rubygems"
require "rake/extensiontask"

Rake::Task[:test].prerequisites << :compile

Rake::ExtensionTask.new "fast_containers" do |ext|
  ext.lib_dir = "lib/fast_containers"
end
