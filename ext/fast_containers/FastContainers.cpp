// Include the Ruby headers and goodies
#include "ruby.h"
#include "fc_pq.h"

// Defining a space for information and references about the module to be stored internally
static VALUE FastContainers = Qnil;
static VALUE PriorityQueue = Qnil;

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
  VALUE data = Data_Wrap_Struct(klass, 0, fc_pq::destroy, queue);
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
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);

  fc_pq::push(queue, (void*)obj, NUM2DBL(priority));
  return self;
}

/*
 * call-seq:
 *    top -> obj
 *
 * Returns the object at the top of the priority queue.
 */
static VALUE pq_top(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  return (VALUE) fc_pq::top(queue);
}

/*
 * call-seq:
 *   top_key -> float
 *
 * Returns the priority of the object at the top of the priority queue.
 */
static VALUE pq_top_key(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  double priority = fc_pq::top_key(queue);
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
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
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
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  if( fc_pq::empty(queue) )
    return Qtrue;
  else
    return Qfalse;
}

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
    rb_define_singleton_method(PriorityQueue, "new", RUBY_METHOD_FUNC(pq_new), 1);
    rb_define_method(PriorityQueue, "push", RUBY_METHOD_FUNC(pq_push), 2);
    rb_define_method(PriorityQueue, "top", RUBY_METHOD_FUNC(pq_top), 0);
    rb_define_method(PriorityQueue, "top_key", RUBY_METHOD_FUNC(pq_top_key), 0);
    rb_define_method(PriorityQueue, "pop", RUBY_METHOD_FUNC(pq_pop), 0);
    rb_define_method(PriorityQueue, "empty?", RUBY_METHOD_FUNC(pq_empty), 0);
  }
}

