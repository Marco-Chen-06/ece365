#ifndef _HEAP_H
#define _HEAP_H

#include <string>
#include <vector>
#include "hash.h"

class heap {

  public:
  // heap - The constructor allocates space for the nodes of the heap
  // and the mapping (hash table) based on the specified capacity
  //
  heap(int capacity);

  //
  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
  //
  int insert(const std::string &id, int key, void *pv = nullptr);

  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int setKey(const std::string &id, int key);

  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not nullptr), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //
  int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

  //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

private:
  // an inner class within a heap
  // id - the id of this node
  // key - the key of this node
  // pData - a pointer to the actual data
  class node {
  public:
    std::string id;
    int key;
    void *pData;
  };

  int capacity; // max count of nodes in heap
  int currentSize; // current count of nodes in heap

  std::vector<node> data;     
  hashTable mapping; // hash table

  /*
   * from class, percolateup() and percolatedown() are used by different 
   * member functions so it is worth creating functions for these things
   */
  // move the node at posCur up until heap order is restored
  void percolateUp(int posCur);

  // move the node at posCur down until heap order is restored
  void percolateDown(int posCur);

  // return the index in data of the node pointed to by pn
  int getPos(node *pn);
};

#endif //_HEAP_H