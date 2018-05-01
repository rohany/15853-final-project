#pragma once
#include <vector>
#include <iostream>

class BufferTreeNode {
public:
  int M, B;
  // Is this needed?
  bool isLeaf;

  BufferTreeNode* parent;
  std::vector<BufferTreeNode*> children;
  std::vector<int> pivots;

  // This will be all of the data of a leaf node,
  // or the buffer of an internal node.
  std::vector<int> buffer;
  int bufferCounter;
  int buflen;

  int mb;

  BufferTreeNode(int m, int b, bool leaf, BufferTreeNode* p) {
    M = m;
    B = b;
    isLeaf = leaf;
    parent = p;

    mb = M / B;

    buflen = M;

    if (isLeaf) {
      buflen = B;
    }
    // else {
    //   children.reserve(mb);
    // }

    // buffer.reserve(buflen);
  }
};

class BufferTree {
public:
  int M, B;

  int size;

  BufferTreeNode* root;

  // Assumption is that B | M
  BufferTree(int M, int B);

  void insert(int data);

  int getSize();

  void flush();

  void printTree(BufferTreeNode* cur);

  // Assuming the size of the output is the same
  // as the number of elements in the tree
  void writeOut(int* output);
private:
  void rec_insert(BufferTreeNode* cur, int data);
  void rec_flush(BufferTreeNode* cur);
  int rec_writeOut(BufferTreeNode* cur, int* output);

};

class BufferTreeSort {
  BufferTree* T;
public:
  BufferTreeSort(int M, int B) {
    T = new BufferTree(M, B);
  }
  void sort(int* in, int N, int* out) {
    for(int i = 0;i < N;i++) {
      T->insert(in[i]);
      // T->printTree(T->root);
      // std::cout << "NEW TREE\n";
    }
    // T->printTree(T->root);
    T->flush();
    // T->printTree(T->root);
    T->writeOut(out);
  }
};
