#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> min;
  vector<double> max;
  double num;
  // input
  while (cin.good()) {
    cin >> num;
    // size is even
    if ((min.size() + max.size()) % 2 == 1) {
      if (max.size() > 0 && num < max[0]) {
        max.push_back(num);
        push_heap(max.begin(), max.end(), less<double>());
        min.push_back(max[0]);
        push_heap(min.begin(), min.end(), greater<double>());
        pop_heap(max.begin(), max.end(), less<double>());
        max.pop_back();
      } else {
        min.push_back(num);
        push_heap(min.begin(), min.end(), greater<double>());
      }
      cout << (max[0] + min[0]) / 2 << endl;
    } // size is odd
    else {
      if (min.size() > 0 && num > min[0]) {
        min.push_back(num);
        push_heap(min.begin(), min.end(), greater<double>());
        max.push_back(min[0]);
        push_heap(max.begin(), max.end(), less<double>());
        pop_heap(min.begin(), min.end(), greater<double>());
        min.pop_back();
      } else {
        max.push_back(num);
        push_heap(max.begin(), max.end(), less<double>());
      }
      cout << max[0] << endl;
    }
    cin.clear();
  }
  return 0;
}
