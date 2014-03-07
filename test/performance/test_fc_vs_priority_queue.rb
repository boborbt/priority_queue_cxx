# Copyright (c) 2014 Roberto Esposito
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
require 'fc'
require 'priority_queue'
require 'benchmark'

# Performs 50.000 pushes and pops in priority queues using the fc and
# algorithms implementations and reports the time spent.

N = 50_000
pq_pq = PriorityQueue.new
fc_pq = FastContainers::PriorityQueue.new(:min)

Benchmark.bm do |bm|
  bm.report('pq:push') { N.times { |n| pq_pq[rand] << n.to_s } }
  bm.report('fc:push')   { N.times { |n| fc_pq.push(n.to_s, rand) } }
  bm.report('pq:pop')  { N.times { pq_pq.shift } }
  bm.report('fc:pop')    { N.times { fc_pq.pop } }
end