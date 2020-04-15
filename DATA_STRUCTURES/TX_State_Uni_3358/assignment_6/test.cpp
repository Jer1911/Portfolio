/******************************************************************************
* Roster Number : 5                                                           *
*                                                                             *
* Author : Jeremy Ecker                                                       *
* Due Date : 4/25/2018                                                        *
* Programming Assignment Number 6                                             *
*                                                                             *
* Spring 2018 - CS 3358 - 262                                                 *
*                                                                             *
* Instructor : Husain Gholoom                                                 *
*                                                                             *
* This program implements simple array-based binary search tree class, with   *
* extra operations.                                                           *
******************************************************************************/

#include<iostream>
using namespace std;

/*******************************************************************************
*                           BST Class Declaration:                             *
*******************************************************************************/
class BST
{
	public:
		int size;
		int *array;

		void insert(int x);
		void search(int x);
		void parent(int x);
		int extend(int x);

		void inOrder(int index);
		void preOrder(int index);
		void postOrder(int index);
		void display(int index, int indentation);
		void build(BST bst, int sizeIn, int arrayIn[]);
		bool leaf(int index);
		int numberOfLeaves(int index);
		void displayLeaves(int index);
		void displaySubRoot(int index);
		void displaySubRoots(int index);

		/* Constructor - allocates some memory for a BST.
		   @param int - initial size */
		BST(int sizeIn)
		{
	        size = extend(sizeIn);
	        array = new int[size];
	        for(int x = 0; x<size; x++)
			{
	            array[x] = NULL;
			}
        }
};

/*******************************************************************************
*                        BST Class Method Implementations:                     *
*******************************************************************************/

/* Counts the number of BST leaves.
   @param int - index of node to begin
   @return int - number of leaves */
int BST::numberOfLeaves(int index)
{
	if(!array[index])
	{
		return 0;
	}
	if(leaf(index))
	{
		return 1;
	}
	else if(!leaf(index))
	{
		return (numberOfLeaves(2*index+1) + numberOfLeaves(2*index+2));
	}
}

/* Determines whether a particular node is a leaf.
   @param int - index of node to check
   @return bool - true if leaf */
bool BST::leaf(int index)
{
	if(array[2*index+1] || array[2*index+2])
	{
		return false;
	}
	else
	{
		return true;
	}
}

/* Shows leaves of BST.
   @param int - index of node to begin */
void BST::displayLeaves(int index)
{
	if(array[index])
	{
		if(leaf(index))
		{
			cout << array[index] << " ";
		}
		else
		{
			displayLeaves(2*index+1);
			displayLeaves(2*index+2);
		}
	}
}

/* Displays sub-roots of a BST node.
   @param int - index of node to begin */
void BST::displaySubRoot(int index)
{
	if(array[index])
	{
		if(!leaf(index))
		{
			cout << array[index] << " ";
		}
		displaySubRoot(2*index+1);
		displaySubRoot(2*index+2);
	}
}

/* Calls displaySubRoot for left sub-tree, then right sub-tree.
   @param int - index of node to begin */
void BST::displaySubRoots(int index)
{
	cout << "Here are all right sub root values for the BST : ";
	displaySubRoot(2*index+2);
	cout << endl << endl;

	cout << "Here are all left sub root values for the BST : ";
	displaySubRoot(2*index+1);
	cout << endl << endl;
}

/* Displays a BST in a human-readable intuitive form, left to right.
   @param int - index of node to begin
   @param int - level of indentation */
void BST::display(int index, int indentation)
{
	if(array[index])
	{
		display(2*index+2, indentation+4);
		if(indentation>0)
		{
			for(int k=0; k<indentation; k++)
			{
				cout << " ";
			}
		}
		cout << array[index] << endl;
		display(2*index+1, indentation+4);
		
	}
}

/* Displays a pre-order traversal of a BST.
   @param int - index of node to begin */
void BST::preOrder(int index)
{
    if(array[index])
	{
		parent(index);
		cout << array[index] << endl;
		preOrder(2*index+1);
		preOrder(2*index+2);
    }
}

/* Displays an in-order traversal of a BST. (Note: not used, was for testing.)
   @param int - index of node to begin */
