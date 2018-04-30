#pragma once
#include <vector>

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

  // Is this needed - follow up from Guy
  void flush();

  // Assuming the size of the output is the same
  // as the number of elements in the tree
  void writeOut(int* output);
private:
  void rec_insert(BufferTreeNode* cur, int data);

};

class BufferTreeSort {
  BufferTree* T;
public:
  BufferTreeSort(int M, int B) {
    BufferTree T2(M, B);
    T = &T2;
  }
  void sort(int* in, int N, int* out) {
    for(int i = 0;i < N;i++) {
      T->insert(in[i]);
    }
    T->flush();
    T->writeOut(out);
  }
};
