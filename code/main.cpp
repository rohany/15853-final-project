#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <assert.h>
#include <sys/mman.h>

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
  // MMAP_ANON
  // int* default_in = new int[N];
  // int* default_out = new int[N];
  int* default_in = (int*)mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (default_in == MAP_FAILED) {
    std::cout << "mmap failed 1" << std::endl;
    exit(1);
  }
  int* default_out = (int*)mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (default_out == MAP_FAILED) {
    std::cout << "mmap failed 2" << std::endl;
    exit(1);
  }

  int* io_in = (int*)mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (io_in == MAP_FAILED) {
    std::cout << "mmap failed 3" << std::endl;
    exit(1);
  }
  int* io_out = (int*)mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (io_out == MAP_FAILED) {
    std::cout << "mmap failed 4" << std::endl;
    exit(1);
  }




  int* input = (int*)mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (input == MAP_FAILED) {
    std::cout << "mmap failed 5" << std::endl;
    exit(1);
  }

  std::cout << "Input allocation complete" << std::endl;

  std::iota(input, input + N, 0);
  std::random_shuffle(input, input + N);


  std::memcpy(default_in, input, sizeof(int) * N);
  std::memcpy(io_in, input, sizeof(int) * N);

  std::cout << "Input generation complete" << std::endl;

  munmap(input, N * sizeof(int));

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
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() <<std::endl;

    for(int i = 0;i < N;i++) {
      assert(default_out[i] == i);
    }

    munmap(default_in, N * sizeof(int));
    munmap(default_out, N * sizeof(int));

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();

    iosort.sort(io_in, N, io_out);

    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::cout << "IO efficient sort time elapsed = " <<
      std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count() <<std::endl;

    for(int i = 0;i < N;i++) {
      assert(io_out[i] == i);
    }

    munmap(io_in, N * sizeof(int));
    munmap(io_out, N * sizeof(int));

    return 0;
  }
  else {
    std::cout << "Unsupported sorting algorithm" << std::endl;
    return 1;
  }
}
