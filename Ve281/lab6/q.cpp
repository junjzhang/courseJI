#include <iostream>
#include <vector>

using namespace std;

void enqueue(int k) {
  heap.push_back(k);
  size_t ii = heap.size(-1);
  while (ii) {
    size_t jj = (ii - 1) / d;
    if (heap[ii] < heap[jj]) {
      swap(heap[ii], heap[jj]);
      ii = jj;
    } else
      break;
  }
}

int main() {
  vector<int> heap;
  int d;
  return 0;
}