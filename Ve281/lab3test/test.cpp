#include "alg.h"
#include <iostream>

using namespace std;

int main() {
  int a[10] = {4, 2, 1, 5, 7, 3, 6, 10, 8, 9};
  bubble_sort(a, 10);
  for (int ii = 0; ii < 10; ii++) {
    cout << a[ii] << endl;
  }

  return 0;
}
