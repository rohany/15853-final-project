#pragma once

class BufferTreeNode {
public:
  int M, B;
  // Is this needed?
  bool isLeaf;

  BufferTreeNode* parent;
  BufferTreeNode** children;

  BufferTreeNode(int M, int B, bool isLeaf, BufferTreeNode* parent);

  // requires the buffer has room
  // returns whether or not the buffer is full
  bool insertIntoBuffer(int data);

  // unsure if this is necessary
  int getBufferSize();

  // More will be added as we go

private:
  // This will be all of the data of a leaf node,
  // or the buffer of an internal node.
  int* buffer;
  int bufferCounter;
  int buflen;

  int mb;

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

};
