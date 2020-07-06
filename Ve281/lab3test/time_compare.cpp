#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int main() {
  auto start1 = chrono::steady_clock::now();
  for (int ii = 0; ii < 13; ii++) {
    int num = pow(2, ii);
    int *array = new int[num];
    for (int jj = 0; jj < num; jj++) {
      array[jj] = mrand48();
    }
  }

  auto end1 = chrono::steady_clock::now();
  chrono::duration<double, std::micro> elapsed = end1 - start1;
  cout << elapsed.count() << endl;
  return 0;
}