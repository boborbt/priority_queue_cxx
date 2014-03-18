# FastContainers

[![Gem Version](https://badge.fury.io/rb/fast_containers.png)](http://badge.fury.io/rb/fast_containers)

FastContainers provides "fast containers" to ruby. Speed is achieved by exposing  c++ standard containers through a light ruby wrapper. It aims at implementing a number of containers that are not in the standard ruby library and are presently only available as pure ruby libraries.

## Containers included in the current version
Presently the library includes a single class named PriorityQueue. More containers will be added as necessity arises. Contributors and feature requests are most welcome.

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

As far as I know, only the PriorityQueue gem provides priority queues as a C extension. This implies that the provided implementation is a *lot* faster than most current alternatives and, as shown below, it compares favorably with PriorityQueue as well.

To get an idea about how fast it is, below we provide a comparison of the time needed to push and pop a large number of elements into a priority queue. Each experiment compares FastContainers with others priority queues implementations. Since timings varies greatly among different implementations, the number of push/pop performed is chosen so to make the experiments to run for (at most) few minutes.

The following table summarizes the outputs, detailed results can be found in the next few sections.

| library | avg &#956;s per push | avg &#956;s per pop | avg &#956;s per op |
|:--------|---------:|---------:|---------:|
| *fast_containers*   | *0.456*   |  *1.138*  | *0.797* |
| PriorityQueue     | 2.09    | 5.186   | 3.638 |
| em-priority-queue | 3.56    | 8.32    | 5.94  |
| pqueue            | 669.0   | 0.1     | 334.55|
| algorithms        | 2584.6  |   29.6  |1307.1 |
| priority_queue    | 1.4     |19134.6  |9568.0 |

where: results are sorted according to "avg &#956;s per op" (higher is better); &#956;s stands for micro seconds; op stands for any operation (push or pop); the figures for fast_containers has been calculated with the results of experiments with PriorityQueue (the experiment with the highest number of operations).


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
|algorithms:push|122.200|  7.030|129.230|(129.173)|
|*fast_containers:push*  |  *0.020*|  *0.000*|  *0.020*|*(  0.020)*|
|algorithms:pop |  1.460|  0.020|  1.480|(  1.476)|
|*fast_containers:pop*   |  *0.030*|  *0.000*|  *0.030*|*(  0.030)*|

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
|priority_queue:push  | 0.060    | 0.010    | 0.070    |(  0.062593)|
|*fast_containers:push*  | *0.020*    | *0.000*    | *0.020*    |*(  0.018866)*|
|priority_queue:pop   | 948.440  | 8.290    | 956.730  |(956.676601)|
|*fast_containers:pop*   | 0.040    | 0.000    | 0.040    |*(  0.032753)*|

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
|em-priority-queue:push  |1.650  |0.130  | 1.780 | (  1.895794) |
|*fast_containers:push*  |*0.190*  |*0.020*  | *0.210* | *(  0.224068)* |
|em-priority-queue:pop   |3.980  |0.180  | 4.160 | (  4.360084) |
|*fast_containers:pop*   |*0.380*  |*0.000*  | *0.380* | *(  0.381250)* |

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
|pqueue:push  | 25.240|41.660 | 66.900| ( 66.871391)|
|*fast_containers:push*  | *0.040* | *0.000* |  *0.040*| *(  0.035270)*|
|pqueue:pop   | 0.010 | 0.000 |  0.010| (  0.018718)|
|*fast_containers:pop*   | *0.070* | *0.000* | *0.070*| *(  0.061138)*|

Summary: FastContainers are *1672.5 times faster* on pushes and *7 times slower* on pops.

### Comparison with [PriorityQueue (0.1.2)](https://rubygems.org/gems/PriorityQueue) (5,000,000 push/pop)


```ruby
require 'fc'
require 'priority_queue'
require 'benchmark'

N = 5_000_000
pq_pq = CPriorityQueue.new
fc_pq = FastContainers::PriorityQueue.new(:min)

Benchmark.bm do |bm|
  bm.report('pq:push') { N.times { |n| pq_pq.push(n.to_s,rand) } }
  bm.report('fc:push') { N.times { |n| fc_pq.push(n.to_s, rand) } }
  bm.report('pq:pop')  { N.times { pq_pq.delete_min } }
  bm.report('fc:pop')  { N.times { fc_pq.pop } }
end
```

Output (reformatted):

|         |      user|    system|     total|       real |
|:--------|---------:|---------:|---------:|-----------:|
|PriorityQueue:push  | 10.020|  0.430| 10.45|( 10.665449)|
|*fast_containers:push*  |  *2.110*|  *0.170*|  *2.28*|*(  2.452529)*|
|PriorityQueue:pop   | 25.860|  0.070| 25.93|( 25.949438)|
|*fast_containers:pop*   |  *5.690*|  *0.000*|  *5.69*|*(  5.688552)*|

Summary: FastContainers are *4.58 times faster* on pushes and *4.54 times faster* on pops.

## Which is the best priority queue implementation for ruby?

As for most important questions the answer is: it depends. The evidence reported here shows that if you are only interested in the speed of push and pop methods, then ```FastContainers::PriorityQueue``` is a very good candidate. Few other important factors may make other libraries be better suited for your needs. The most glaring one is that ```FastContainers::PriorityQueue``` does not support changes of priorities<sup><a id="backref1" href="#notes">1</a></sup>. If your problem requires this feature I would recommend using  [PriorityQueue (0.1.2)](https://rubygems.org/gems/PriorityQueue) library. Also, in making your choice you may want to consider the fact that not all the presented library are actively maintained (although, no one gave any problem at the time of the writing).

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

#### second_best_key → float

Returns the priority of the second best element in the priority queue.

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

## Notes

<sup id="ref1">1</sup> It is worth mentioning that, due to how priority queue are implemented by the C++ standard library, this implementation can't efficiently support priority changes. In any case, to support this feature would require important changes in the current API.<a href="#which-is-the-best-priority-queue-implementation-for-ruby" title="back reference">&#8617;</a>

