# FastContainers

FastContainers is a light wrapper library around c++ containers. It aims at implementing a number of containers that are not in the standard ruby library and are presently only available as pure ruby libraries. 

## Containers included in the current version
Presently the library includes a single class named PriorityQueue. More containers will be added as necessity arises. Contributors are most welcome.

## Installation

```
gem install 'fast_containers'
```

## Usage Example

```ruby
   require 'fc'
   q = FastContainers::PriorityQueue.new(:max)
   q.push("largest", 10)
   q.push("smallest", 5)
   q.top      # =>  "largest"
   q.top_key  # => 10
   q.pop
```

## How fast is it?

As far as I know, there are no C extensions implementing priority queues to date. This implies that the provided implementation is a *lot* faster than the best current alternative. 
To get an idea about how faster it is, here it follows a comparison of the time needed by [algorithms](https://github.com/kanwei/algorithms) priority queue implementation and the FastContainers implementation.

```ruby
  require 'fc'
  require 'algorithms'
  require 'benchmark'

  # Performs 50.000 pushes and pops in priority queues using the fc and
  # algorithms implementations and reports the time spent.

  N = 50_000
  algo_pq = Containers::PriorityQueue.new
  fc_pq = FastContainers::PriorityQueue.new(:min)

  Benchmark.bm do |bm|
    bm.report('algo:push') { N.times { |n| algo_pq.push(n.to_s, rand) } }
    bm.report('fc:push')   { N.times { |n| fc_pq.push(n.to_s, rand) } }
    bm.report('algo:pop')  { N.times { algo_pq.pop } }
    bm.report('fc:pop')    { N.times { fc_pq.pop } }
  end
```

Outputs:
```
                 user     system      total        real
algo:push   15.950000   0.720000  16.670000 ( 16.661620)
fc:push      0.000000   0.000000   0.000000 (  0.007781)
algo:pop     0.500000   0.010000   0.510000 (  0.508014)
fc:pop       0.010000   0.000000   0.010000 (  0.010557)
```

