/*******************************************************************************
* Author: Jeremy Ecker                                                         *
* Serial Number: 5                                                             *
* Due Date: 3/5/2018                                                           *
* Programming Assignment Number 3                                              *
* Spring 2018 - CS 3358 - Section Number 262                                   *
*																			   *
* Instructor: Husain Gholoom                                                   *
*                                                                              *
* This program demonstrates a simple linked list with extra operations.        *
*******************************************************************************/

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>

using namespace std;

/*******************************************************************************
*                     LinkedList class declaration:                            *
* A basic linked-list class, with some extra operation methods added:          *
*******************************************************************************/
class LinkedList
{
	private:
		// A linked-list node structure for integers:
		struct Node
		{
			int value; // data value
			Node *next; // pointer to next node
		};

		Node *head; // Pointer to head

	public:
		LinkedList(); // default constructor
		LinkedList(const LinkedList&); // copy constructor
		LinkedList(LinkedList, LinkedList); // constructor join two lists
		~LinkedList(); // destructor
		void appendNode(int); // push a new node to the end of the list
		void moveNode(int, int); // insert a node at a specified position
		void deleteNode(int); // delete a node
		void displayList(); // display the list
		int getRandom(); // procure a random integer
		int occurences(); // find number of occurences of first list element
		void removeDupes(); // remove duplicate numbers from a list
		int elementCount(); // get a count of number of nodes in a list
		void displayBackward(); // display a list backwards
		int getSmallest(); // return the smallest element in a list
		void sort(); // sort a list using selection sort
};

/*******************************************************************************
*                     LinkedList class method definitions:                     *
*******************************************************************************/

// Default constructor:
LinkedList::LinkedList()
{
	head = NULL;
}

