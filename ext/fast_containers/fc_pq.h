#ifndef FC_QUEUE_H_KTY6FH1S
#define FC_QUEUE_H_KTY6FH1S

#include <queue>

namespace fc_pq {
  typedef struct _PQueue* PQueue;
  typedef struct _PQueueIterator* PQueueIterator;
  typedef enum { MIN_QUEUE, MAX_QUEUE } PQueueKind;
  
  /* Constructor. It defaults to construct a max queue. If true is passed
  it construct a min queue.*/  
  PQueue create(PQueueKind kind);
  
  /* Destructor */
  void destroy(PQueue q); 
  
  /* Adding elements */
  void push(PQueue q, void* value, double priority);
  
  /* Inspecting the queue top (for values) */
  void* top(PQueue q);
  
  /* Inspecting the queue top (for priorities) */
  double top_key(PQueue q);
  
  /* Removing the queue top */
  void pop(PQueue q);
  
  /* Returns true if the queue is empty */
  bool empty(PQueue q);
  
  /* Returns a new iterator object */
  PQueueIterator iterator(PQueue q);
  
  /* Dispose the iterator */
  void iterator_dispose(PQueueIterator it);
  
  /* Returns the value of the current element */
  void* iterator_get_value(PQueueIterator it);
  
  /* Returns the priority of the current  element */
  double iterator_get_key(PQueueIterator it);
  
  /* Moves on to the next element */
  PQueueIterator iterator_next(PQueueIterator it);
  
  /* Return true if the iterator is already out of the container */
  bool iterator_end(PQueueIterator it);
}

#endif /* end of include guard: FC_QUEUE_H_KTY6FH1S */


