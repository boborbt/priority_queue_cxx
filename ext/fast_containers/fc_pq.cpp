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