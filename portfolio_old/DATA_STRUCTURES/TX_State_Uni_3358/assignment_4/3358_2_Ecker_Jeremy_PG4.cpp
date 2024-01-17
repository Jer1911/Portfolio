/*******************************************************************************
* Author: Jeremy Ecker                                                         *
* Serial Number: 5                                                             *
* Due Date: 3/28/2018                                                          *
* Programming Assignment Number 4                                              *
* Spring 2018 - CS 3358 - Section Number 262                                   *
*																			   *
* Instructor: Husain Gholoom                                                   *
*                                                                              *
* This program demonstrates simple stack and queu with extra operations.       *
*******************************************************************************/

#include<iostream>
#include<string>

using namespace std;

/*******************************************************************************
*                       Stack Class Declaration:                               *
*******************************************************************************/

class Stack
{
	private:
		// Since the Node for Stack is small, we shall implement it here:
		class Node
		{
			friend class Stack; // Node is inside of Stack.
			char letter; // We don't need a template just for chars.
			Node *next;

			// Node constructor:
			Node(char letter1, Node *next1 = NULL)
			{
				letter = letter1;
				next = next1;
			}
		};
		Node *top;

	public:
		Stack();
		void push(char);
		void pop(char &);
		char peek(); // Makes it easy to compare chars.
		bool empty() const;
};

/*******************************************************************************
*                       Stack Class Implementation:                            *
*******************************************************************************/

// Default Constructor:
Stack::Stack()
{
	top = NULL;
}

/* Push a letter to the top of the stack.
   Param char
*/
void Stack::push(char letterIn)
{
	top = new Node(letterIn, top);
}

// Pop the letter from the top of the stack:
void Stack::pop(char &letter1)
{
	Node *temp;

	if(empty())
	{
		cout << "Empty stack. Nothing to pop." << endl;
		return;
	}
	else
	{
		letter1 = top->letter;
		temp = top;
		top = top->next;
		delete temp;
	}
}

