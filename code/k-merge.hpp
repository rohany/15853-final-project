#pragma once

class KMergeSort {
public:
  KMergeSort(int M, int B);

  void sort(int* input, int n, int* output);
private:
  int M, B;
};
