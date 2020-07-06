#ifndef __ALG_H__
#define __ALG_H__

void bubble_sort(int *input, int n);
// EFFECTS: sort input array
// MODIFIES: *input

void insertion_sort(int *input, int n);
// EFFECTS: sort input array
// MODIFIES: *input

void selection_sort(int *input, int n);
// EFFECTS: sort input array
// MODIFIES: *input

void merge_sort(int *input, int left, int right);
// EFFECTS: sort input array
// MODIFIES: *input

void merge(int *input, int left, int mid, int right);
// EFFECTS:  merge the two sorted sub-array
// MODIFIES: *input

void quick_sort(int *input, int left, int right);
// EFFECTS: sort input array
// MODIFIES: *input

int partition(int *input, int left, int right, int pivot_index);
// EFFECTS: retrun the pivot's index and put all elements smaller than pivot
// to the left, others to the right. If pivot_index is -1, use random one.
// left, other wise to right MODIFIES: *input

int random_select(int *array, int left, int right, int order);
// EFFECTS: return the order-th smallest number
// MODIFIES: *array

int determin_select(int *array, int left, int right, int order);
// EFFECTS: return the order-th smallest number
// MODIFIES: *array

void print_array(int *array, int n);
// EFFECTS: print the array in form of standard output

#endif
