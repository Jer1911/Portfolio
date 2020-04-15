/*******************************************************************************
* Roster Number : 5                                                            *
*                                                                              *
* Author : Jeremy Ecker                                                        *
* Due Date : 4/30/2018                                                         *
* Programming Assignment Number 7                                              *
*                                                                              *
* Spring 2018 - CS 3358 - 262                                                  *
*                                                                              *
* Instructor : Husain Gholoom                                                  *
*                                                                              *
* This is a simple hashing program.                                            *
*******************************************************************************/

#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

/*******************************************************************************
*                        hash class declaration:                               *
*******************************************************************************/
class hash
{
	private:
		int hash_pos;
		int array[30];
		int linearProbes;
		int collisions;
	public:
		hash();
		void insert(int);
		int Hash(int);
		int reHash(int);
		void Display();
		int getRandom();
		void generate();
		void greeting();
		void showMenu();
		string getChoice();
		int getProbes();
		int getCollisions();
		void newSearch(int);
		void newDelete(int);
};

/*******************************************************************************
*                        hash class implementation:                            *
*******************************************************************************/

// Constructor:
hash::hash()
{
	for(int i=0; i<30; i++)
	{
		array[i] = '*';
	}
	linearProbes = 0;
	collisions = 0;
}

/* Inserts an integer into the hash.
   @param int - data item to be inserted */
void hash::insert(int data)
{
	int count = 0;
	bool collided = false;
	if(data < 125 || data > 425)
	{
		cout << endl << "*** Invalid Choice ***" << endl << endl;
		return;
	}
	hash_pos = Hash(data);
	linearProbes += 1;
	if(hash_pos > 30)
	{
		hash_pos = 0;
	}
	while(array[hash_pos] != '*')
	{
		hash_pos = reHash(hash_pos);
		collisions += 1;
		count++;
		if(count >= 30)
		{
			cout << "Memory Full!! No space is available for storage";
			break;
		}
	}
	if(array[hash_pos] == '*')
	{
		array[hash_pos] = data;
	}
}

/* Hashes a key.
   @param int - key to be hashed
   @return int - index */
int hash::Hash(int key)
{	
	return key % 30;
}

/* Re-hashes a key.
   @param int - key to be re-hashed
   @return int - index */
int hash::reHash(int key)
{
	return (key+1) % 30;
}

/* Searches for a data item.
   @param int - data item to be searched */
void hash::newSearch(int key)
{
	bool found = false;
	int index = 0;
	int count = 0;
	if(key == array[Hash(key)])
	{
		found = true;
		index = Hash(key);
	}
	else
	{
		while(count < 30)
		{
			if(key == array[reHash(key+count)])
			{
				found = true;
				index = reHash(key+count);
			}
			else
			{
				count++;				
			}
		}
	}
	if(found)
	{
		cout  << endl << "The number " << key << " was found in element "
			  << index << endl << endl;
	}
	else
	{
		cout << endl << "No record found!!" << endl << endl;
	}
}

/* Deletes a data item.
   @param int - data item to be deleted */
void hash::newDelete(int key)
{
	bool found = false;
	int index = 0;
	int count = 0;
	if(key == array[Hash(key)])
	{
		found = true;
		index = Hash(key);
	}
	else
	{
		while(count < 30)
		{
			if(key == array[reHash(key+count)])
			{
				found = true;
				index = reHash(key+count);
			}
			else
			{
				count++;				
			}
		}
	}
	if(found)
	{
		array[index] = '*';
		cout << endl << key << " Has been deleted" << endl << endl;
	}
	else
	{
		cout << endl << key << " not found in the array." << endl << endl;
	}
}

// Displays the array.
void hash::Display()
{
	cout << endl;
	cout << "Generated Array" << endl << "---------------" << endl << endl;
	for(int i=0; i<15; i++)
	{
		if(array[i] == 42)
		{
			cout << "*";
		}
		else
		{
			cout << array[i];
		}
		cout << "  ";
	}
	cout << endl;
	for(int i=15; i<30; i++)
	{
		if(array[i] == 42)
		{
			cout << "*";
		}
		else
		{
			cout << array[i];
		}
		cout << "  ";
	}
	cout << endl << endl;
}

/* Gets a random integer between 125-425.
   @return int - random integer */
int hash::getRandom()
{
	int k = rand() % 300 + 125;
	return k;
}

