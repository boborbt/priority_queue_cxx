require "minitest/autorun"
require "fast_containers"

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
  
  def test_top_returns_the_maximal_element_in_a_max_queue
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal "30", pq.top
  end

  def test_top_returns_the_minimal_element_in_a_min_queue
    pq = FastContainers::PriorityQueue.new(:min) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal "10", pq.top
  end

  def test_top_key_returns_the_top_priority
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    assert_equal 30, pq.top_key
  end
  
  def test_pop_removes_an_element_from_the_top
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    pq.push("10", 10)
    pq.push("30", 30)
    pq.push("20", 20)
    pq.pop
    
    assert_equal 20, pq.top_key
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
    assert !pq.empty();
  end
  
  def test_empty_returns_true_if_the_queue_is_empty
    pq = FastContainers::PriorityQueue.new(:max) # this is a max queue
    assert pq.empty();
  end
end
