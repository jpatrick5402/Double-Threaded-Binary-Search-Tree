// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"
#include <string>

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E>
{
private:
  BSTNode<Key, E> *root; // Root of the BST
  int nodecount;         // Number of nodes in the BST

  // Private "helper" functions
  void clearhelp(BSTNode<Key, E> *);
  BSTNode<Key, E> *inserthelp(BSTNode<Key, E> *, const Key &, const E &);
  BSTNode<Key, E> *deletemin(BSTNode<Key, E> *);
  BSTNode<Key, E> *getmin(BSTNode<Key, E> *);
  BSTNode<Key, E> *removehelp(BSTNode<Key, E> *, const Key &);
  E *findhelp(BSTNode<Key, E> *, const Key &) const;
  void printhelp(BSTNode<Key, E> *, int) const;
  void printhelpinorder(BSTNode<Key, E> *) const;
  void printhelpreverse(BSTNode<Key, E> *) const;
  void visit(BSTNode<Key, E> *) const;

public:
  BST()
  {
    root = NULL;
    nodecount = 0;
  } // Constructor

  // Note from Prof Sipantzi -- I've commented out the destructor
  // since you would have to change clearhelp() to make it work with
  // doubly-threaded trees and that is not part of the assignment.
  //~BST() { clearhelp(root); }            // Destructor

  void clear() // Reinitialize tree
  {
    clearhelp(root);
    root = NULL;
    nodecount = 0;
  }

  // Insert a record into the tree.
  // k Key value of the record.
  // e The record to insert.
  void insert(const Key &k, const E &e)
  {
    root = inserthelp(root, k, e);
    nodecount++;
  }

  // Remove a record from the tree.
  // k Key value of record to remove.
  // Return: The record removed, or NULL if there is none.
  E *remove(const Key &k)
  {
    E *temp = findhelp(root, k); // First find it
    if (temp != NULL)
    {
      root = removehelp(root, k);
      nodecount--;
    }
    return temp;
  }
  // Remove and return the root node from the dictionary.
  // Return: The record removed, null if tree is empty.
  E *removeAny()
  { // Delete min value
    if (root != NULL)
    {
      E *temp = new E;
      *temp = root->element();
      root = removehelp(root, root->key());
      nodecount--;
      return temp;
    }
    else
      return NULL;
  }

  // Return Record with key value k, NULL if none exist.
  // k: The key value to find. */
  // Return some record matching "k".
  // Return true if such exists, false otherwise. If
  // multiple records match "k", return an arbitrary one.
  E *find(const Key &k) const { return findhelp(root, k); }

  // Return the number of records in the dictionary.
  int size() { return nodecount; }

  void print() const
  { // Print the contents of the BST
    if (root == NULL)
      cout << "The BST is empty.\n";
    else
      printhelp(root, 0);
  }

  void printinorder() const
  { // Print the contents of the BST
    if (root == NULL)
      cout << "The BST is empty.\n";
    else
      printhelpinorder(root);
  }

  void printreverse() const
  { // Print the contents of the BST
    if (root == NULL)
      cout << "The BST is empty.\n";
    else
      printhelpreverse(root);
  }
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::visit(BSTNode<Key, E> *r) const
{
  cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E> *root)
{
  if (root == NULL)
    return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::inserthelp(BSTNode<Key, E> *root, const Key &k, const E &it)
{
  if (root == NULL)
  {
    return new BSTNode<Key, E>(k, it, NULL, NULL); // Create start tree node if tree is NULL
  }
  if (k < root->key())
  {
    // if left is thread, reassign it to a new node
    if (root->getLcThreadStatus())
    {
      // Create Node
      BSTNode<Key, E> *newNode;
      newNode = new BSTNode<Key, E>(k, it, NULL, NULL);
      newNode->setRight(root, true);        // set the right node to the root
      newNode->setLeft(root->left(), true); // set the left node to the left node of the root BEFORE we change root's left to newNode
      root->setLeft(newNode, false);        // New Node
    }
    // if left is a branch, then go one more down the branch
    else
    {
      root->setLeft(inserthelp(root->left(), k, it), false);
    }
  }
  else
  {
    // if right is thread, reassign it to a new node
    if (root->getRcThreadStatus())
    {
      BSTNode<Key, E> *newNode;
      newNode = new BSTNode<Key, E>(k, it, NULL, NULL);
      newNode->setLeft(root, true);
      newNode->setRight(root->right(), true);
      root->setRight(newNode, false); // New Node
    }
    // if right is not a thread and is a branch, then go one more down the branch
    else
    {
      root->setRight(inserthelp(root->right(), k, it), false);
    }
  }
  return root; // Return tree with node inserted
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::getmin(BSTNode<Key, E> *rt)
{
  if (rt->left() == NULL)
    return rt;
  else
    return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::deletemin(BSTNode<Key, E> *rt)
{
  if (rt->left() == NULL) // Found min
    return rt->right();
  else
  { // Continue left
    rt->setLeft(deletemin(rt->left()), false);
    return rt;
  }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E> *BST<Key, E>::removehelp(BSTNode<Key, E> *rt, const Key &k)
{
  if (rt == NULL)
    return NULL; // k is not in tree
  else if (k < rt->key())
    rt->setLeft(removehelp(rt->left(), k), false);
  else if (k > rt->key())
    rt->setRight(removehelp(rt->right(), k), false);
  else
  { // Found: remove it
    BSTNode<Key, E> *temp = rt;
    if (rt->left() == NULL)
    {                   // Only a right child
      rt = rt->right(); //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL)
    {                  // Only a left child
      rt = rt->left(); //  so point to left
      delete temp;
    }
    else
    { // Both children are non-empty
      BSTNode<Key, E> *temp = getmin(rt->right());
      rt->setElement(temp->element());
      rt->setKey(temp->key());
      rt->setRight(deletemin(rt->right()), false);
      delete temp;
    }
  }
  return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E *BST<Key, E>::findhelp(BSTNode<Key, E> *root, const Key &k) const
{
  if (root == NULL)
    return NULL; // Empty tree
  if (k < root->key())
    return findhelp(root->left(), k); // Check left
  else if (k > root->key())
    return findhelp(root->right(), k); // Check right
  else
  {
    E *temp = new E;
    *temp = root->element();
    return temp; // Found it
  }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E> *root, int level) const
{
  if (root == NULL)
  {
    return; // Empty tree
  }
  if (!root->getLcThreadStatus() == true) // ensure that the node we are on is not a threaded node
  {
    printhelp(root->left(), level + 1); // Do left subtree
  }
  for (int i = 0; i < level; i++) // Indent to level
  {
    cout << "  ";
  }
  cout << root->key() << "\n"; // Print node value
  if (!root->getRcThreadStatus() == true)
  {
    printhelp(root->right(), level + 1); // Do right subtree
  }
}

template <typename Key, typename E>
void BST<Key, E>::printhelpinorder(BSTNode<Key, E> *root) const
{
  BSTNode<Key, E> *current = root;                                 // create a copy of root to use
  while (current->left() != NULL && !current->getLcThreadStatus()) // Move all of the way to the left without using a thread
  {
    current = current->left();
  }
  while (current->right() != NULL) // Unless the pointer to the right of our node points to NULL, print and move right
  {
    visit(current);
    if (current->getRcThreadStatus())
      current = current->right();
    else
    {
      current = current->right();
      while (!current->getLcThreadStatus()) // loop through the left thread again
      {
        current = current->left();
      }
    }
  }
  visit(current);
}

template <typename Key, typename E>
void BST<Key, E>::printhelpreverse(BSTNode<Key, E> *root) const
{
  BSTNode<Key, E> *current = root;                                  // create a copy of root to use
  while (current->right() != NULL && !current->getRcThreadStatus()) // Move all of the way to the left without using a thread
  {
    current = current->right();
  }
  while (current->left() != NULL) // Unless the pointer to the right of our node points to NULL, print and move right
  {
    visit(current);
    if (current->getLcThreadStatus())
      current = current->left();
    else
    {
      current = current->left();
      while (!current->getRcThreadStatus()) // loop through the left thread again
      {
        current = current->right();
      }
    }
  }
  visit(current);
}

#endif