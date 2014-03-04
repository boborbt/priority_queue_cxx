// Copyright (c) 2014 Roberto Esposito
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#include "ruby.h"
#include "fc_pq.h"

// Defining a space for information and references about the module to be stored internally
static VALUE FastContainers = Qnil;
static VALUE PriorityQueue = Qnil;

// --------------------------------------------------------------------------------
// UTILITIES 
// --------------------------------------------------------------------------------

static fc_pq::PQueue pq_from_self(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, struct fc_pq::_PQueue, queue);
  
  return queue;
}

static void pq_mark(void *ptr) {
  if(ptr==NULL)
    return;
  
  fc_pq::PQueueIterator it = fc_pq::iterator((fc_pq::PQueue)ptr);
  while( !fc_pq::iterator_end(it) ) {
    rb_gc_mark( (VALUE) fc_pq::iterator_get_value(it) );
    it = fc_pq::iterator_next(it);
  }
  fc_pq::iterator_dispose(it);
}

// --------------------------------------------------------------------------------
// METHODS 
// --------------------------------------------------------------------------------

/*
 * call-seq:
 *    PriorityQueue.new(queue_kind) 
 *
 * Create a new priority queue and returns it.
 * +queue_kind+ specifies whether to build a :min or a :max queue.
 */
static VALUE pq_new(VALUE klass, VALUE queue_kind) {
  if( TYPE(queue_kind) != T_SYMBOL ) {
    rb_raise(rb_eTypeError, "queue_kind parameter must be a symbol");
  }
  
  fc_pq::PQueueKind kind;
  
  if( rb_intern("max") == rb_to_id(queue_kind) )
    kind = fc_pq::MAX_QUEUE;
  else if( rb_intern("min") == rb_to_id(queue_kind) )
    kind = fc_pq::MIN_QUEUE;
  else rb_raise(rb_eTypeError, "queue_kind parameter must be either :max or :min");
    
  fc_pq::PQueue queue = fc_pq::create(kind);
  VALUE data = Data_Wrap_Struct(klass, pq_mark, fc_pq::destroy, queue);
  rb_obj_call_init(data, 0, NULL);
  return data;
}

/*
 * call-seq:
 *    push(obj,priority) -> self
 *
 * Push the +obj+/+priority+ pair into the queue and returns self.
 */
static VALUE pq_push(VALUE self, VALUE obj, VALUE priority) {
  fc_pq::push(pq_from_self(self), (void*)obj, NUM2DBL(priority));
  return self;
}

/*
 * call-seq:
 *    top -> obj
 *
 * Returns the object at the top of the priority queue.
 */
static VALUE pq_top(VALUE self) {
  fc_pq::PQueue queue = pq_from_self(self);
  if( fc_pq::empty(queue) ) {
    return Qnil;
  }
  
  return (VALUE) fc_pq::top( queue );
}

/*
 * call-seq:
 *   top_key -> float
 *
 * Returns the priority of the object at the top of the priority queue.
 */
static VALUE pq_top_key(VALUE self) {
  double priority = fc_pq::top_key( pq_from_self(self) );
  return DBL2NUM(priority);
}

/*
 * call-seq:
 *     pop -> self
 *
 * Pops the top most element from the priority queue.
 * Returns self.
 */
static VALUE pq_pop(VALUE self) {
  fc_pq::PQueue queue = pq_from_self(self);
  
  if( fc_pq::empty(queue) )
    rb_raise(rb_eRuntimeError, "Pop called on an empty queue");
  
  fc_pq::pop(queue);
  return self;
}

/*
 * call-seq:
 *     empty?
 *
 * Returns true if the queue is empty
 */

static VALUE pq_empty(VALUE self) {
  if( fc_pq::empty(pq_from_self(self)) )
    return Qtrue;
  else
    return Qfalse;
}


/*
 * call-seq:
 *    each { |obj,priority| ... } -> self
 *
 * Iterates through the priority queue yielding each element to the given block.
 * The order of the yielded elements is not defined.
 * Returns self.
 */

static VALUE pq_each(VALUE self) {
  fc_pq::PQueue queue = pq_from_self(self);
  
  fc_pq::PQueueIterator iterator = fc_pq::iterator(queue);
  while( !fc_pq::iterator_end(iterator) ) {
    VALUE value = (VALUE) fc_pq::iterator_get_value(iterator);
    VALUE num = DBL2NUM(fc_pq::iterator_get_key(iterator));
    rb_yield_values( 2,value, num );
    fc_pq::iterator_next(iterator);
  }
  fc_pq::iterator_dispose(iterator);
  
  return self;
}

/*
 * call-seq:
 *    pop_each { |obj, priority| ... } -> self
 *
 * Iterates through the priority queue popping the top element and
 * yielding it to the block. The order of yielded elements is guaranteed
 * to be the priority order.
 * Returns self.
 */

static VALUE pq_pop_each(VALUE self) {
  fc_pq::PQueue queue= pq_from_self(self);
  while( !fc_pq::empty(queue) ) {
    VALUE value = (VALUE) fc_pq::top(queue);
    double key = fc_pq::top_key(queue);
    fc_pq::pop(queue);
    rb_yield_values(2, value, DBL2NUM(key));
  }
  
  return self;
}

// --------------------------------------------------------------------------------
// INITIALIZATION 
// --------------------------------------------------------------------------------

/*
 * Document-module: FastContainers
 * Exposes C++ implementation of some containers not defined in the standard ruby libraries.
 */

/*
 * Document-class: FastContainers::PriorityQueue
 * Implements priority queues through a C++ heap (using the standard std::priority_queue class)
 */
extern "C" {
  void Init_fast_containers() {
    FastContainers = rb_define_module("FastContainers");
    PriorityQueue = rb_define_class_under(FastContainers, "PriorityQueue", rb_cObject);
    rb_global_variable(&FastContainers);
    rb_global_variable(&PriorityQueue);
    
    rb_define_singleton_method(PriorityQueue, "new", RUBY_METHOD_FUNC(pq_new), 1);
    rb_define_method(PriorityQueue, "push",     RUBY_METHOD_FUNC(pq_push), 2);
    rb_define_method(PriorityQueue, "top",      RUBY_METHOD_FUNC(pq_top), 0);
    rb_define_method(PriorityQueue, "top_key",  RUBY_METHOD_FUNC(pq_top_key), 0);
    rb_define_method(PriorityQueue, "pop",      RUBY_METHOD_FUNC(pq_pop), 0);
    rb_define_method(PriorityQueue, "empty",    RUBY_METHOD_FUNC(pq_empty), 0);
    rb_define_method(PriorityQueue, "each",     RUBY_METHOD_FUNC(pq_each), 0);
    rb_define_method(PriorityQueue, "pop_each", RUBY_METHOD_FUNC(pq_pop_each), 0);
  }
}
