Gem::Specification.new do |s|
  s.name        = "priority_queue_cxx"
  s.version     = "0.3.5"
  s.summary     = "Fast (c++ wrapper) priority queue implementation for ruby."
  s.date        = "2014-03-25"
  s.description = "Fast priority queue implementation (c++ wrapper, see README.md for a comparison with other libraries)"
  s.authors     = ["Roberto Esposito"]
  s.email       = ["boborbt@gmail.com"]
  s.homepage    = "https://github.com/boborbt/priority_queue_cxx"
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
