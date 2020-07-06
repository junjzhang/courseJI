#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include "alg.h"

using namespace std;

int main() {
  for (int ii = 16; ii < 23; ii++) {
    int num = pow(2, ii);
    int *array = new int[num];
    for (int jj = 0; jj < num; jj++) {
      array[jj] = mrand48();
    }
    //int order = rand() % (num+1);
    auto start = chrono::steady_clock::now();
    quick_sort(array,0,num-1);
    auto end = chrono::steady_clock::now();
    chrono::duration<double, micro> elapsed = end - start;
    cout << elapsed.count() << endl;
    delete[] array;
  }
  return 0;
}
