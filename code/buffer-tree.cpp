#include <cstddef>
#include <new>
#include <algorithm>
#include <assert.h>

#include "buffer-tree.hpp"

/* BEGIN BUFFERTREENODE IMPLEMENTATION */

BufferTreeNode::BufferTreeNode(int m, int b, bool leaf, BufferTreeNode* p) {
  M = m;
  B = b;
  isLeaf = leaf;
  parent = p;

  mb = M / B;

  children = nullptr;

  buflen = M;

  if (isLeaf) {
    children = new BufferTreeNode*[mb];
    std::fill_n(children, mb, nullptr);
    buflen = B;
  }

  buffer = new int[buflen];
  bufferCounter = 0;
}

bool BufferTreeNode::insertIntoBuffer(int data) {
  assert(bufferCounter < buflen);
  buffer[bufferCounter] = data;
  bufferCounter++;
  return bufferCounter == buflen;
}

int BufferTreeNode::getBufferSize() {
  return bufferCounter;
}

/* END BUFFERTREENODE IMPLEMENTATION */

/* BEGIN BUFFERTREE IMPLEMENTATION */

BufferTree::BufferTree(int m, int b) {
  M = m;
  B = b;
  size = 0;

  // Not sure about this right now,
  // clarify with guy
  BufferTreeNode r(M, B, false, nullptr);
  root = &r;
}

void BufferTree::insert(int data) {
  //TODO: fill
}

int BufferTree::getSize() {
  return size;
}

void BufferTree::flush() {
  //TODO: fill
}

void BufferTree::writeOut(int* output) {
  //TODO: fill
}

/* END BUFFERTREEIMPLEMENTATION */
