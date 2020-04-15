/******************************************************************************
* heapDriver.cpp                                                              *
* Editor: Jeremy Ecker                                                        *
* Assignment: 9                                                               *
* COSC-2436 (Programming Fundamentals III: Data Structures, 18736)            *
* Date: 5/2/17                                                                *
******************************************************************************/

#include <iostream>
#include <string>
#include "ArrayMaxHeap.h"
using namespace std;

int main()
{
    cout << endl << "Creating heap 1..." << endl << endl;
    ArrayMaxHeap<int> *heap1Ptr = new ArrayMaxHeap<int>(); 
    cout << "Adding 50, 10, 40, 30, 60, 20..." << endl << endl;
    heap1Ptr->add(50);
    heap1Ptr->add(10);
    heap1Ptr->add(40);
    heap1Ptr->add(30);
    heap1Ptr->add(60);
    heap1Ptr->add(20);

    cout << "Heap 1: " << endl;
    while (!heap1Ptr->isEmpty())
    {
        cout << "# of nodes: " << heap1Ptr->getNumberOfNodes() << endl;
        cout << "Height: "     << heap1Ptr->getHeight() << endl;
        cout << "max value: "  << heap1Ptr->peekTop() << endl;
        cout << "remove: "     << (heap1Ptr->remove()? "success": "failure\n") 
                               << endl << endl;
    }
    heap1Ptr->clear();

    int heap2size = 26;
    cout << "Creating heap 2 local array..." << endl << endl;
    string heap2[] = {"charlie", "zulu", "hotel", "alpha", "victor", "sierra",
                      "india", "uniform", "delta", "yankee", "bravo", 
                      "november", "golf", "echo", "tango", "whiskey", 
                      "juliett", "oscar", "mike", "x-ray", "foxtrot", "romeo",
                      "kilo", "quibec", "lima", "papa"};
    cout << "Heap 2 unsorted local array:" << endl;
    for(int n=0; n<heap2size-1; n++)
        cout << heap2[n] << ", ";
    cout << heap2[heap2size-1] << endl << endl;
    
    cout << "Creating and filling heap 2:" << endl << endl;
    ArrayMaxHeap<string> *heap2Ptr = new ArrayMaxHeap<string>(heap2, heap2size);

    cout << "Heap 2: " << endl;
    int heap2counter = 1;
    while(!heap2Ptr->isEmpty())
    {
        cout << "# of nodes: " << heap2Ptr->getNumberOfNodes() << endl;
        cout << "Height: "     << heap2Ptr->getHeight() << endl;

        // sort heap2 local array:
        heap2[heap2size-heap2counter] = heap2Ptr->peekTop();
        cout << "max value: "  << heap2[heap2size-heap2counter] << endl;
        cout << "remove: "     << (heap2Ptr->remove()? "success": "failure\n") 
                               << endl << endl;
        heap2counter++;
    }
    heap2Ptr->clear();

    // display sorted heap2 array:
    cout << "Sorted heap 2:" << endl;
    for(int j=0; j<heap2size-1; j++)
        cout << heap2[j] << ", ";
    cout << heap2[heap2size-1] << endl<< endl;

    return 0;
}  // end main

