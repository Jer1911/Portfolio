#include<iostream>
#include<string>
using namespace std;

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


//*****************************************************************************
int main()
{
	cout << "\n\nEnqueueing some shit:\n\n";

	Queue testQueue;

	char test[5] = {'a','b','c','d','e'};
	for(int k=0; k<5; k++)
	{
		testQueue.enqueue(test[k]);
	}

	cout << "Here is the shit we got:\n\n";

	while(!testQueue.empty())
	{
		char letter;
		testQueue.dequeue(letter);
		cout << letter << " ";
	}
	cout << endl;

	return 0;
}








