#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include "k-merge.hpp"

KMergeSort::KMergeSort(int m, int b) {
  M = m;
  B = b;
}

void KMergeSort::sort(int* input, int n, int* output) {

  if (n <= M) {
    std::memcpy(output, input, sizeof(int) * n);
    std::sort(output, output + n);
    return;
  }

  // break into M/B peices

  int pieces = M/B;

  int* ends = new int[M/B];
  int* cur = new int[M/B];

  int** int_res = new int*[M/B];

  for (int i = 0;i < pieces;i++) {
    int s =  (n / (M / B)) * i;
    // end is exclusive
    int end = s + (n / (M / B));
    if (i + 1 == pieces) {
      end = n;
    }
    ends[i] = end - s;
    cur[i] = 0;
    int_res[i] = new int[end - s];

    sort(input + s, end - s, int_res[i]);
  }

  // // perform a k-way merge

  // // naive merge
  for (int i = 0;i < n;i++) {
    int m = INT_MAX;
    int id = -1;
    for (int j = 0;j < pieces;j++) {
      int comp = INT_MAX;
      if (cur[j] < ends[j]) {
        comp = int_res[j][cur[j]];
      }
      if (comp < m) {
        m = comp;
        id = j;
      }
    }
    output[i] = m;
    cur[id]++;
  }

  delete[] ends;
  delete[] cur;

  for(int i = 0;i < pieces;i++) {
    delete[] int_res[i];
  }
  delete[] int_res;
}
