#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include "priority_queue.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a
//           Fibonacci heap.
template <typename TYPE, typename COMP = std::less<TYPE>>
class fib_heap : public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

  // EFFECTS: Deconstruct the heap with no memory leak.
  // MODIFIES: this
  // RUNTIME: O(n)
  ~fib_heap();

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: Amortized O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

private:
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
  // You may want to define a strcut/class to represent nodes in the heap and a
  // pointer to the min node in the heap.
  struct node {
    TYPE val;
    node *parent = nullptr;
    std::list<node> child;
    size_type degree = 0;
  };
  std::list<node> root;
  typename std::list<node>::iterator H_min;
  size_type H_n = 0;

  void Consolidate();
  void fib_heap_link(typename std::list<node>::iterator x,
                     typename std::list<node>::iterator y);
};

template <typename TYPE, typename COMP> fib_heap<TYPE, COMP>::~fib_heap() {}

template <typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::Consolidate() {
  size_type D = floor(log(H_n));
  typename std::list<node>::iterator *A =
      new typename std::list<node>::iterator[D + 1];

  for (size_type ii = 0; ii <= D; ii++)
    A[ii] = root.end();

  for (typename std::list<node>::iterator ii = root.begin(); ii != root.end();
       ii++) {
    size_type d = ii->degree;
    typename std::list<node>::iterator x = ii;
    while (A[d] != root.end()) {
      typename std::list<node>::iterator y = A[d];
      if (compare(y->val, x->val))
        std::swap(x, y);
      fib_heap_link(x, y);
      A[d] = root.end();
      d = d + 1;
    }
  }
  H_min = root.begin();
  for (typename std::list<node>::iterator ii = root.begin()++; ii != root.end();
       ii++) {
    if (compare(ii->val, H_min->val))
      H_min = ii;
  }
  delete[] A;
  return;
}

template <typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::fib_heap_link(typename std::list<node>::iterator x,
                                         typename std::list<node>::iterator y) {

  x->child.splice(x->child.end(), root, y);
  x->degree++;
  return;
}

template <typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::fib_heap(COMP comp) {
  compare = comp;
  H_min = root.begin();
  H_n = 0;
}

template <typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::enqueue(const TYPE &val) {
  node x;
  x.val = val;
  if (root.empty()) {
    root.push_front(x);
    H_min = root.begin();
  } else if (compare(val, H_min->val)) {
    H_min = root.insert(H_min, x);
  } else {
    root.insert(H_min, x);
  }
  H_n++;
  return;
}

template <typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP>::dequeue_min() {
  if (empty())
    return TYPE();
  if (!H_min->child.empty()) {
    for (typename std::list<node>::iterator ii = H_min->child.begin();
         ii != H_min->child.end(); ii++) {
      ii->parent = nullptr;
      root.splice(H_min, H_min->child, ii);
    }
  }
  TYPE min = H_min->val;
  root.erase(H_min);
  H_n--;

  if (H_n == 0)
    H_min = root.begin();
  else
    Consolidate();
  return min;
}

template <typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP>::get_min() const {
  if (empty())
    return TYPE();
  return H_min->val;
}

template <typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP>::size() const {
  return H_n;
}

template <typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP>::empty() const {
  return H_n == 0;
}
#endif // FIB_HEAP_H
