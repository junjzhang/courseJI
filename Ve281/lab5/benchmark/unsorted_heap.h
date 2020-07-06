#ifndef UNSORTED_HEAP_H
#define UNSORTED_HEAP_H

#include "priority_queue.h"
#include <algorithm>

// OVERVIEW: A specialized version of the 'heap' ADT that is implemented with
//           an underlying unordered array-based container. Every time a min
//           is required, a linear search is performed.
template <typename TYPE, typename COMP = std::less<TYPE>>
class unsorted_heap : public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  unsorted_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(n)
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(n)
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
  // Add any additional member functions or data you require here.
};

template <typename TYPE, typename COMP>
unsorted_heap<TYPE, COMP>::unsorted_heap(COMP comp) {
  compare = comp;
  data.push_back(TYPE());
}

template <typename TYPE, typename COMP>
void unsorted_heap<TYPE, COMP>::enqueue(const TYPE &val) {
  data.push_back(val);
  return;
}

template <typename TYPE, typename COMP>
TYPE unsorted_heap<TYPE, COMP>::dequeue_min() {
  if (empty())
    return data[0];
  typename std::vector<TYPE>::iterator min_at =
      std::min_element(data.begin() + 1, data.end(), compare);
  TYPE min = *min_at;
  *min_at = data.back();
  data.pop_back();
  return min;
}

template <typename TYPE, typename COMP>
const TYPE &unsorted_heap<TYPE, COMP>::get_min() const {
  if (empty())
    return data[0];
  return *(std::min_element(data.begin() + 1, data.end(), compare));
}

template <typename TYPE, typename COMP>
bool unsorted_heap<TYPE, COMP>::empty() const {
  return data.size() == 1;
}

template <typename TYPE, typename COMP>
unsigned unsorted_heap<TYPE, COMP>::size() const {
  return data.size() - 1;
}

#endif // UNSORTED_HEAP_H
