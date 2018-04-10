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
    std::memcpy(output, input, n);
    std::sort(output, output + n);
    return;
  }

  // break into M/B peices

  int pieces = M/B;

  int* starts = new int[M/B];
  int* cur = new int[M/B];

  int** int_res = new int*[M/B];


  for (int i = 0;i < pieces;i++) {
    int s =  (n / (M / B)) * i;
    // end is exclusive
    int end = std::min(n, s + (n / (M / B)));
    starts[i] = s;
    cur[i] = 0;
    int_res[i] = new int[n / (M / B)];

    sort(input + s, end - s, int_res[i]);
  }

  // // perform a k-way merge

  // for (int i = 0;i < pieces;i++) {
  //   std::cout << starts[i] << std::endl;
  // }

  // // naive merge
  for (int i = 0;i < n;i++) {
    int m = INT_MAX;
    int id = -1;
    for (int j = 0;j < pieces;j++) {
      int comp = INT_MAX;
      if (cur[j] < (n / (M / B)) && (starts[j] + cur[j]) < n) {
        comp = int_res[j][starts[j] + cur[j]];
      }
      if (comp < m) {
        m = comp;
        id = j;
      }
    }
    output[i] = m;
    cur[id]++;
  }

  delete[] starts;
  std::cout << "end" << std::endl;
  delete[] cur;

  for(int i = 0;i < pieces;i++) {
    delete[] int_res[i];
  }
  delete[] int_res;

  // for (int i = 0;i < pieces;i++) {
  //   std::cout << starts[i] << std::endl;
  // }

  // std::cout << starts << " " << cur << std::endl;
  // std::cout << "before" << std::endl;
  // delete[] starts;
  // std::cout << "end" << std::endl;
  // delete[] cur;

  // for(int i = 0;i < pieces;i++) {
  //   delete[] int_res[i];
  // }
  // delete[] int_res;

}
