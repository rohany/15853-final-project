#include <cstddef>
#include <new>
#include <algorithm>
#include <vector>
#include <assert.h>

#include "buffer-tree.hpp"

/*

High level idea for insert - 

insert into child

if child has too many children, split child into half, insert new element into current node, and return

beginning of tree - 
buffer of size m, once it hits m, sort it and create a root node.

*/

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

// assume unique elements only?
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

void BufferTree::rec_insert(BufferTreeNode* cur, int data) {
  if (cur->isLeaf) {
    auto it = std::lower_bound(cur->buffer.begin(), cur->buffer.end(), data);
    cur->buffer.insert(it, data);
  } else {
    cur->buffer.push_back(data);
    if (cur->buffer.size() >= cur->buflen) {
      // recursive inserts
      std::sort(cur->buffer.begin(), cur->buffer.end());

      for (int i = 0;i < cur->buffer.size();i++) {
        auto it = std::lower_bound(cur->pivots.begin(), cur->pivots.end(), cur->buffer[i]);
        int idx = std::distance(cur->pivots.begin(), it);
        // is this the right child - i think lower bound works here
        rec_insert(cur->children[i], cur->buffer[i]);
        // rebalance the child node now
        // if child is a leaf
        if (cur->children[i]->isLeaf &&
            (cur->children[i]->buffer.size() >= cur->children[i]->buflen)) {
          // split chilren[i], who is a leaf
          // @RAHUL CHECK THAT THIS MAKES SENSE
          int mid = cur->children[i]->buflen / 2;
          auto midIter = cur->children[i]->buffer.begin() + mid;

          BufferTreeNode n1(M, B, true, cur);
          BufferTreeNode n2(M, B, true, cur);

          n1.buffer = std::vector<int>(cur->children[i]->buffer.begin(), midIter);
          n2.buffer = std::vector<int>(midIter, cur->children[i]->buffer.end());

          // at this point, cur->pivots[i] contains an element that is
          // larger than all elements in n1 and n2, and cur->pivots[i-1]
          // contains n1.buffer[0]
          cur->pivots.insert(cur->pivots.begin() + i, n2.buffer[0]);
          cur->children[i] = &n2;
          cur->children.insert(cur->children.begin() + i, &n1);

        } else if (cur->children[i]->children.size() > cur->children[i]->mb) {
          // split children[i], who is an internal node
        }
      }
    }
  }
}
/* END BUFFERTREEIMPLEMENTATION */
