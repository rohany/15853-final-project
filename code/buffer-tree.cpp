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
  rec_insert(root, data);
  size++;

  if (root->children.size() > root->mb) {
    BufferTreeNode r(M, B, false, nullptr);
    BufferTreeNode c2(M, B, false, &r);

    int mid = root->pivots.size() / 2;
    auto midPivotIter = root->pivots.begin() + mid;
    auto midChildIter = root->children.begin() + mid;

    r.children.push_back(root);
    r.children.push_back(&c2);

    c2.pivots = std::vector<int>(midPivotIter, root->pivots.end());
    root->pivots = std::vector<int>(root->pivots.begin(), midPivotIter);
 
    c2.children = std::vector<BufferTreeNode*>(midChildIter, root->children.end());
    root->children = std::vector<BufferTreeNode*>(root->children.begin(), midChildIter);

    r.pivots.push_back(root->pivots[0]);
    r.pivots.push_back(c2.pivots[0]);

    root = &r;
  }
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

      if (cur->children.size() == 0) {
        int size = cur->M / cur->B;
        for (int i = 0; i < size; i++) {
          BufferTreeNode n(M, B, true, cur);
          cur->children.push_back(&n);
          cur->pivots.push_back(cur->buffer[i * B]);
          auto startIter = cur->buffer.begin() + i * B;
          auto endIter = cur->buffer.begin() + (i + 1) * B;
          n.buffer = std::vector<int>(startIter, endIter);
        }
        cur->buffer = std::vector<int>();
        return;
      }

      for (int i = 0;i < cur->buffer.size();i++) {
        auto it = std::lower_bound(cur->pivots.begin(), cur->pivots.end(), cur->buffer[i]);
        int idx = std::distance(cur->pivots.begin(), it);
        // is this the right child - i think lower bound works here
        rec_insert(cur->children[idx], cur->buffer[i]);
        // rebalance the child node now
        // if child is a leaf
        if (cur->children[idx]->isLeaf &&
            (cur->children[idx]->buffer.size() >= cur->children[idx]->buflen)) {
          // split chilren[idx], who is a leaf
          // @RAHUL CHECK THAT THIS MAKES SENSE
          int mid = cur->children[idx]->buflen / 2;
          auto midIter = cur->children[idx]->buffer.begin() + mid;

          BufferTreeNode n1(M, B, true, cur);
          BufferTreeNode n2(M, B, true, cur);

          n1.buffer = std::vector<int>(cur->children[idx]->buffer.begin(), midIter);
          n2.buffer = std::vector<int>(midIter, cur->children[idx]->buffer.end());

          // at this point, cur->pivots[i] contains an element that is
          // larger than all elements in n1 and n2, and cur->pivots[i-1]
          // contains n1.buffer[0]
          cur->pivots.insert(cur->pivots.begin() + idx, n2.buffer[0]);
          cur->children[idx] = &n2;
          cur->children.insert(cur->children.begin() + idx, &n1);

        } else if (cur->children[idx]->children.size() > cur->children[idx]->mb) {
          // split children[idx], which is an internal node
          int mid = cur->children[idx]->pivots.size() / 2;
          auto midPivotIter = cur->children[idx]->pivots.begin() + mid;
          auto midChildIter = cur->children[idx]->children.begin() + mid;
	  
          BufferTreeNode n(M, B, false, cur);
          cur->children.insert(cur->children.begin() + idx + 1, &n);

          n.pivots = std::vector<int>(midPivotIter, cur->children[idx]->pivots.end());
          cur->children[idx]->pivots = std::vector<int>(cur->children[idx]->pivots.begin(), midPivotIter);
 
          n.children = std::vector<BufferTreeNode*>(midChildIter, cur->children[idx]->children.end());
          cur->children[idx]->children = std::vector<BufferTreeNode*>(cur->children[idx]->children.begin(), midChildIter);

          int pivot = n.pivots[0];
          cur->pivots.insert(cur->pivots.begin() + idx + 1, pivot);
        }
      }
      cur->buffer = std::vector<int>();
    }
  }
}
/* END BUFFERTREEIMPLEMENTATION */
