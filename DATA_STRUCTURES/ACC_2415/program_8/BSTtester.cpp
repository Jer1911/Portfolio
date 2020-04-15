/**************************************************************************
* BSTtester.cpp                                                           *
* program for testing BST class template                                  *
*                                                                         *
* Editor: Jeremy Ecker                                                    *
* Assignment: 8                                                           *
* COSC-2436 (Programming Fundamentals III: Data Structures, 18736)        *
* Date: 4/28/17                                                           *
*                                                                         *
* edits made: added testing for functions getHeight, getNumberOfNodes,    *
*             and getNumberOfLeaves.                                      *
**************************************************************************/

#include <iostream>
using namespace std;

#include "BST.h"

int main()
{
   // Testing Constructor and empty()
   BST<int> intBST;            // test the class constructor
   cout << "Constructing empty BST\n";
   cout << "BST " << (intBST.isEmpty() ? "is" : "is not") << " empty\n";

   // Testing inorder
   cout << "Inorder Traversal of BST: \n";
   intBST.inorder(cout);

   // Testing insert
   cout << "\nNow insert a bunch of integers into the BST."
           "\nTry items not in the BST and some that are in it:\n";
   int number;
   for (;;)
   {
      cout << "Item to insert (-999 to stop): ";
      cin >> number;
      if (number == -999) break;
      intBST.add(number);
   }
   intBST.graph(cout);

   cout << "BST " << (intBST.isEmpty() ? "is" : "is not") << " empty\n";
   cout << "Inorder Traversal of BST: \n";
   intBST.inorder(cout);

   cout << endl;

    // Testing getHeight:
    int height;
    height = intBST.getHeight();
    cout << "Height is: " << height << endl << endl;

    // Testing getNumberOfNodes:
    int nodesnum;
    nodesnum = intBST.getNumberOfNodes();
    cout << "Number of nodes is: " << nodesnum << endl << endl;

    // Testing getNumberOfLeaves():
    int leavesnum;
    leavesnum = intBST.getNumberOfLeaves();
    cout << "Number of leaves is: " << leavesnum << endl << endl;

   // Testing search()
   cout << "\n\nNow testing the contains() operation."
           "\nTry both items in the BST and some not in it:\n";
   for (;;)
   {
      cout << "Item to find (-999 to stop): ";
      cin >> number;
      if (number == -999) break;
      cout << (intBST.contains(number) ? "Found" : "Not found") << endl;
   }

   // Testing remove()
   cout << "\nNow testing the remove() operation."
           "\nTry both items in the BST and some not in it:\n";
   for (;;)
   {
      cout << "Item to remove (-999 to stop): ";
      cin >> number;
      if (number == -999) break;
      intBST.remove(number);
      intBST.graph(cout);
   }
   cout << "\nInorder Traversal of BST: \n";
   intBST.inorder(cout);
   cout << endl;

    // Testing getHeight again:
    height = intBST.getHeight();
    cout << "Height is: " << height << endl << endl;

    // Testing getNumberOfNodes again:
    nodesnum = intBST.getNumberOfNodes();
    cout << "Number of nodes is: " << nodesnum << endl << endl;

    // Testing getNumberOfLeaves() again:
    leavesnum = intBST.getNumberOfLeaves();
    cout << "Number of leaves is: " << leavesnum << endl << endl;

    return 0;
}


