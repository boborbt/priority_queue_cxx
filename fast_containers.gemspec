Gem::Specification.new do |s|
  s.name        = "fast_containers"
  s.version     = "0.2.12"
  s.summary     = "Fast containers not included in the std library. Presently implements: priority queues"
  s.date        = "2014-03-11"
  s.description = "A thin wrapper around C++ containers (presently implements: priority queues)"
  s.authors     = ["Roberto Esposito"]
  s.email       = ["boborbt@gmail.com"]
  s.homepage    = "https://github.com/boborbt/fast_containers"
  s.files       = [ "lib/fc.rb", 
                    "ext/fast_containers/FastContainers.cpp",   
                    "ext/fast_containers/fc_pq.cpp", 
                    "ext/fast_containers/fc_pq.h", 
                    "test/test_fast_containers.rb" ] +
                    Dir.glob("test/performance/*.rb")
  s.rdoc_options << "--main" << "README.md"
  s.extra_rdoc_files = ["README.md"]
  s.extensions   << "ext/fast_containers/extconf.rb"
  s.licenses     = ['MIT']
  
  s.add_development_dependency 'rake-compiler', '~>0'
end