#include "alg.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void bubble_sort(int *input, int n) {
  for (int ii = 0; ii < n - 1; ii++) {
    for (int jj = 0; jj < n - 1 - ii; jj++) {
      if (input[jj] > input[jj + 1]) {
        int temp = input[jj];
        input[jj] = input[jj + 1];
        input[jj + 1] = temp;
      }
    }
  }
  return;
}

void insertion_sort(int *input, int n) {
  for (int ii = 1; ii < n; ii++) {
    int cand = input[ii];
    int jj = ii - 1;
    while (cand < input[jj] && jj >= 0) {
      input[jj + 1] = input[jj];
      jj--;
    }
    input[jj + 1] = cand;
  }
  return;
}

void selection_sort(int *input, int n) {
  for (int ii = 0; ii < n - 1; ii++) {
    for (int jj = ii + 1; jj < n; jj++) {
      if (input[jj] < input[ii]) {
        int temp = input[jj];
        input[jj] = input[ii];
        input[ii] = temp;
      }
    }
  }
  return;
}

void merge_sort(int *input, int left, int right) {
  if (left >= right)
    return;
  int mid = (left + right) / 2;
  merge_sort(input, left, mid);
  merge_sort(input, mid + 1, right);
  merge(input, left, mid, right);
}

void merge(int *input, int left, int mid, int right) {
  int l_index = 0, r_index = 0, index = left;
  int *l_array = new int[mid - left + 1];
  int *r_array = new int[right - mid];
  for (int ii = 0; ii < mid - left + 1; ii++) {
    l_array[ii] = input[ii + left];
  }
  for (int ii = 0; ii < right - mid; ii++) {
    r_array[ii] = input[ii + mid + 1];
  }
  while (l_index < (mid - left + 1) && r_index < (right - mid)) {
    input[index++] = l_array[l_index] < r_array[r_index] ? l_array[l_index++]
                                                         : r_array[r_index++];
  }
  while (l_index < (mid - left + 1)) {
    input[index++] = l_array[l_index++];
  }
  while (r_index < (right - mid)) {
    input[index++] = r_array[r_index++];
  }
  delete[] l_array;
  delete[] r_array;
  return;
}

void quick_sort(int *input, int left, int right) {
  if (left >= right)
    return;
  int pivot_index = partition(input, left, right, -1);
  quick_sort(input, left, pivot_index - 1);
  quick_sort(input, pivot_index + 1, right);
}

int partition(int *input, int left, int right, int pivot_index) {
  if (pivot_index == -1)
    pivot_index = (rand() % (right - left + 1)) + left;
  int pivot = input[pivot_index];
  if (pivot_index != left) {
    input[pivot_index] = input[left];
    input[left] = pivot;
  }
  while (left < right) {
    while (left < right && input[right] >= pivot) {
      right--;
    }
    input[left] = input[right];
    while (left < right && input[left] <= pivot) {
      left++;
    }
    input[right] = input[left];
  }
  input[left] = pivot;
  return left;
}

int random_select(int *array, int left, int right, int order) {
  if (left >= right)
    return array[left];
  int pivot_index = partition(array, left, right, -1);
  if (pivot_index == order)
    return array[pivot_index];
  if (pivot_index > order)
    return random_select(array, left, pivot_index - 1, order);
  else
    return random_select(array, pivot_index + 1, right, order);
}

int determin_select(int *array, int left, int right, int order) {
  if (left >= right)
    return array[left];
  int n = right - left + 1;
  int pivot_index = 0;
  int num_groups = ((right - left + 1) % 5 == 0) ? n / 5 : n / 5 + 1;
  // split into 5-groups and sort each one. Get the median array
  int *median_array = new int[num_groups];
  for (int ii = 0; ii < num_groups; ii++) {
    if (ii == num_groups - 1) {
      insertion_sort(array + left + 5 * ii, n + 5 - num_groups * 5);
      median_array[ii] = array[left + 5 * ii + (n + 5 - num_groups * 5) / 2];
    } else {
      insertion_sort(array + left + 5 * ii, 5);
      median_array[ii] = array[left + 5 * ii + 2];
    }
  }
  int pivot = determin_select(median_array, 0, num_groups - 1, num_groups / 2);
  delete[] median_array;
  // get the pivot's index
  for (int ii = left; ii < right + 1; ii++) {
    if (pivot == array[ii]) {
      pivot_index = ii;
      break;
    }
  }
  // patition
  pivot_index = partition(array, left, right, pivot_index);
  if (pivot_index == order)
    return array[pivot_index];
  if (pivot_index > order)
    return determin_select(array, left, pivot_index - 1, order);
  else
    return determin_select(array, pivot_index + 1, right, order);
}

void print_array(int *array, int n) {
  for (int ii = 0; ii < n; ii++) {
    cout << array[ii] << endl;
  }
  return;
}
