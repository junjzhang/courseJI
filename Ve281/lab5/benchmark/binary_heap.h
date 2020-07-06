#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "priority_queue.h"
#include <algorithm>

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template <typename TYPE, typename COMP = std::less<TYPE>>
class binary_heap : public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  binary_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(log(n))
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
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;

private:
  void percolate_up(int id);

  void percolate_down(int id);
};

template <typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::percolate_up(int id) {
  while (id > 1 && compare(data[id], data[id / 2])) {
    std::swap(data[id], data[id / 2]);
    id /= 2;
  }
  return;
}

template <typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::percolate_down(int id) {
  size_type n = size();
  for (int ii = 2 * id; ii <= n; ii = 2 * id) {
    if (ii < n && compare(data[ii + 1], data[ii]))
      ii++;
    if (!compare(data[ii], data[id]))
      break;
    std::swap(data[ii], data[id]);
    id = ii;
  }
  return;
}

template <typename TYPE, typename COMP>
binary_heap<TYPE, COMP>::binary_heap(COMP comp) {
  compare = comp;
  data.push_back(TYPE());
}

template <typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::enqueue(const TYPE &val) {
  data.push_back(val);
  percolate_up(size());
  return;
}

template <typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP>::dequeue_min() {
  if (empty())
    return data[0];
  TYPE min = data[1];
  data[1] = data.back();
  data.pop_back();
  percolate_down(1);
  return min;
}

template <typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP>::get_min() const {
  if (empty())
    return data[0];
  return data[1];
}

template <typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP>::empty() const {
  return data.size() == 1;
}

template <typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP>::size() const {
  return data.size() - 1;
}

#endif // BINARY_HEAP_H
