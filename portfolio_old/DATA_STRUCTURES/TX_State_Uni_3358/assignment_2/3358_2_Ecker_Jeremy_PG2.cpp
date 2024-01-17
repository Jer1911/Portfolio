/******************************************************************************
* Author: Jeremy Ecker - Serial #: 5                                          *
* Due Date: 2/19/18                                                           *
* Programming Assignment Number 2                                             *
* Spring 2018 - CS 3358 - Section # 262                                       *
*                                                                             *
* Instructor: Husain Gholoom                                                  *
*                                                                             *
* This program keeps track of grades for programming assignments and tests.   *
******************************************************************************/

#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

/*******************************************************************************
*                             Class declaration:                               *
*******************************************************************************/
/*
MyGrades class: keeps track of grades for programming assignments and tests.
Includes methods for setting grades, displaying grades, removing grades,
displaying menu, and a program loop.
*/
class MyGrades
{
	private:
		int test1; // records grade for test #1
		bool t1validation; // flag to determine if test #1 exists
		int test2; // records grade for test #2
		bool t2validation; // flag to determine if test #2 exists
		vector<int> assignments; // records assignment grades

	public:
		//Default constructor - Initializes the private member variables:
		MyGrades();
		// Sets an assignment grade into the vector:
		void setAssign();
		// Sets a grade for test #1:
		void setTest1();
		// Sets a grade for test #2:
		void setTest2();
		// Prompts user to select which test he prefers to set. Returns int:
		int setTest();
		// Displays all assignments:
		void showAssign();
		// Displays all tests:
		void showTests();
		// Calls showAssign and showTest, to display all grades. Param MyGrades:
		void showAll(MyGrades mg);
		// Removes an assignment from the vector:
		void deleteAssign();
		// Removes a test:
		void deleteTest();
		// Program loop. param MyGrades:
		void loop(MyGrades mg);
		// Displays the main menu:
		void showMenu();
};

/*******************************************************************************
*                          Class method definitions:                           *
*******************************************************************************/


//Default constructor - Initializes the private member variables:
MyGrades::MyGrades()
{
	int test1;
	int test2;
	vector<int> assignments;
	bool t1validation = false;
	bool t2validation = false;
}

// Sets an assignment grade into the vector:
void MyGrades::setAssign()
{
	cout << "\nEnter a grade (integer value from 1 to 10):" << endl;
	int assignment = 0;
	if(cin >> assignment)
	{
		if(assignment<0 || assignment>10)
		{
			cout << "ERROR - invalid choice. Grades must be from 1 to 10\n";
			return;
		}
		else
		{
			assignments.push_back(assignment);
		}
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nERROR - Input must be an integer.\n" << endl;
	}
}

// Sets a grade for test #1:
void MyGrades::setTest1()
{
	cout << "\nEnter a grade (integer value from 1 to 20):" << endl;
	int t1 = 0;
	if(cin >> t1)
	{
		if(t1<0 || t1>20)
		{
			cout << "\nERROR - invalid choice. Grade must be from 1 to 20\n";
			return;
		}
		else
		{
			test1 = t1;
			t1validation = true;
		}
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nERROR - Input must be an integer." << endl;
	}
}

// Sets a grade for test #2:
void MyGrades::setTest2()
{
	cout << "\nEnter a grade (integer value from 1 to 25):" << endl;
	int t2 = 0;
	if(cin >> t2)
	{
		if(t2<0 || t2>25)
		{
			cout << "\nERROR - invalid choice. Grade must be from 1 to 25\n";
			return;
		}
		else
		{
			test2 = t2;
			t2validation = true;
		}
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nERROR - Input must be an integer." << endl;
	}
}

// Displays all assignments:
void MyGrades::showAssign()
{
	if(!assignments.empty())
	{
		cout << "\nProgramming Assignment Grades are As Follows" << endl;
		int i = 0; // temporary iterator to keep track of spots in the vector
		double average = 0.0; // running total of actual points
		int total = 0; // running total of possible points
		while(i < assignments.size())
		{
			printf("(%d): %.2f\t", i+1, double(assignments[i]));
			average += assignments[i];
			total += 10; // each assignment has 10 possible points
			i++;
		}
		cout << "\n\nAverage of the Programming Assignment Grades is\t";
		printf("%.2f out of %d\n\n", average, total);
	}
	else
	{
		cout << "\nThere are no Programming Assignment Grades to report.\n\n";
	}
}

// Displays all tests:
void MyGrades::showTests()
{
	if(t1validation==false && t2validation==false)
	{
		cout << "\nNo test grades on record to report." << endl << endl;
		return;
	}
	cout << "\nTest grades are as follows" << endl;
	int total = 0; // running total of possible points
	if(t1validation == true)
	{
		printf("Test #1: %.2f\t", double(test1));
		total += 20; // test #1 has 20 possible points
	}
	if(t2validation == true)
	{
		printf("Test #2: %.2f\t", double(test2));
		total += 25; // test #2 has 25 possible points
	}
	if(t1validation && t2validation)
	{
		printf("\n\nAverage of test grades is %.2f", double(test1+test2));
		printf(" out of %d\n\n", total);
	}
	else if(t1validation && !t2validation)
	{
		printf("\n\nAverage of test grade is %.2f", double(test1));
		printf(" out of %d\n\n", total);
	}
	else if(!t1validation && t2validation)
	{
		printf("\n\nAverage of test grade is %.2f", double(test2));
		printf(" out of %d\n\n", total);
	}
}

