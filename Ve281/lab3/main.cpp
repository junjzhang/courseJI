#include "alg.h"
#include <iostream>

using namespace std;

int main() {
  // get the input
  int count = 0;
  int select_flag, order = 0;
  long num;
  cin >> select_flag >> num;
  int *array = new int[num];
  if (select_flag >= 5) {
    cin.ignore(2048, '\n');
    cin.clear();
    cin >> order;
  }
  while (count < num) {
    cin.ignore(2048, '\n');
    cin.clear();
    cin >> array[count++];
  }
  switch (select_flag) {
  case 0:
    bubble_sort(array, num);
    break;
  case 1:
    insertion_sort(array, num);
    break;
  case 2:
    insertion_sort(array, num);
    break;
  case 3:
    merge_sort(array, 0, num - 1);
    break;
  case 4:
    quick_sort(array, 0, num - 1);
    break;
  case 5:
    cout << "The order-" << order << " item is "
         << random_select(array, 0, num - 1, order) << endl;
    break;
  case 6:
    cout << "The order-" << order << " item is "
         << determin_select(array, 0, num - 1, order) << endl;
    break;
  }
  if (select_flag < 5)
    print_array(array, num);
  delete[] array;
  return 0;
}