void BST::inOrder(int index)
{
    if(array[index])
	{
        inOrder(2*index+1);
        parent(index);
        cout << array[index] << " " << endl;
        inOrder(2*index+2);
    }
}

/* Displays a post-order traversal of a BST.
   @param int - index of node to begin */
void BST::postOrder(int index)
{
    if(array[index])
	{
        postOrder(2*index+1);
        postOrder(2*index+2);
        parent(index);
        cout << array[index] << " " << endl;
    }
}

/* Extends a memory space to hold a BST.
   @param int - initial value */
int BST::extend(int x)
{
	int value = 0;
	for(int y=0; y<x+1; y++)
	{
		value = (2*value)+2;
	}
	return value;
}

/* Inserts a value into a BST.
   @param int - value */
void BST::insert(int x)
{
	int currentIndex = 0;
	//cout << "adding: " << x;
	while(true)
	{
		if(!array[currentIndex])
		{
			array[currentIndex] = x;
			//cout << " inserted at index: " << currentIndex << endl;
			break;
		}
		else if(array[currentIndex] <= x)
		{
			if(array[currentIndex] == x)
			{
				cout << "ERROR!-- Repeating element" << endl;
				break;
			}
			else
			{
				//cout << " Right ";
			}
			currentIndex = (2*currentIndex+2);
		}
		else if(array[currentIndex] >= x)
		{
			if(array[currentIndex] == x)
			{
				cout << "ERROR!-- Repeating element" << endl;
				break;
			}
			else
			{
				//cout << " Left ";
			}
			currentIndex = (2*currentIndex+1);
		}
	}
}

/* Searches for a value in a BST. (Note: not used, included for testing.)
   @param int - value */
void BST::search(int x)
{
	int currentIndex = 0;
	while(true)
	{
		if(!array[currentIndex])
		{
			cout << "Not Found" << endl;
			break;
		}
		if(array[currentIndex] == x)
		{
			cout << "Found at index; " << currentIndex << endl;
			break;
		}
		else if(array[currentIndex] < x)
		{
			currentIndex = (2*currentIndex+2);
		}
		else if(array[currentIndex] > x)
		{
			currentIndex = (2*currentIndex+1);
		}
	}
}

/* Displays some spaces. Useful for functions displaying trees.
   @param int - value */
void BST::parent(int x)
{
	while(x != 0)
	{
		x = (x-1)/2;
		cout << "    ";
	}
}

/* Builds a BST.
   @param BST - pass in the tree object you wish to build
   @param int - size of array
   @param int[] - array of values */
void BST::build(BST bst, int sizeIn, int arrayIn[])
{
	cout << "Inserting nodes." << endl;
	for(int k=0; k<sizeIn; k++)
	{
		insert(arrayIn[k]);
	}
	cout << "Building BST is completed." << endl << endl;
	cout << "Values of the Binary Search Tree :" << endl << endl;
	display(0,0);
}

/*******************************************************************************
*                           Main function:                                     *
*******************************************************************************/
int main()
{
	// introduce the program:
	cout << endl << "Binary Search Tree By Jeremy Ecker" << endl;

	// create useful variables and objects:
	int array[] = {70,50,100,30,60,80,110,20,68,90,120,25,62};
	int size = 13;
	BST tree(size);

	// build and display a BST:
	tree.build(tree, size, array);

	// display pre-order traversal:
	cout << endl << endl << "Pre-Order Traversal : " << endl << endl;
	tree.preOrder(0);

	// display post-order traversal:
	cout << endl << endl << "Post-Order Traversal : " << endl << endl;
	tree.postOrder(0);
	cout << endl << endl;

	// display left and right sub-roots:
	tree.displaySubRoots(0);

	// display number of leaves:
	cout << "Number of Leaves : " << tree.numberOfLeaves(0) << endl << endl;

	// display leaf values:
	cout << "Here are the leaf values in the BST : ";
	tree.displayLeaves(0);

	// say goodbye:
	cout << endl << endl << "April 25, 2018" << endl
		 << "Written by Jeremy Ecker" << endl << endl;

    return 0;
}