// Displays the main menu:
void MyGrades::showMenu()
{
	cout << "\n1. Set a Programming Assignment Grade" << endl
		 << "2. Set A Test Grade" << endl
		 << "3. Show All Programming Assignment Grades" << endl
		 << "4. Show All Test Grades" << endl
		 << "5. Show Overall Grades" << endl
		 << "6. Delete A Programming Assignment Grade" << endl
		 << "7. Delete A Test Grade" << endl
		 << "9. Exit the program" << endl << endl
		 << "Enter your choice	--->	";
}

// Prompts user to select which test he prefers to set. Returns int:
int MyGrades::setTest()
{
	cout << endl << "\nPress 1 to enter Test #1 score, " 
		 << "or press 2 to enter Test #2 score:" << endl;
	int input = 0; // will hold a 1 or a 2 for test #1 or #2
	if(cin >> input)
	{
		if(!(input == 1 || input == 2))
		{
			cout << "\nERROR - You did not enter 1 or 2." << endl << endl;
		}
	}
	else
	{
		cout << "\nERROR - You must enter an integer." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return input; // used by caller to decide which setTest method to use
}

// Calls showAssign and showTest, to display all grades. Param MyGrades:
void MyGrades::showAll(MyGrades mg)
{
	cout << "\nMy Overall Grades so far are as follows:\n\n";
	mg.showAssign();
	mg.showTests();
}

// Removes a test:
void MyGrades::deleteTest()
{
	// if no tests exist:
	if(t1validation==false && t2validation==false)
	{
		cout << "\nThere are no tests on record, cannot delete anything." << endl;
		return;
	}

	cout << "\nWhich test do you want to remove?" << endl;

	// if both tests exist:
	if(t1validation==true && t2validation==true)
	{
		cout << "Press '1' or '2' for Test #1 or #2" << endl;
	}
	// if only test 1 exists:
	if(t1validation==true && t2validation==false)
	{
		cout << "Press '1' for Test #1" << endl;
	}
	// if only test 2 exists:
	if(t1validation==false && t2validation==true)
	{
		cout << "Press '2' for Test #2" << endl;
	}

	int testNum = 0; // holds value of which test# the user wants to remove

	// check user input, then delete the appropriate test:
	if(cin >> testNum)
	{
		// deletes test #1:
		if(testNum==1 && t1validation==true)
		{
			test1 = 0;
			t1validation = false;
		}

		// deletes test #2:
		if(testNum==2 && t2validation==true)
		{
			test2 = 0;
			t2validation = false;
		}

		// input error handlers:
		if(testNum==1 && t1validation==false)
		{
			cout << "\nERROR - Test #1 does not exist." << endl;
		}
		if(testNum==2 && t2validation==false)
		{
			cout << "\nERROR - Test #2 does not exist." << endl;
		}
		if(!(testNum==1 || testNum==2))
		{
			cout << "\nERROR - You can only enter 1 or 2." << endl;
		}
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nERROR - You did not enter an integer." << endl;
	}
}

// Removes an assignment from the vector:
void MyGrades::deleteAssign()
{
	// Check to see if any assignments exist:
	if(assignments.size()==0)
	{
		cout << "\nThere are no assignments on record, cannot delete anything\n";
		return;
	}

	int size = assignments.size(); // holds number of assignments in vector

	// Prompt to select an assignment from the options:
	cout << "\nWhich assignment grade do you wish to delete?" << endl;
	printf("Your options are 1 through %d\n", size);

	int assignment = -1; // which assignment number the user wants to remove

	// Check user input and delete the appropriate grade:
	if(cin >> assignment)
	{
		if(!(assignment > assignments.size() || assignment < 0))
		{
			assignments.erase(assignments.begin()+(assignment-1));
		}
		else
		{
			cout << "\nERROR - You entered an invalid integer." << endl;
		}
	}
	else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nERROR - You did not enter an integer." << endl;
	}
}

// Program loop. Param MyGrades:
void MyGrades::loop(MyGrades mg)
{
	// welcome message:
	cout << endl << "Welcome to My Grades APP" << endl << endl;

	int answer = 0; // value of user's menu selection
	int testNum = 0; // value of test# for case 2

	// begins program main loop:
	do
	{
		// display the main menu:
		mg.showMenu();

		// if an integer was entered cin succeeds:
		if(cin >> answer)
		{
			// check for bad integers:
			if(answer<1 || answer>9 || answer==8)
			{
				cout << "\nERROR - Not a valid choice\n" << endl;
				answer = 0;
			}

			// the integer was good:
			else
			{
				// use the integer to call the appropriate method:
				switch(answer)
				{
					case 1: // set an assignment:
						mg.setAssign();
						break;
					case 2: // set a test:
						testNum = mg.setTest();
						if(testNum == 1)
							mg.setTest1();
						if(testNum == 2)
							mg.setTest2();
						break;
					case 3: // display assignments:
						mg.showAssign();
						break;
					case 4: // display tests:
						mg.showTests();
						break;
					case 5: // display all grades:
						mg.showAll(mg);
						break;
					case 6: // remove an assignment:
						mg.deleteAssign();
						break;
					case 7: // remove a test:
						mg.deleteTest();
						break;
				} // end switch
			} // end else
		} // end if

		// the user entered garbage (something besides an integer):
		else
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nERROR - Input must be an integer." << endl;
		}
	}

	// If the user enters a '9', end the loop:
	while(answer!=9);

	// goodbye message:
	cout << "\n\nImplemented by Jeremy Ecker" << endl << "February 2018\n\n";
}

/*******************************************************************************
*                             Main function:                                   *
*******************************************************************************/
int main()
{
	// create a MyGrades instance:
	MyGrades mg;

	// initiate the main program loop:
	mg.loop(mg);

    return 0;
}















