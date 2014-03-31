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
  typedef unsigned int PQueueStorageVersion;

  typedef struct _PQueue {
    PQueueStorage storage;
    PairsComparator comparator;
    PQueueStorageVersion version;

    _PQueue(PQueueKind kind) : comparator(kind), version(0) { }
  }* PQueue;

  void destroy(PQueue q){
    delete q;
  }

  PQueue create(PQueueKind kind) {
    return new _PQueue(kind);
  }

  /* Getting the size of the container */
  unsigned int size(PQueue q) {
     return q->storage.size();
  }


  void push(PQueue q, void* value, double priority) {
    q->version++;
    q->storage.push_back(PQElem(value, priority));
    push_heap(q->storage.begin(), q->storage.end(), q->comparator);
  }

  void* top(PQueue q) {
    return q->storage.at(0).first;
  }

  double top_key(PQueue q) {
    return q->storage.at(0).second;
  }

  double second_best_key(PQueue q) {
     if(q->storage.size()==2)
        return q->storage.at(1).second;

     double key1 = q->storage.at(1).second;
     double key2 = q->storage.at(2).second;
     if( key1 > key2 ) {
        return key1;
     } else {
        return key2;
     }
  }

  void pop(PQueue q) {
    q->version++;
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
    PQueue pqueue;
    PQueueStorage* storage;
    PQueueStorageVersion version;

    _PQueueIterator(PQueue q) : iterator(q->storage.begin()), pqueue(q), storage(&q->storage), version(q->version)
      { }

    void checkVersion() throw(PQueueException) {
      if(version != pqueue->version) {
        throw PQueueException("FastContainers::PriorityQueue - a change in the priority queue invalidated the current iterator.");
      }
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
  PQueueIterator iterator_next(PQueueIterator it) throw(PQueueException) {
    it->checkVersion();
    it->iterator++;
    return it;
  }

  bool iterator_end(PQueueIterator it) {
    return it->iterator == it->storage->end();
  }
}
