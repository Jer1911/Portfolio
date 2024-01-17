#include<iostream>
#include<string>
using namespace std;

class Queue
{
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
	Node *back;

	public:
		Queue();
		~Queue();

		void enqueue(char);
		void dequeue(char &);
		bool empty() const;
		void clear();
};

Queue::Queue()
{
	front = NULL;
	back = NULL;
}

Queue::~Queue()
{
	clear();
}

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

void Queue::clear()
{
	char dummy;
	while(!empty())
	{
		dequeue(dummy);
	}
}

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








