/*******************************************************************************
* Roster Number: 5                                                             *
*                                                                              *
* Author: Jeremy Ecker                                                         *
* Due Date: ???                                                                *
* Programming Assignment Number 5                                              *
*                                                                              *
* Spring 2018 - CS 3358 - 2??                                                  *
*                                                                              *
* Instructor: Husain Gholoom.                                                  *
*                                                                              *
* This program demonstrates some simple uses of recursion, using dynamically   *
* created arrays filled with random numbers.                                   *
*******************************************************************************/

#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;

/*******************************************************************************
*                      function declarations:                                  *
*******************************************************************************/

void greeting();
void quickSort();
void loop();
void showMenu();
void timeSort();
void goodbye();
int getRandom();
int getArraySize();
void showSquares();
void getSquares();
int getLargest();
void showPower();
long int getPower();
void showLargest();
int getDigitSum();
void showDigitSum();
bool isPrime();
void showPrime();

/*******************************************************************************
*                      main function:                                          *
*******************************************************************************/

int main()
{
	loop();
	return 0;
}

/*******************************************************************************
*                      function implementations:                               *
*******************************************************************************/

// Gets a random number between 10 and 1000:
int getRandom()
{
    int k = rand() % (1001 - 10) + 10;
    return k;
}

// Prints the main menu:
void showMenu()
{
	printf("\nSelect from the following menu\n"
		   "A.\tEnter Array Size that is > 10.\n"
		   "X.\tTerminate The Program.\t\t");
}

// Prints the greeting:
void greeting()
{
	printf("\nThinking Recursively\n\n"
		   "The function of this program is to\n"
		   "use recursion in order to perform the following operations :-\n\n"
		   "\t1. Display squares of integers in ascending order from 1 to the\n"
		   "\t   last element in the array\n"
		   "\t2. Raise the first number to a power  2\n"
		   "\t3. Find the array's max value.\n"
		   "\t4. Sort the array in descending order\n"
		   "\t5. Calculating sum of digits\n"
		   "\t6. Determine if a number is prime (processes all array values)\n"
		   );
}

// Prints the goodbye message:
void goodbye()
{
	printf("\n\nJeremy Ecker - Tweak Programming Developer\n"
		   "April 2018\n\n");
}

