#include <algorithm>
#include <iostream>
#include <string>

#include "k-merge.hpp"
#include "standard-sort.hpp"
#include "buffer-tree.hpp"

int main(int argc, char** argv) {

  int N, M, B;
  std::string mode;

  if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    std::cout << "Usage: ./sort <buffer or merge> n m b" << std::endl;
    return 0;
  }
  else if (argc < 5) {
    std::cout << "Usage: ./sort <buffer or merge> n m b" << std::endl;
    return 1;
  }
  else {
    mode = std::string(argv[1]);
    N = atoi(argv[2]);
    M = atoi(argv[3]);
    B = atoi(argv[4]);
  }

  std::cout << mode << N << M << B << std::endl;

  return 0;
}
