#include "fc_pq.h"
#include <iostream>
#include <queue>

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

  typedef std::priority_queue<PQElem, std::vector<PQElem>, PairsComparator> PQueueImpl;
  #define Q(q) ((PQueueImpl*)(q))
  
  void destroy(PQueue q){
    delete Q(q);  
  }
  
  PQueue create(PQueueKind kind) {
    return (PQueue)new PQueueImpl(PairsComparator(kind));
  }
  
  void push(PQueue q, void* value, double priority) {
    Q(q)->push(PQElem(value, priority));
  }
  void* top(PQueue q) {
    return Q(q)->top().first;
  }
  
  double top_key(PQueue q) {
    return Q(q)->top().second;
  }
  
  void pop(PQueue q) {
    Q(q)->pop();
  }
  
  bool empty(PQueue q) {
    return Q(q)->empty();
  }
}