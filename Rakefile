require "rubygems"
require "rake/extensiontask"
require 'rdoc/task'
require 'rake/testtask'

Rake::Task[:test].prerequisites << :compile
Rake::TestTask.new do |t|
  t.test_files = FileList['test/test*.rb']
end

Rake::ExtensionTask.new "fast_containers" do |ext|
  ext.lib_dir = "lib/fast_containers"
end

# --------------------------------------------------------------------------------
# RDOC 
# --------------------------------------------------------------------------------

RDOC_FILES = FileList["README.md", "ext/fast_containers/FastContainers.cpp"]

Rake::RDocTask.new do |rd|
    rd.main = "README.md"
    rd.rdoc_dir = "doc/site/api"
    rd.rdoc_files.include(RDOC_FILES)
end

Rake::RDocTask.new(:ri) do |rd|
     rd.main = "README.md"
     rd.rdoc_dir = "doc/ri"
     rd.options << "--ri-system"
     rd.rdoc_files.include(RDOC_FILES)
end