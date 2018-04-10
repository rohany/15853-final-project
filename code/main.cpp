#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>

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

  // Look into using mmap here?
  int* default_in = new int[N];
  int* default_out = new int[N];

  int* io_in = new int[N];
  int* io_out = new int[N];

  int* input = new int[N];

  std::cout << "Input allocation complete" << std::endl;

  std::generate(input, input + N, std::rand);

  std::memcpy(default_in, input, N);
  std::memcpy(io_in, input, N);

  std::cout << "Input generation complete" << std::endl;

  delete[] input;


  if (mode == "buffer") {
    std::cout << "not supported yet!" << std::endl;
    return 0;
  }
  else if (mode == "merge") {
    StandardSort stdsort;
    KMergeSort iosort(M, B);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    stdsort.sort(default_in, N, default_out);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Standard sort time elapsed = " <<
      std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() <<std::endl;

    // TODO: verify correctness

    delete[] default_in;
    delete[] default_out;

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();

    iosort.sort(io_in, N, io_out);

    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::cout << "IO efficient sort time elapsed = " <<
      std::chrono::duration_cast<std::chrono::seconds>(end2 - begin2).count() <<std::endl;

    // TODO: verify correctness

    delete[] io_in;
    delete[] io_out;

    return 0;
  }
  else {
    std::cout << "Unsupported sorting algorithm" << std::endl;
    return 1;
  }
}
