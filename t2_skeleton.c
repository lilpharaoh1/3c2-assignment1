#include <stdio.h> 
#include <stdlib.h>
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void printArrayInside(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void selectionSort(int arr[], int size) // FIX DECLARATIONS BEFORE SUBMIT
{ 
  for (int i = 0; i < size - 1; i++) { 
    int smallest_idx = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[smallest_idx]) { 
        smallest_idx = j;
      }
      number_comparisons += 1;
    }
    if (smallest_idx != i) {
      int tmp = arr[i];
      arr[i] = arr[smallest_idx];
      arr[smallest_idx] = tmp;
      number_swaps += 1;
    }
  }

  // printArrayInside(arr, size);
} 

void insertionSort(int arr[], int size) //FIX DECLARATIONS BEFORE SUBMIT
{ 
  for (int i = 1; i < size; i++) {
    for (int j = i; j > 0; j--) {
      if (arr[j] < arr[j - 1]) { 
        int tmp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = tmp;
        number_swaps += 1;
        number_comparisons += 1;
      }
      else { 
        number_comparisons += 1;
        break;
      }
    }
  }

  // printArrayInside(arr, size);
}

int partition(int * arr, int l, int r) {
  int pivot = r;
  r -= 1;

  while (l != r) { 
    while (arr[l] < arr[pivot] && l != r) { 
      number_comparisons += 1;
      l++;
    }
    number_comparisons += 1;

    while (arr[r] >= arr[pivot] && l != r) { 
      number_comparisons += 1;
      r--;
    }
    number_comparisons += 1;

    int tmp = arr[r];
    arr[r] = arr[l];
    arr[l] = tmp;
    number_swaps += 1;
  }

  // printf("l = %i, r = %i, pivot = %i\n", l, r, pivot);

  if (arr[pivot] <= arr[l]) {
    int tmp = arr[pivot];
    arr[pivot] = arr[l];
    arr[l] = tmp;
    number_swaps += 1;

    pivot = l;
  }

  return pivot;
}

void quickSortFunc(int * arr, int l, int r) {
  int q = 0;
  if (r > l) { 
    q = partition(arr, l, r);
    quickSortFunc(arr, l, q-1);
    quickSortFunc(arr, q+1, r);
  }
}

void quickSort(int arr[], int size) 
{
  quickSortFunc(arr, 0, size-1);
}