// Checks to see if the stack is empty:
bool Stack::empty() const
{
	if(!top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* Peek at the value on the top of the stack
   Return char
*/
char Stack::peek()
{
	Node *temp = top;
	return temp->letter;
}

/*******************************************************************************
*                       Queue Class Declaration:                               *
*******************************************************************************/

class Queue
{
	private:
		// Again, node is small enough to implement inline:
		class Node
		{
			friend class Queue;
			char letter;
			Node *next;

			Node(char letter1, Node *next1 = NULL)
			{
				letter = letter1;
				next = next1;
			}
		};
		Node *front;
		Node *back; // the queue needs two pointers, unlike the stack.

	public:
		Queue();
		~Queue();

		void enqueue(char);
		void dequeue(char &);
		bool empty() const;
		void clear();
};

/*******************************************************************************
*                       Queue Class Implementation:                            *
*******************************************************************************/

// Default constructor:
Queue::Queue()
{
	front = NULL;
	back = NULL;
}

// Destructor:
Queue::~Queue()
{
	clear();
}

/* Enqueue a character.
   Param char
*/
void Queue::enqueue(char letterIn)
{
	if(empty())
	{
		front = new Node(letterIn);
		back = front;
	}
	else
	{
		back->next = new Node(letterIn);
		back = back->next;
	}
}

/* Dequeue a character.
   Param &char reference
*/
void Queue::dequeue(char &letterIn)
{
	Node *temp;
	if(empty())
	{
		cout << "\n\nEmpty queue, nothing to dequeue.\n\n";
		return;
	}
	else
	{
		letterIn = front->letter;
		temp = front;
		front = front->next;
		delete temp;
	}
}

// Check to see whether the queue is empty.
bool Queue::empty() const
{
	if(front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Empty out the whole queue (helper to destructor):
void Queue::clear()
{
	char dummy;
	while(!empty())
	{
		dequeue(dummy);
	}
}

/*******************************************************************************
*                          Local function declarations:                        *
*******************************************************************************/

/* Gets an input string from user.
   Return string
*/
string getInput();

/* Locates the position of the '#' separator. If the separator is not located,
   returns -1. 
   Param string
   Return size_t
*/
size_t findSeperator(string input);

/* Gets the first string.
   Param string
   Param size_t
   Return string
*/
string getFirst(string input, size_t found);

/* Gets the last string.
   Param string
   Param size_t
   Return string
*/
string getLast(string input, size_t found);

// say hello:
void sayHello();

// show menu:
void showMenu();

void sayGoodbye();

// stack option:
void stackOption();

// queue option:
void queueOption();

// Program loop:
void loop();

/*******************************************************************************
*                       Main function:                                         *
*******************************************************************************/

int main()
{
	loop();

	return 0;
}

/*******************************************************************************
*                      Local function implementations:                         *
*******************************************************************************/

/* Gets an input string from user.
   Return string
*/
string getInput()
{
	string input;
	getline(cin, input);

	return input;
}

/* Locates the position of the '#' separator. If the separator is not located,
   returns -1. If the separator is in a bad position, returns -2. If there is 
   more than 1 separator, returns -3.
   Param string
   Return size_t
*/
size_t findSeperator(string input)
{
	char ch = '#';
	size_t found;
	bool isFound = false;
	int num_chars = 0;

	for(int k=0; k<input.size(); k++)
	{
		if (input.at(k) == ch)
		{
			found = size_t(k);
			isFound = true;
			num_chars++;
		}
	}

	// make sure the string has a # at a valid position:
	if(found == string::npos || !isFound)
	{
		found = -1;
	}
	if(found == input.size()-1 || found == 0)
	{
		found = -2;
	}
	if(num_chars > 1)
	{
		found = -3;
	}

	return found;
}

/* Gets the first string.
   Param string
   Param size_t
   Return string
*/
string getFirst(string input, size_t found)
{
	string first (input.begin(), input.begin()+found);
	return first;
}

/* Gets the last string.
   Param string
   Param size_t
   Return string
*/
string getLast(string input, size_t found)
{
	string last(input.begin()+found+1, input.end());
	return last;
}

// Say hello:
void sayHello()
{
	cout << "\n*** Welcome to My stack / Queue Program ***\n\n"
	     << "The function of this program is to :" << endl << endl
		 << "\t1. Use stack to determine whether or not" << endl
		 << "\t   two strings are the same." << endl << endl
		 << "\t2. Use queue to determine whether or not" << endl
		 << "\t   STRING2 is the reversed of STRING1." << endl << endl;
}

// show menu:
void showMenu()
{
	cout << "\nSelect from the following menu" << endl
		 << "\t1.	Enter Stack Values." << endl
		 << "\t2.	Enter Queue Values." << endl
		 << "\t9.	Terminate the program.\t";
}

// say goodbye:
void sayGoodbye()
{
	cout << "\n\n\n*** End of the program. ***\n"
		 << "*** Written by Jeremy Ecker ***\n"
		 << "*** March 20 - 2018 ***\n\n";
}

// Program loop:
void loop()
{
	// say hello:
	sayHello();

	// start the loop:
	int answer = 0;
	do
	{
		showMenu(); // show the menu.
		if(cin >> answer) // check that the input was an integer.
		{
			// check that the integer was valid:
			if(!(answer==1 || answer==2 || answer == 9))
			{
				cout << "\n\nInvalid Option\n\n\n";
				answer = 0;
			}
			else
			{
				switch(answer) // Here is the real loop:
				{
					case 1: // user chooses Stack option:
					{
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "\n\nEnter Stack Values :\t";
						stackOption();
						break;
					}
					case 2: // user chooses Queue option:
					{
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "\n\nEnter Queue Values :\t";
						queueOption();
						break;
					}
				}
			}
		}
		else // the user did not enter an integer
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\n\nInvalid Option\n\n";
		}
	}
	while(answer != 9); // 9 indicates exit condition.

	// say goodbye:
	sayGoodbye();
}

// Stack Option:
void stackOption()
{
	bool keepPlaying = true;
	do
	{
		// get a string from the user:
		string input = getInput();

		// find the position of the separator character:
		size_t found = findSeperator(input);

		// check that the separator exists:
		if(found != -1 && found != -2 && found != -3)
		{
			string first = getFirst(input, found);
			string last = getLast(input, found);

			// make some stacks:
			Stack stack1;
			Stack stack2;

			// put the strings on the stacks:
			for(int k=0; k<first.size(); k++)
			{
				char j = first.at(k);
				stack1.push(j);
			}
			for(int k=0; k<last.size(); k++)
			{
				char j = last.at(k);
				stack2.push(j);
			}

			// compare the stacks:
			while(!(stack1.empty() && stack2.empty()))
			{
				if(stack1.peek() == stack2.peek())
				{
					char p1;
					char p2;
					stack1.pop(p1);
					stack2.pop(p2);
				}
				else
				{
					break;
				}
			}
			if(stack1.empty() && stack2.empty())
			{
				cout << "\nStrings are identical.\n\n";
			}
			else
			{
				cout << "\nStrings are not identical\n\n";
			}

			// exit the loop:
			keepPlaying = false;
		}
		else
		{
			switch(found)
			{
				case -1:
				{
					cout << "\n\nYou entered no # seperator.\n\n";
					break;
				}
				case -2:
				{
					cout << "\n\n# separator was in an invalid position.\n\n";
					break;
				}
				case -3:
				{
					cout << "\n\nYou entered too many # separators.\n\n";
					break;
				}
			}
			cout << "Enter Stack Values:\t";
		}
	}
	while(keepPlaying == true);
}

// Queue Option:
void queueOption()
{
	bool keepPlaying = true;
	do
	{
		// get a string from the user:
		string input = getInput();

		// find the position of the separator character:
		size_t found = findSeperator(input);

		// check that the separator exists:
		if(found != -1 && found != -2 && found != -3)
		{
			string first = getFirst(input, found);
			string last = getLast(input, found);

			// Create some queues:
			Queue queue1;
			Queue queue2;

			// Put the strings in the queues:
			for(int k=0; k<first.size(); k++)
			{
				char j = first.at(k);
				queue1.enqueue(j);
			}
			for(int k=last.size()-1; k>=0; k--)
			{
				char j = last.at(k);
				queue2.enqueue(j);
			}

			// Compare the queues:
			if(first.size() != last.size())
			{
				cout << "\n\nSTRING2 is not reversed of STRING1.\n\n";
				return;
			}
			while(!(queue1.empty() && queue2.empty()))
			{
				char temp1, temp2;
				queue1.dequeue(temp1);
				queue2.dequeue(temp2);
				if(temp1 != temp2)
				{
					cout << "\n\nSTRING2 is not reversed of STRING1.\n\n";
					return;
				}
			}
			cout << "\n\nSTRING2 is reversed of STRING1\n\n";

			// exit the loop:
			keepPlaying = false;
		}
		else
		{
			switch(found)
			{
				case -1:
				{
					cout << "\n\nYou entered no # seperator.\n\n";
					break;
				}
				case -2:
				{
					cout << "\n\n# separator was in an invalid position.\n\n";
					break;
				}
				case -3:
				{
					cout << "\n\nYou entered too many # separators.\n\n";
					break;
				}
			}
			cout << "Enter Queue Values:\t";
		}
	}
	while(keepPlaying == true);
}







