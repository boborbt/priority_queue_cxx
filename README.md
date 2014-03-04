# FastContainers

[![Gem Version](https://badge.fury.io/rb/fast_containers.png)](http://badge.fury.io/rb/fast_containers)

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

```ruby

                 user     system      total        real
algo:push   15.950000   0.720000  16.670000 ( 16.661620)
fc:push      0.000000   0.000000   0.000000 (  0.007781)
algo:pop     0.500000   0.010000   0.510000 (  0.508014)
fc:pop       0.010000   0.000000   0.010000 (  0.010557)
```

## API

Here it follows a transcription of the RDoc documentation for the library. I'm adding it here because I've having difficulties in instructing the 'gem' executable to generate the correct files on installation (everything works fine using rdoc from the command line though). Any suggestion about how to solve this problem is *very* welcome.

### Public Class Methods

#### new(queue_kind)

Create a new priority queue and returns it. queue_kind specifies whether to build a :min or a :max queue.

Example:

```ruby 
  pq = FastContainers::PriorityQueue.new(:min)
```

### Public Instance Methods

#### each { |obj,priority| ... } → self

Iterates through the priority queue yielding each element to the given block. The order of the yielded elements is not defined. Returns self.

Example:

```ruby

pq.each do |obj,priority|
  puts "Obj #{obj} has priority #{priority}"
end
```


#### empty?

Returns true if the queue is empty

#### pop → self

Pops the top most element from the priority queue. Returns self.

#### pop_each { |obj, priority| ... } → self

Iterates through the priority queue popping the top element and yielding it to the block. The order of yielded elements is guaranteed to be the priority order. Returns self.

Example:

```ruby
ary = [100, 1, 90, 55, 6]
ary.each { |x| pq.push(x.to_s, x)}
ary.pop_each {|obj, priority| print(priority, ',') } # => 1,6,55,90,100,
```

#### push(obj,priority) → self

Push the obj/priority pair into the queue and returns self.

#### top → obj

Returns the object at the top of the priority queue.

#### top_key → float

Returns the priority of the object at the top of the priority queue.
