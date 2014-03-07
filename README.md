# FastContainers

[![Gem Version](https://badge.fury.io/rb/fast_containers.png)](http://badge.fury.io/rb/fast_containers)

FastContainers is a light wrapper library around c++ containers. It aims at implementing a number of containers that are not in the standard ruby library and are presently only available as pure ruby libraries. 

## Containers included in the current version
Presently the library includes a single class named PriorityQueue. More containers will be added as necessity arises. Contributors are most welcome.

## Installation

```ruby
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
To get an idea about how faster it is, here it follows a comparison of the time needed to push and pop a given number of elements by FastContainers and others priority queues implementations that can be found on Rubygems. In each experiment the number of push/pop to be performed is chosen so to have a reasonable response time (within few minutes).

### Comparison with [algorithms (0.6.1)](http://rubygems.org/gems/algorithms) (50,000 push/pop)

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

Output (reformatted):

|         |      user|    system|     total|       real |
|:--------|---------:|---------:|---------:|-----------:|
|algo:push|122.200|  7.030|129.230|(129.173)|
|fc:push  |  0.020|  0.000|  0.020|(  0.020)|
|algo:pop |  1.460|  0.020|  1.480|(  1.476)|
|fc:pop   |  0.030|  0.000|  0.030|(  0.030)|

Summary: FastContainers::PriorityQueues are *6461.5 times faster* on pushes and *49.3 times faster* on pops.


### Comparison with [priority_queue (0.2.0)](http://rubygems.org/gems/priority_queue) (50,000 push/pop)

```ruby
require 'fc'
require 'priority_queue'
require 'benchmark'

N = 50_000
pq_pq = PriorityQueue.new
fc_pq = FastContainers::PriorityQueue.new(:min)

Benchmark.bm do |bm|
  bm.report('pq:push') { N.times { |n| pq_pq[rand] << n.to_s } }
  bm.report('fc:push')   { N.times { |n| fc_pq.push(n.to_s, rand) } }
  bm.report('pq:pop')  { N.times { pq_pq.shift } }
  bm.report('fc:pop')    { N.times { fc_pq.pop } }
end
```

Output (reformatted):

|         |      user|    system|     total|       real |
|:--------|---------:|---------:|---------:|-----------:|
|pq:push  | 0.060    | 0.010    | 0.070    |(  0.062593)|
|fc:push  | 0.020    | 0.000    | 0.020    |(  0.018866)|
|pq:pop   | 948.440  | 8.290    | 956.730  |(956.676601)|
|fc:pop   | 0.040    | 0.000    | 0.040    |(  0.032753)|

Summary: FastContainers::PriorityQueues are *3.5 times faster* on pushes and *23918.25 times faster* on pops.

### Comparison with [em-priority-queue (1.1.2)](http://rubygems.org/gems/em-priority-queue) (500,000 push/pop)

```ruby
require 'fc'
require 'em-priority-queue'
require 'benchmark'

N = 500_000
em_pq = EM::PriorityQueue.new
fc_pq = FastContainers::PriorityQueue.new(:min)

Benchmark.bm do |bm|
  bm.report('em:push') { N.times { |n| em_pq.push(n.to_s, rand) } }
  bm.report('fc:push') { N.times { |n| fc_pq.push(n.to_s, rand) } }
  bm.report('em:pop')  { N.times { em_pq.pop {} } }
  bm.report('fc:pop')  { N.times { fc_pq.pop } }
end
```

Output (reformatted):

|         |      user|    system|     total|       real |
|:--------|---------:|---------:|---------:|-----------:|
|em:push  |1.650  |0.130  | 1.780 | (  1.895794) |
|fc:push  |0.190  |0.020  | 0.210 | (  0.224068) |
|em:pop   |3.980  |0.180  | 4.160 | (  4.360084) |
|fc:pop   |0.380  |0.000  | 0.380 | (  0.381250) |

Summary: FastContainers are *8.5 times faster* on pushes and *10.9 times faster* on pops.

### Comparison with [pqueue (2.0.2)](http://rubygems.org/gems/pqueue) (100,000 push/pop)


```ruby
require 'fc'
require 'pqueue'
require 'benchmark'

N = 100_000
pq_pq = PQueue.new { |x,y| x[1] <=> y[1] }
fc_pq = FastContainers::PriorityQueue.new(:min)

Benchmark.bm do |bm|
  bm.report('pq:push') { N.times { |n| pq_pq.push([n,rand]) } }
  bm.report('fc:push')   { N.times { |n| fc_pq.push(n.to_s, rand) } }
  bm.report('pq:pop')  { N.times { pq_pq.pop } }
  bm.report('fc:pop')    { N.times { fc_pq.pop } }
end
```

Output (reformatted):

|         |      user|    system|     total|       real |
|:--------|---------:|---------:|---------:|-----------:|
|pq:push  | 25.240|41.660 | 66.900| ( 66.871391)|
|fc:push  | 0.040 | 0.000 |  0.040| (  0.035270)|
|pq:pop   | 0.010 | 0.000 |  0.010| (  0.018718)|
|fc:pop   | 0.070 | 0.000 |  0.070| (  0.061138)|

Summary: FastContainers are *1672.5 times faster* on pushes and *7 times slower* on pops.


## API

Here it follows a transcription of the RDoc documentation for the library. I'm adding it here because I've having difficulties in instructing the 'gem' executable to generate the correct files on installation (everything works fine using rdoc from the command line though). Any suggestion about how to solve this problem is *very* welcome.

### FastContainers::PriorityQueue

#### Public Class Methods

##### new(queue_kind)

Create a new priority queue and returns it. queue_kind specifies whether to build a :min or a :max queue.

Example:

```ruby 
  pq = FastContainers::PriorityQueue.new(:min)
```

#### Public Instance Methods

##### each { |obj,priority| ... } → self

Iterates through the priority queue yielding each element to the given block. The order of the yielded elements is not defined. Returns self.

Example:

```ruby

pq.each do |obj,priority|
  puts "Obj #{obj} has priority #{priority}"
end
```

##### next

Alias for: [top](#label-top+%E2%86%92+obj)

##### next_key

Alias for: [top_key](#label-top_key+%E2%86%92+float)

##### empty?

Returns true if the queue is empty

##### pop → self

Pops the top most element from the priority queue. Returns self.

##### pop_each { |obj, priority| ... } → self

Iterates through the priority queue popping the top element and yielding it to the block. The order of yielded elements is guaranteed to be the priority order. Returns self.

Example:

```ruby
ary = [100, 1, 90, 55, 6]
ary.each { |x| pq.push(x.to_s, x)}
ary.pop_each {|obj, priority| print(priority, ',') } # => 1,6,55,90,100,
```

##### push(obj,priority) → self

Push the obj/priority pair into the queue and returns self.

##### size  → num

Returns the size of the priority queue

##### top → obj

Returns the object at the top of the priority queue.

##### top_key → float

Returns the priority of the object at the top of the priority queue.

#### Included Modules

The class Includes Enumerable, so that standard enumeration based methods (e.g., map, all?, any?, ...) can all be used with this container. Notice that Enumerable methods are based on #each, implying that the order used to iterate through the container is undefined.
