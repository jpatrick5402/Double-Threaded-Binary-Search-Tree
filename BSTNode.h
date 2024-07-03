// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E>
{
private:
  Key k;       // The node's key
  E it;        // The node's value
  BSTNode *lc; // Pointer to left child
  BSTNode *rc; // Pointer to right child

  bool lcThreadStatus; // bool of if left child is a thread
  bool rcThreadStatus; // bool of if right child is a thread

public:
  // Two constructors -- with and without initial values
  BSTNode() { lc = rc = NULL; }
  BSTNode(Key K, E e, BSTNode *l = NULL, BSTNode *r = NULL)
  {
    k = K;
    it = e;
    lc = l;
    rc = r;
    lcThreadStatus = true;
    rcThreadStatus = true;
  }
  ~BSTNode() {} // Destructor

  // Functions to set and return the value and key
  E &element() { return it; }
  void setElement(const E &e) { it = e; }
  Key &key() { return k; }
  void setKey(const Key &K) { k = K; }

  // Functions to set and return the children
  inline BSTNode *left() const { return lc; }
  void setLeft(BinNode<E> *b, bool isThread)
  {
    lc = (BSTNode *)b;

    if (isThread == true)
      lcThreadStatus = true;
    else
      lcThreadStatus = false;
  }
  inline BSTNode *right() const { return rc; }
  void setRight(BinNode<E> *b, bool isThread)
  {
    rc = (BSTNode *)b;

    if (isThread == true)
      rcThreadStatus = true;
    else
      rcThreadStatus = false;
  }

  // Getters and Setters for the bools, lcThreadStatus and rcThreadStatus
  bool getLcThreadStatus() { return lcThreadStatus; }
  void setLcThreadStatus(bool b) { lcThreadStatus = b; }
  bool getRcThreadStatus() { return rcThreadStatus; }
  void setRcThreadStatus(bool b) { rcThreadStatus = b; }

  // Return true if it is a leaf, false otherwise
  bool isLeaf() { return (lcThreadStatus == true) && (rcThreadStatus == true); }
};

#endif