// Input: an integer array
// Output: yes or no
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
bool verifySquenceOfBST(vector<int> sequence);

int main() {
  vector<int> a({2, 1, 9, 4, 3, 6, 5});
  cout << verifySquenceOfBST(a) << endl;
  return 0;
}

bool verifySquenceOfBST(vector<int> sequence) {
  stack<int> s;
  int root = INT_MIN;
  for (size_t ii = 0; ii < sequence.size(); ii++) {
    if (sequence[ii] < root)
      return false;
    while (!s.empty() && s.top() < sequence[ii]) {
      root = s.top();
      s.pop();
    }
    s.push(sequence[ii]);
  }
  return true;
}
