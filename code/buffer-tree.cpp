#include <cstddef>
#include <new>
#include <algorithm>
#include <assert.h>

#include "buffer-tree.hpp"

/* BEGIN BUFFERTREENODE IMPLEMENTATION */

/*

High level idea for insert - 

insert into child

if child has too many children, split child into half, insert new element into current node, and return

beginning of tree - 
buffer of size m, once it hits m, sort it and create a root node.

*/


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
