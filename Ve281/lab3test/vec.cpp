#include "vec.h"
#include <iostream>

using namespace std;

vec::vec() : array(nullptr), size(0) {}

vec::vec(const vec &v) : array(new int[v.size]), size(v.size) {
  for (int ii = 0; ii < size; ii++) {
    array[ii] = v.array[ii];
  }
}

vec::vec(int n) : array(new int[n]), size(n) {}

vec::vec(const vec &v, int begin, int end)
    : array(new int[begin - end + 1]), size(begin - end + 1) {
  for (int ii = begin; ii < end + 1; ii++) {
    array[ii - begin] = v.array[ii];
  }
}

vec::~vec() {
  if (array != nullptr)
    delete[] array;
  size = 0;
}

int vec::get_size() { return size; }

int &vec::operator[](int i) { return array[i]; }

void vec::output() {
  for (int ii = 0; ii < size; ii++) {
    cout << array[ii] << endl;
  }
  return;
}