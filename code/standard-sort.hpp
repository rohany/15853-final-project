#pragma once
#include <algorithm>
#include <cstring>

class StandardSort {
public:
  void sort(int* input, int n, int* output) {
    std::memcpy(output, input, sizeof(int) * n);
    std::sort(output, output + n);
  }
};
