#include <algorithm>
#include <functional>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

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

  // perform a k-way merge

  auto cmp = [](std::pair<int, int> l, std::pair<int, int> r) {
    return l.first > r.first;
  };
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,  decltype(cmp)> heap(cmp);
  for (int i = 0;i < pieces;i++) {
    heap.push(std::pair<int, int>(int_res[i][0], i));
  }

  int i = 0;
  while (i < n) {
    auto p = heap.top();
    output[i] = p.first;
    cur[p.second]++;

    heap.pop();
    if (cur[p.second] < ends[p.second]) {
      heap.push(std::pair<int, int>(int_res[p.second][cur[p.second]], p.second));
    }
    i++;
  }

  delete[] ends;
  delete[] cur;

  for(int i = 0;i < pieces;i++) {
    delete[] int_res[i];
  }
  delete[] int_res;
}
