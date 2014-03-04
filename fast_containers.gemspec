Gem::Specification.new do |s|
  s.name        = "fast_containers"
  s.version     = "0.2.3"
  s.summary     = "Fast containers not included in the std library"
  s.date        = "2014-03-03"
  s.description = "A thin wrapper around C++ containers (presently only around priority queues)"
  s.authors     = ["Roberto Esposito"]
  s.email       = ["boborbt@gmail.com"]
  s.homepage    = "https://github.com/boborbt/fast_containers"
  s.files       = ["lib/fc.rb", "ext/fast_containers/FastContainers.cpp", "ext/fast_containers/fc_pq.cpp", "ext/fast_containers/fc_pq.h"]
  s.rdoc_options << "--main" << "README.md"
  s.extra_rdoc_files = ["README.md"]
  s.extensions   << "ext/fast_containers/extconf.rb"
  s.licenses     = ['MIT']
  
  s.add_development_dependency 'rake-compiler', '~>0'
end