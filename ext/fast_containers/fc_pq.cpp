#include "fc_pq.h"
#include <iostream>

namespace fc_pq {
  
  typedef std::pair<void*,double> PQElem;
 
  class PairsComparator
  {
    bool reverse;
  public:
    PairsComparator(PQueueKind kind) {reverse=(kind==MIN_QUEUE);}
    bool operator() (const PQElem& lhs, const PQElem& rhs) const
    {
      if (reverse) return (lhs.second>rhs.second);
      else return (lhs.second<rhs.second);
    }
  };
  
  // --------------------------------------
  // PQueue
  // --------------------------------------
    
  typedef std::vector<PQElem> PQueueStorage;
  typedef struct _PQueue { 
    PQueueStorage storage;
    PairsComparator comparator;
    
    _PQueue(PQueueKind kind) : comparator(kind) { }
  }* PQueue;  

  void destroy(PQueue q){
    delete q;
  }
  
  PQueue create(PQueueKind kind) {
    return new _PQueue(kind);
  }
  
  void push(PQueue q, void* value, double priority) {
    q->storage.push_back(PQElem(value, priority));
    push_heap(q->storage.begin(), q->storage.end(), q->comparator);
  }
  
  void* top(PQueue q) {
    return q->storage.at(0).first;
  }
  
  double top_key(PQueue q) {
    return q->storage.at(0).second;
  }
  
  void pop(PQueue q) {
    pop_heap(q->storage.begin(), q->storage.end(), q->comparator);
    q->storage.pop_back();
  }
  
  bool empty(PQueue q) {
    return q->storage.empty();
  }
  
  // --------------------------------------
  // Iterator
  // --------------------------------------
  

  
  typedef struct _PQueueIterator {
    PQueueStorage::const_iterator iterator;
    PQueueStorage* queue;
    
    _PQueueIterator(PQueue q) {
      queue = &q->storage;
      iterator = q->storage.begin();      
    }
  } PQueueImplIterator;
  #define QIT(it) ((PQueueImplIterator*)(it))
  
  /* Returns a new iterator object */
  PQueueIterator iterator(PQueue q) {
    PQueueImplIterator* it = new PQueueImplIterator(q);
    return it;
  }
  
  void iterator_dispose(PQueueIterator it) {
    delete it;
  }
  
  /* Returns the value of the current element */
  void* iterator_get_value(PQueueIterator it) {
    return it->iterator->first;
  }
  
  /* Returns the priority of the current  element */
  double iterator_get_key(PQueueIterator it) {
    return it->iterator->second;
  }
  
  /* Moves on to the next element */
  PQueueIterator iterator_next(PQueueIterator it) {
    it->iterator++;
    return it;
  }
  
  bool iterator_end(PQueueIterator it) {
    return it->iterator == it->queue->end();
  }
}