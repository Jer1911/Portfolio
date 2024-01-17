/******************************************************************************
* ArrayMaxHeap.h                                                              *
* Editor: Jeremy Ecker                                                        *
* Assignment: 9                                                               *
* COSC-2436 (Programming Fundamentals III: Data Structures, 18736)            *
* Date: 5/2/17                                                                *
******************************************************************************/

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2016 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
 Listing 17-2.
 @file ArrayMaxHeap.h */ 
 
#ifndef ARRAY_MAX_HEAP_
#define ARRAY_MAX_HEAP_

#include "HeapInterface.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class ArrayMaxHeap : public HeapInterface<ItemType>
{
private:
    static const int ROOT_INDEX = 0;        // Helps with readability
    static const int DEFAULT_CAPACITY = 26; /* Increased capacity to
                                               accomodate full alphabet */
    ItemType *items;                        // Array of heap items
    int itemCount;                          // Current count of heap items
    int maxItems;                           // Maximum capacity of the heap
   
    // ---------------------------------------------------------------------
    // Most of the private utility methods use an array index as a parameter
    // and in calculations. This should be safe, even though the array is an
    // implementation detail, since the methods are private.
    // ---------------------------------------------------------------------
   
    // Returns the array index of the left child (if it exists).
    int getLeftChildIndex(const int nodeIndex) const;
   
    // Returns the array index of the right child (if it exists).
    int getRightChildIndex(int nodeIndex) const;
    
    // Returns the array index of the parent node.
    int getParentIndex(int nodeIndex) const;
   
    // Tests whether this node is a leaf.
    bool isLeaf(int nodeIndex) const;
   
    // Converts a semiheap to a heap.
    void heapRebuild(int subTreeRootIndex);
   
    // Creates a heap from an unordered array.
    void heapCreate();
     
public:
    ArrayMaxHeap();
    ArrayMaxHeap(const ItemType someArray[], const int arraySize);
    virtual ~ArrayMaxHeap();
   
    // HeapInterface Public Methods:
    bool isEmpty() const;
    int getNumberOfNodes() const;
    int getHeight() const;
    ItemType peekTop() const throw(PrecondViolatedExcep);
    bool add(const ItemType& newData);
    bool remove();
    void clear();
}; // end ArrayMaxHeap

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */ 
 
#include <cmath> // for log2
#include <algorithm>  // for swap
#include "PrecondViolatedExcep.h"

//******************************************************************
// 
// Private methods start here
//
//******************************************************************

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
    return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(int nodeIndex) const
{
    return (2 * nodeIndex) + 2;
} // end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(int nodeIndex) const
{
    return ((nodeIndex -1) / 2);
} // end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const
{
    bool leaf = false;
    int left = getLeftChildIndex(nodeIndex);
    if(left > (itemCount-1))
        leaf = true;
    return leaf;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int subTreeRootIndex)
{
    if(!isLeaf(subTreeRootIndex))
    {
        int leftChildIndex = 2 * subTreeRootIndex + 1;
        int rightChildIndex = leftChildIndex + 1;
        int largerChildIndex = rightChildIndex;
        if((largerChildIndex >= itemCount) || 
                        (items[leftChildIndex] > items[rightChildIndex]))
        {
            largerChildIndex = leftChildIndex;
        }
        if(items[subTreeRootIndex] < items[largerChildIndex])
        {
            std::swap(items[subTreeRootIndex], items[largerChildIndex]);
            heapRebuild(largerChildIndex);
        }
    }
} // end heapRebuild

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
    for(int index = itemCount/2-1; index >= 0; index--)
        heapRebuild(index);
} // end heapCreate

//******************************************************************
// 
// Public methods start here
//
//******************************************************************

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() 
                        : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
    items = new ItemType[DEFAULT_CAPACITY];
} // end default constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize)
{
    // Allocate the array
    items = new ItemType[2 * arraySize];

    // Copy given values into the array
    for (int i = 0; i < itemCount; i++)
        items[i] = someArray[i];
   
    // Reorganize the array into a heap
    heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{  
    delete [] items;
}  // end destructor

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
    bool empty = false;
    if(itemCount == 0)
        empty = true;
    return empty;
} // end isEmpty

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
    return ceil(log2(itemCount + 1));
}  // end getHeight

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
    return itemCount;
} // end getNumberOfNodes

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
    itemCount = 0;
} // end clear

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcep)
{
    if (isEmpty())
        throw PrecondViolatedExcep("Attempted peek into an empty heap.");
   
    return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
    items[itemCount] = newData;
    int newDataIndex = itemCount;
    bool inPlace = false;
    if(itemCount >= DEFAULT_CAPACITY-1)
        return inPlace;
    while((newDataIndex >=0) && (!inPlace))
    {
        int parentIndex = (newDataIndex - 1) / 2;
        if(items[newDataIndex] <= items[parentIndex])
            inPlace = true;
        else
        {
            std::swap(items[newDataIndex], items[parentIndex]);
            newDataIndex = parentIndex;
        }
    }
    itemCount++;
    return inPlace;
} // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
    bool success = false;
    if(!isEmpty())
    {
        items[0] = items[itemCount-1];
        itemCount--;
        heapRebuild(0);
        success = true;
    }
    return success;
} // end remove

#endif

