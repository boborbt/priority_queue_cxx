// Include the Ruby headers and goodies
#include "ruby.h"
#include "fc_pq.h"


// Defining a space for information and references about the module to be stored internally
static VALUE FastContainers = Qnil;
static VALUE PriorityQueue = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
extern "C" { 
  void Init_fast_containers(); 

  /* Constructor. It defaults to construct a max queue. If true is passed
  it construct a min queue.*/
  VALUE pq_new(VALUE klass, VALUE min_queue);
  
  /* Destructor. Returns nil */
  // VALUE pq_delete(VALUE self);
  // 

  /* Adding elements */
  VALUE pq_push(VALUE self, VALUE value, VALUE priority);
  
  /* Inspecting the queue top (for values) */
  VALUE pq_top(VALUE self);
  
  /* Inspecting the queue top (for priorities) */
  VALUE pq_top_key(VALUE q);
  
  /* Removing the queue top */
  VALUE pq_pop(VALUE q);

  /* Returns true iff the queue is empty */
  VALUE pq_empty(VALUE q);
}

// The initialization method for this module
extern "C" {
  void Init_fast_containers() {
    FastContainers = rb_define_module("FastContainers");
    PriorityQueue = rb_define_class_under(FastContainers, "PriorityQueue", rb_cObject);
    rb_define_singleton_method(PriorityQueue, "new", (VALUE(*)(ANYARGS))pq_new, 1);
    rb_define_method(PriorityQueue, "push", (VALUE(*)(ANYARGS)) pq_push, 2);
    rb_define_method(PriorityQueue, "top", (VALUE(*)(ANYARGS)) pq_top, 0);
    rb_define_method(PriorityQueue, "top_key", (VALUE(*)(ANYARGS)) pq_top_key, 0);
    rb_define_method(PriorityQueue, "pop", (VALUE(*)(ANYARGS)) pq_pop, 0);
    rb_define_method(PriorityQueue, "empty", (VALUE(*)(ANYARGS)) pq_empty, 0);
  }
}

/*
 * Create a new priority queue and returns it.
 * @param queue_kind [Symbol] specifies whether to build a :min or a :max queue.
 */

VALUE pq_new(VALUE klass, VALUE queue_kind) {
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
 * Push a new key/value pair into the queue and returns self.
 * @param obj [Object] the object to be stored into the queue
 * @param priority [Float] the priority of the object to be inserted
 * @return [FastContainers::PriorityQueue] self
 */
VALUE pq_push(VALUE self, VALUE obj, VALUE priority) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);

  fc_pq::push(queue, (void*)obj, NUM2DBL(priority));
  return self;
}

/*
 * @return [Object] the object at the top of the priority queue.
 */
VALUE pq_top(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  return (VALUE) fc_pq::top(queue);
}

/*
 * @return [Float] the priority of the object at the top of the priority queue.
 */
VALUE pq_top_key(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  double priority = fc_pq::top_key(queue);
  return DBL2NUM(priority);
}

/*
 * Pops the top most element from the priority queue.
 * @return [FastContainers::PriorityQueue] self
 */
VALUE pq_pop(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  if( fc_pq::empty(queue) )
    rb_raise(rb_eRuntimeError, "Pop called on an empty queue");
  
  fc_pq::pop(queue);
  return self;
}

/*
 * @return [TrueClass,FalseClass] true if the queue is empty
 */

VALUE pq_empty(VALUE self) {
  fc_pq::PQueue queue;
  Data_Get_Struct(self, fc_pq::PQueue, queue);
  
  if( fc_pq::empty(queue) )
    return Qtrue;
  else
    return Qfalse;
}

