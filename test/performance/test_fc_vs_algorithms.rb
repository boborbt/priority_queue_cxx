require 'fc'
require 'algorithms'
require 'benchmark'

# Performs 50.000 pushes and pops in priority queues using the fc and
# algorithms implementations and reports the time spent.

N = 20_000
algo_pq = Containers::PriorityQueue.new
fc_pq = FastContainers::PriorityQueue.new(:min)

Benchmark.bm do |bm|
  bm.report('algo:push') { N.times { |n| algo_pq.push(n.to_s, rand) } }
  bm.report('fc:push')   { N.times { |n| fc_pq.push(n.to_s, rand) } }
  bm.report('algo:pop')  { N.times { algo_pq.pop } }
  bm.report('fc:pop')    { N.times { fc_pq.pop } }
end