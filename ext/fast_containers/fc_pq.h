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
#ifndef FC_QUEUE_H_KTY6FH1S
#define FC_QUEUE_H_KTY6FH1S

#include <queue>
#include <stdexcept>

namespace fc_pq {
  class PQueueException : public std::runtime_error {
  public:
    PQueueException(const char* msg) : std::runtime_error(msg) {}
  };

  typedef struct _PQueue* PQueue;
  typedef struct _PQueueIterator* PQueueIterator;
  typedef enum { MIN_QUEUE, MAX_QUEUE } PQueueKind;

  /* Constructor. It defaults to construct a max queue. If true is passed
  it construct a min queue.*/
  PQueue create(PQueueKind kind);

  /* Destructor */
  void destroy(PQueue q);

  /* Getting the size of the container */
  unsigned int size(PQueue q);

  /* Adding elements */
  void push(PQueue q, void* value, double priority);

  /* Inspecting the queue top (for values) */
  void* top(PQueue q);

  /* Inspecting the queue top (for priorities) */
  double top_key(PQueue q);

 /* Returns the priority of the next best element */
  double second_best_key(PQueue q);

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
  PQueueIterator iterator_next(PQueueIterator it) throw(PQueueException);

  /* Return true if the iterator is already out of the container */
  bool iterator_end(PQueueIterator it);
}

#endif /* end of include guard: FC_QUEUE_H_KTY6FH1S */
