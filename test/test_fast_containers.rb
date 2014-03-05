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
require "minitest/autorun"
require "fc"

class TestFastContainers < MiniTest::Unit::TestCase
  def test_new_object_creation
    assert !FastContainers::PriorityQueue.new(:max).nil?
  end
  
  def test_new_handling_of_bad_parameter
    assert_raises(TypeError) do
      FastContainers::PriorityQueue.new(true)
    end
  end
  
  def test_push_returns_self
    pq = FastContainers::PriorityQueue.new(:max)
    assert_equal pq, pq.push("test",10)
  end
  
  def test_top_on_a_single_element_queue_returns_that_element
    pq = FastContainers::PriorityQueue.new(:max);
    pq.push("test",10)
    assert_equal "test", pq.top
  end
  
  def test_next_on_a_single_element_queue_returns_that_element
    pq = FastContainers::PriorityQueue.new(:max);
    pq.push("test",10)
    assert_equal "test", pq.next
  end
  
  
  def test_top_returns_the_maximal_element_in_a_max_queue
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal "30", pq.top
  end
  
  def test_next_returns_the_maximal_element_in_a_max_queue
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal "30", pq.next
  end
  

  def test_top_returns_the_minimal_element_in_a_min_queue
    pq = FastContainers::PriorityQueue.new(:min) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal "10", pq.top
  end
  
  def test_next_returns_the_minimal_element_in_a_min_queue
    pq = FastContainers::PriorityQueue.new(:min) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal "10", pq.next
  end

  def test_top_key_returns_the_top_priority
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal 30, pq.top_key
  end
  
  def test_next_key_returns_the_top_priority
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal 30, pq.next_key
  end
  
  
  def test_pop_removes_an_element_from_the_top
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    extracted = pq.pop
    
    assert_equal 20, pq.top_key
    assert_equal "30", extracted
  end
  
  def test_pop_raises_an_exception_if_the_queue_is_empty
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.pop
    assert_raises(RuntimeError) {
      pq.pop
    }
  end
  
  def test_empty_returns_false_if_the_queue_is_not_empty
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    assert !pq.empty?
  end
  
  def test_empty_returns_true_if_the_queue_is_empty
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    assert pq.empty?
  end
  
  def test_size_on_empty_queue
    pq = FastContainers::PriorityQueue.new(:max)
    assert_equal 0, pq.size
  end
  
  def test_size_on_non_empty_queue
    pq = FastContainers::PriorityQueue.new(:max)
    pq.push("x",10);
    pq.push("y",20);
    pq.push("z",30);
    assert_equal 3, pq.size
  end
  
  def test_enumerable
    pq = FastContainers::PriorityQueue.new(:max)
    pq.push(1,10);
    pq.push(2,20);
    pq.push(3,30);
    sum_o = 0
    sum_p = 0
    pq.map { |o,p| sum_o+=o; sum_p+=p }
    assert_equal sum_o, 6
    assert_equal sum_p, 60
  end
end