// Prints the greeting.
void hash::greeting()
{
	cout << endl << "Welcome to my Hashing Program" << endl << endl
		 << "-----------------------------" << endl << endl
		 << "1.  Creates an integer array of size 30. Assigning 8 to each\n"
		 << "    location in the array indicating that the array is empty."
		 << endl << "2.  Populates half of the array with random integer "
		 << "values" << endl << "    between 125 and 425 inclusive." << endl
		 << "3.  If a collision occurs, linear probing will find the next"
		 << endl << "    available position / location." << endl
		 << "4.  The generated array will be displayed in 2 lines." << endl
		 << "    Each line contains 15 numbers separated by 2 spaces." << endl;
}

// Prints the main menu.
void hash::showMenu()
{
	cout << "Select from the following menu options" << endl << endl
		 << "A.  Display the generated array." << endl
		 << "B.  Search for a number (between 125-425) in the array." << endl
		 << "C.  Insert a new number (between 125-425) in the array." << endl
		 << "D.  Delete a number (between 125-425) in the array." << endl
		 << "X.  End the program." << endl << endl;
}

// Generates the array.
void hash::generate()
{
	for(int k=0; k<15; k++)
	{
		insert(getRandom());
	}
}

/* Gets user input for main menu choice.
   @return string - user's choice */
string hash::getChoice()
{
	cout << "Select your option: ";
	string answer = "";
	getline(cin, answer);
	if(answer!="A" && answer!="a" && answer!="B" && answer!="b" && answer!="C"
	   && answer!="c" && answer!="D" && answer!="d" && answer!="X"
	   && answer!="x")
	{
		cout << endl << "*** Invalid Option ***" << endl << endl;
		showMenu();
		answer = getChoice();
	}
	else
	{
		return answer;
	}
}

/* Gets the number of linear probes.
   @return int - number of probes */
int hash::getProbes()
{
	return linearProbes;
}

/* Gets the number of collisions.
   @return int - collisions */
int hash::getCollisions()
{
	return collisions;
}

/*******************************************************************************
*                        main function:                                        *
*******************************************************************************/
int main()
{
	// initialize random with seed of time:
	srand(time(NULL));

	// create a hash object:
	hash h;

	// Hold a user choice for main menu:
	string choice = "";

	// Hold a search value:
	int searchNum = 0;

	// Say the greeting:
	h.greeting();

	// Generate the array:
	h.generate();

	// Display the array:
	h.Display();

	// Begin program loop:
	do
	{
		// Display the main menu:
		h.showMenu();

		// Get a choice from the user:
		choice = h.getChoice();

		// A - displays array:
		if(choice=="A" || choice=="a")
		{
			h.Display();
		}

		// B - searches for a value:
		else if(choice=="B" || choice=="b")
		{
			cout << "\nenter a number you want to search (between 125-425): ";
			if(cin >> searchNum)
			{
				h.newSearch(searchNum);
			}
			else
			{
				cout << endl << "*** Invalid Choice ***" << endl << endl;
			}
			cin.clear();
			cin.ignore(10000, '\n');
		}

		// C - inserts a new value:
		else if(choice=="C" || choice=="c")
		{
			cout << "\nenter a number you want to insert (between 125-425): ";
			if(cin >> searchNum)
			{
				h.insert(searchNum);
			}
			else
			{
				cout << endl << "*** Invalid Choice ***" << endl << endl;
			}
			cin.clear();
			cin.ignore(10000, '\n');
		}

		// D - deletes a value:
		else if(choice=="D" || choice=="d")
		{
			cout << "\nenter a number you want to delete (between 125-425): ";
			if(cin >> searchNum)
			{
				h.newDelete(searchNum);
			}
			else
			{
				cout << endl << "*** Invalid Choice ***" << endl << endl;
			}
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

	// X - exits the loop:
	while(choice!="X" && choice!="x");

	// Display the probes and collisions data:
	cout << "\nThe number of times each position / location is hashed when"
		 << endl << "adding an element in the array is " << h.getProbes()
		 << endl << endl
		 << "The number of linear probes when each number is hashed and "
		 << "collision " << endl << "occurred when adding an element in the "
		 << "array is " << h.getCollisions() << endl;

	// Say goodbye:
	cout << endl << "This Hashing Program was Implemented by" << endl
		 << "Jeremy Ecker - April 30, 2018" << endl << endl;

	return 0;
}