// Descending Quick Sort with right-hand pivot:
void quickSort(long int *array, int left, int right)
{
	int i = left;
	int j = right;
	int tmp;
	int pivot = array[right];

	// partition
	while(i <= j)
	{
		while(array[i] > pivot)
		{
			i++;
		}
		while(array[j] < pivot)
		{
			j--;
		}
		if(i <= j)
		{
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}

	// recursion
	if(left < j)
	{
		quickSort(array, left, j);
	}
	if(i < right)
	{
		quickSort(array, i, right);
	}
}

// Calls quickSort and times its execution:
void timeSort(long int *array, int size)
{
	clock_t start;
	clock_t end;

	start = clock();

	quickSort(array,0,size-1);

	end = clock();

	cout << "Sorted Array" << endl << endl;
	for(int k=0; k<size; k++)
	{
		cout << (int)array[k] << " ";
	}
	cout << endl << endl;

	double actualTime = (end - start) / (double)(CLOCKS_PER_SEC / 1000);
	
	cout << "Start Time\t: " << start << endl;
	cout << "End Time\t: " << end << endl;
	cout << "Actual CPU Clock time\t: " << actualTime << " ms" << endl << endl;
}

// Gets a valid array size from user input:
int getArraySize()
{
	int size = 0;
	bool valid = false;
	printf("Enter Array Size: ");

	do
	{
		if(cin >> size)
		{		
			if(size < 10 || size > 1000)
			{
				printf("\n\n*** Invalid Array Size Value ***\n");
				printf("Enter Array Size that is >= 10 and <= 1000 : ");
			}
			else
			{
				cin.clear();
				cin.ignore(10000, '\n');
				valid = true;
			}
		}
		else
		{
			printf("\n\n*** Invalid Array Size Value ***\n");
			printf("Enter an integer not a char: ");
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	while(valid == false);

	return size;
}

// Gets the largest number from the array:
int getLargest(long int *array, int current, int last, int largest)
{
	if(current != last)
	{
		if(largest < array[current])
		{
			largest = array[current];
		}
		largest = getLargest(array,current+1,last,largest);
	}
	else
	{
		return largest;
	}
}

// Calls getLargest and displays formatted output:
void showLargest(long int *array, int size)
{
	int current = 1;
	int last = size-1;
	int largest = array[0];
	largest = getLargest(array,current,last,largest);
	printf("Max number of (");
	for(int k=0; k<size-1; k++)
	{
		int temp = (int)array[k];
		printf(" %d, ",temp);
	}
	int temp = (int)array[size-1];
	printf("%d ) is : %d\n\n",temp,largest);
}

// Gets squares of numbers from current to last:
void getSquares(int last, int current)
{
	if(current != last)
	{
		long int square = current*current;
		printf("%-8d%ld\n",current,square);
		getSquares(last,current+1);
	}
	else
	{
		long int square = current*current;
		printf("%-8d%ld\n",current,square);
	}
}

// Calls getSquares for 1 through last array value:
void showSquares(long int *array, int size)
{
	int last = array[size-1];
	printf("\nTable of square values 1 - %d\n\n",last);
	printf("N\tN Squared\n\n");
	getSquares(last,1);
	cout << endl;
}

// Raise number to power:
long int getPower(long int number, int power)
{
	if(power > 1)
	{
		number = number*number;
		getPower(number,power-1);
	}
	else
	{
		return number;
	}
}

// Calls getPower to get square of first array value:
void showPower(long int *array)
{
	int first = array[0];
	int power = 2;
	long int answer = getPower(first,power);

	cout << "Power Function:" << endl;
	printf("%d raised to the 2nd power is: %ld\n\n",first,answer);
}

// Gets sum of digits for number:
int getDigitSum(int number, int answer)
{
	if(number == 0)
	{
		return answer;
	}
	else
	{
		answer = answer + number % 10;
		number = number / 10;
		return getDigitSum(number, answer);
	}
}

// Calls getDigitSum for the first value in the array:
void showDigitSum(long int *array)
{
	int number = array[0];
	int answer = 0;
	answer = getDigitSum(number,answer);
	cout << "Sum of digits for the number " << number << "\tis\t" << answer 
		 << endl << endl;
}

// Discovers whether or not a value is prime:
bool isPrime(int value, int lesserValue)
{
	if(lesserValue == 1)
	{
		return true;
	}
	else
	{
		if(value % lesserValue == 0)
		{
			return false;
		}
		else
		{
			return isPrime(value, lesserValue-1);
		}
	}
}

// Calls getPrime for all array values and shows output:
void showPrime(long int *array, int size)
{
	bool prime = false;

	for(int k=0; k<size; k++)
	{
		prime = isPrime(array[k], array[k]-1);
		if(prime)
		{
			cout << array[k] << " is Prime" << endl;
		}
		else
		{
			cout << array[k] << " is Not Prime" << endl;
		}
	}	
}

// Program loop:
void loop()
{
	// initialize rand with time as seed:
	srand(time(NULL));

	// variable initializations:
	string answer = "";
	int arraySize = 0;
	long int *dynamicArray;

	// say the greeting:
	greeting();

	// start loop:
	do
	{
		// show the menu and get user choice:
		do 
		{	
			showMenu();
			getline(cin, answer);
			if(answer!="x" && answer!="X" && answer !="a" && answer!="A")
			{
				cout << "\n*** Invalid Option ***\n\n";
			}
		}
		// if the user entered a valid input, continue:
		while(answer != "x" && answer != "X" && answer != "a" && answer != "A");

		// if the user chooses 'A', execute the rest of the program:
		if(answer == "a" || answer == "A")
		{
			// get the array size from the user:
			arraySize = getArraySize();

			// assign the size to the array:
			dynamicArray = new long int[arraySize];

			// assign random numbers to the array elements:
			for(int k=0; k<arraySize; k++)
			{
				dynamicArray[k] = getRandom();
			}

			// print the first ten elements of the array:
			printf("\n\nThe generated array is:\n\n");
			for(int k=0; k<10; k++)
			{
				cout << dynamicArray[k] << " ";
			}
			cout << endl << endl;

			// show table of squares:
			showSquares(dynamicArray, arraySize);

			// show power function:
			showPower(dynamicArray);

			// show largest number in the array:
			showLargest(dynamicArray,arraySize);

			// sort the array:
			timeSort(dynamicArray,arraySize);

			// show sum of digits in first element:
			showDigitSum(dynamicArray);

			// show prime numbers:
			showPrime(dynamicArray,arraySize);

			// remember to clean up our mess:
			delete[] dynamicArray;
		}
	}
	// if the user chooses 'X', terminate the loop:
	while(answer == "a" || answer == "A");

	// say goodbye:
	goodbye();
}