// Destructor:
LinkedList::~LinkedList()
{
	Node *nodePtr;
	Node *nextNode;
	nodePtr = head;
	while(nodePtr)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

// Pushes a node to the end of the list. Param int value to be added:
void LinkedList::appendNode(int num)
{
	Node *newNode;

	newNode = new Node;
	newNode->value = num;
	newNode->next = NULL;

	if(!head)
		head = newNode;
	else
	{
		Node *nodePtr;
		nodePtr = head;

		while(nodePtr->next)
			nodePtr = nodePtr->next;

		nodePtr->next = newNode;
	}
}

/* Moves a node from one position to another. Param int, int
   The first int parameter is for the position of the node to be moved. The
   second is for the position of the node which will proceed the first node's
   new position after the move. */
void LinkedList::moveNode(int position1, int position2)
{
	Node *node1 = head; // for walking the list to position1
	Node *node2 = head; // for walking the list to position2
	Node *node3 = head; // for remembering which is the new last node
	int size = elementCount(); // list size

	// if the positions are invalid, don't try to do anything:
	if((position2>size) || (position1>size) || (position1<0) || (position2<0))
		return;

	// find the node that needs to be moved:
	for(int k=0; k<position1; k++)
	{
		if(node1->next != NULL)
			node1 = node1->next;
	}

	// find the node in position where the first node will be moving:
	for(int k=0; k<position2-1; k++) // offset must be -1
	{
		if(node2->next != NULL)
			node2 = node2->next;
	}

	/* make sure to remember the position of the dangling node - it needs to be
	   given something to point to: */
	int position3 = position1 - 2; // offset must be -2
	for(int k=0; k<position3; k++)
	{
		if(node3->next != NULL)
			node3 = node3->next;
	}

	// point the node to be moved, to the next of the node to move after:
	node1->next = node2->next;

	// point the node to move after, to the inserted node:
	node2->next = node1;

	/* make the new last node point to null. If we were needing to move others
	   besides the last node, we would expand this code some more, but for this
	   assignment, we don't need to: */
	node3->next = NULL;	
}

// Deletes a node from the list. Param int represents value of node to delete:
void LinkedList::deleteNode(int num)
{
	if(!head)
		return;

	Node *nodePtr;
	if(head->value == num)
	{
		nodePtr = head;
		head = nodePtr->next;
		delete nodePtr;
	}
	else
	{
		Node *previousNode;
		nodePtr = head;

		while(nodePtr && nodePtr->value != num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if(nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

// Displays the list:
void LinkedList::displayList()
{
	Node *nodePtr;
	for(nodePtr=head; nodePtr; nodePtr=nodePtr->next)
		cout << nodePtr->value << " ";
	cout << endl;
}

// Returns a random integer between 1 and 19:
int LinkedList::getRandom()
{
    int k = rand()%19+1;
    return k;
}

/* Constructor which combines two existing lists into a new list.
   Takes parameters of two existing lists. */
LinkedList::LinkedList(LinkedList oldList1, LinkedList oldList2)
{
	head = NULL;
	Node *nodePtr1;
	Node *nodePtr2;

	for(nodePtr1=oldList1.head; nodePtr1; nodePtr1=nodePtr1->next)
	{
		appendNode(nodePtr1->value);
	}

	for(nodePtr2=oldList2.head; nodePtr2; nodePtr2=nodePtr2->next)
	{
		appendNode(nodePtr2->value);
	}
}

// Copy constructor:
LinkedList::LinkedList(const LinkedList& oldList)
{
	head = NULL;
	Node *nodePtr;

	for(nodePtr=oldList.head; nodePtr; nodePtr=nodePtr->next)
	{
		appendNode(nodePtr->value);
	}
}

// Returns the number of occurences of the first element in a list:
int LinkedList::occurences()
{
	Node *nodePtr;
	Node *countPtr;
	nodePtr = head;
	int firstElem = nodePtr->value; // the first element value
	int count = 0; // how many nodes are there

	for(countPtr=head; countPtr; countPtr=countPtr->next)
	{
		if(countPtr->value == firstElem)
		{
			count++;
		}
	}	

	return count; 
}

// Removes all duplicate numbers from a list:
void LinkedList::removeDupes()
{
	Node *nodePtr;
	Node *tempPtr;
	Node *previousPtr;

	for(nodePtr=head; nodePtr; nodePtr=nodePtr->next)
	{
		previousPtr = nodePtr;
		for(tempPtr=nodePtr->next; tempPtr; tempPtr=tempPtr->next)
		{
			int currentVal = nodePtr->value; // value of a node
			int nextVal = tempPtr->value; // value of the next node

			if(currentVal == nextVal) // compare the values
			{
				deleteNode(currentVal); // remove the duplicate
			}
		}
	}
}

// Returns the total number of nodes in a list:
int LinkedList::elementCount()
{
	int count = 0; // how many total nodes
	Node *nodePtr;
	for(nodePtr=head; nodePtr; nodePtr=nodePtr->next)
	{
		count++;
	}
	return count;
}

// Displays a list backwards:
void LinkedList::displayBackward()
{
	Node *nodePtr;
	nodePtr = head;
	int count = elementCount(); // total nodes

	while(count > 0) // for every element
	{
		for(int k=0; k<count; k++)
		{
			nodePtr = nodePtr->next; // go to the end of the list
		}
		if(nodePtr != NULL)
			cout << nodePtr->value << " "; // print the last value
		nodePtr = head;
		count--; // now do it again for the next-to-last value, etc.
	}
	cout << nodePtr->value << endl; // finally, print the first element.
}

/* Returns the value of the smallest node in the list. This is used to help
   with the selection sort. */
int LinkedList::getSmallest()
{
	Node *nodePtr = head;
	int smallest = nodePtr->value; // the smallest value
	while(nodePtr != NULL)
	{
		if(nodePtr->value < smallest)
			smallest = nodePtr->value;
		nodePtr = nodePtr->next;
	}
	return smallest;
}

// Sorts the list in ascending order by selection:
void LinkedList::sort()
{
	LinkedList tempList; // a temporary list, to put sorted values
	int size = elementCount(); // list size

	// get smallest values one by one, putting them in the temp list:
	for(int k=0; k<size; k++) 
	{
		int smallest = getSmallest();
		tempList.appendNode(smallest);
		deleteNode(smallest); // get rid of the node on original list
	}

	Node *nodePtr = tempList.head;
	size = tempList.elementCount();

	// put the sorted values back in the original list:
	for(int k=0; k<size; k++)
	{
		int elem = nodePtr->value; // value of the element
		appendNode(elem);
		nodePtr = nodePtr->next;
	}
}

/*******************************************************************************
*                          Local function declarations:                        *
*******************************************************************************/

// Procures input from the user to decide to play again. Returns boolean.
bool getInput();

// Print a barrier line to make the program sections more readable:
void printBarrier();

// Program loop:
void loop();

/*******************************************************************************
*                            Main function:                                    *
*******************************************************************************/
int main()
{
	// call the program loop function:
	loop();
	return 0;
}

/*******************************************************************************
*                          Local function definitions:                         *
*******************************************************************************/

// Procures input from the user to decide to play again. Returns boolean.
bool getInput()
{
	string answer = ""; // what the user will input
	do
	{
		cout << "Press 'q' or 'Q' to Quit;" << endl 
			 << "Press 'c' or 'C' to Continue and try the program again: ";

		getline(cin, answer);

		// if the user enters something wrong, tell them:
		if(answer != "q" && answer != "Q" && answer != "c" && answer != "C")
		{
			cout << endl << "Error - invalid choice - " << endl
				 << "the only acceptable answers are:"
				 << endl << "q | Q or c | C" << endl << endl;
		}
	}
	// repeat this until the user enters something correctly:
	while(answer != "q" && answer != "Q" && answer != "c" && answer != "C");

	// send the valid input back to the caller:
	if(answer == "q" || answer == "Q")
		return false;
	else if(answer == "c" || answer == "C")
		return true;
}

// Print a barrier line to make the program sections more readable:
void printBarrier()
{
	char barrier = '-'; // character to use as our barrier
	for(int k=0; k<80; k++) // width of barrier needs to be 80 characters
	{
		cout << barrier;
	}
	cout << endl;
}

// Program loop (this is where everything happens):
void loop()
{
	srand(time(NULL)); // initialize random with seed of time
	bool playAgain = true; // a check to see if user wants to play again

	// begin program loop:
	do
	{
		/***********************************************************************
		*                              Part A:                                 *
		***********************************************************************/
		printBarrier();

		// Explain what is done in Part A:
		cout << "Part A: Build 2 lists consisting of 15 random" 
			 << " integers between 0 and 20" << endl
			 << "exclusive and display them." << endl;

		// Construct our two lists:
		LinkedList list1; // list #1
		LinkedList list2; // list #2

		// add 15 random integers to lists 1 and 2:
		for(int k=0; k<15; k++)
		{
			list1.appendNode(list1.getRandom());
			list2.appendNode(list2.getRandom());
		}

		// display lists 1 and 2:
		cout << endl << "List 1: " << endl;
		list1.displayList();
		cout << endl << "List 2: " << endl;
		list2.displayList();
		printBarrier();

		/***********************************************************************
		*                              Part B:                                 *
		***********************************************************************/
		// Explain what is done in part B:
		cout << "Part B: Create a new list that contains all elements"
			 << endl << "of list 1 followed by all elements of list 2" 
			 << " and display it." << endl;

		// construct list #3 combining lists 1 and 2
		LinkedList list3(list1, list2);

		// display list 3:
		cout << endl << "List 3 (a combination of lists 1 and 2): " << endl;
		list3.displayList();
		printBarrier();

		/***********************************************************************
		*                              Part C:                                 *
		***********************************************************************/
		// Explain what is done in part C:
		cout << "Part C: Display the number of occurences of" << endl
			 << "the first element in list 3." << endl;

		// display number of occurences of the first element in list 3:
		int list3FirstElemCount = list3.occurences();
		cout << endl << "Number of occurences of first element in list 3: ";
		cout << list3FirstElemCount << endl;
		printBarrier();

		/***********************************************************************
		*                              Part D:                                 *
		***********************************************************************/
		// Explain what is done in part D:
		cout << "Part D: Create a new list #4 by removing all" << endl
			 << "duplicate numbers that are in list 3 and display." << endl;

		// create list #4 from list 3; remove duplicate numbers:
		LinkedList list4(list3);
		list4.removeDupes();
		cout << endl << "List 4: " << endl;
		list4.displayList();
		printBarrier();

		/***********************************************************************
		*                              Part E:                                 *
		***********************************************************************/
		// Explain what is done in part E:
		cout << "Part E: Display number of elements in list 4." << endl;

		// display number of nodes in list 4:
		int count = list4.elementCount();
		cout << endl << "Number of elements in list 4: ";
		cout << count << endl;
		printBarrier();

		/***********************************************************************
		*                              Part F:                                 *
		***********************************************************************/
		// Explain what is done in part F:
		cout << "Part F: Display list 4 backwards." << endl;

		// display list 4 backwards:
		cout << endl << "List 4 backwards: " << endl;
		list4.displayBackward();
		printBarrier();

		/***********************************************************************
		*                              Part G:                                 *
		***********************************************************************/
		// Explain what is done in part G:
		cout << "Part G: Move the last element in list 4 and place it" << endl
			 << "after the third element in the same list and display." << endl;

		// move last element of list 4, place after 3rd element, display:
		int list4size = list4.elementCount();
		list4.moveNode(list4size, 3);
		cout << endl;
		cout << "List 4, last node moved to after the third node:" << endl;
		list4.displayList();
		printBarrier();

		/***********************************************************************
		*                              Part H:                                 *
		***********************************************************************/
		// Explain what is done in part H:
		cout << "Part H: Sort list 4 in increasing order and display." << endl;

		// sort list 4 and display:	
		list4.sort();
		cout << endl << "List 4 sorted:" << endl;
		list4.displayList();
		printBarrier();

		/***********************************************************************
		*                      Query user for repeating:                       *
		***********************************************************************/
		// ask user if they want to play again:
		playAgain = getInput();
	}
	while(playAgain == true);

	// say goodbye:
	cout << endl << "Implemented by Jeremy Ecker, February 2018" << endl 
		 << endl;
}










