#ifndef FC_QUEUE_H_KTY6FH1S
#define FC_QUEUE_H_KTY6FH1S

#include <queue>

namespace fc_pq {
  typedef void* PQueue;
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
}

#endif /* end of include guard: FC_QUEUE_H_KTY6FH1S */


