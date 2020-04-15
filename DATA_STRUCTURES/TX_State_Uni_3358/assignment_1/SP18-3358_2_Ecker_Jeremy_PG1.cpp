/******************************************************************************
* Author: Jeremy Ecker                                                        *
* Serial Number: 5                                                            *
* Due Date: 2/5/1018                                                          *
* Programming Assignment Number 1                                             *
* Spring 2018 - CS 3358 - Section Number 262                                  *
*                                                                             *
* Instructor: Husain Gholoom                                                  *
*                                                                             *
* This program creates arrays of integers from random number generator and    *
* finds: sum, product, determinant, special number, and special array.        *
******************************************************************************/

#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

/*******************************************************************************
*                            Function Prototypes:                              *
*******************************************************************************/

// Gets a random number between 1 and 12:
int get_random();

// Populates a one dimensional array with non-repeating random numbers:
void populate_1d(int array0[], int WIDTH);

// Populates a two-dimensional array using a one-dimensional array:
void populate_2d(int array1d[], int array2d[][3], int SIZE);

// Displays a two-dimensional array:
void display_2d(int array[][3], int SIZE);

// Greeting:
void greeting();

// Adds two 2d arrays, places results in third 2d array:
void add2d(int array1[][3], int array2[][3], int array3[][3], int SIZE);

// Multiplies two 2d arrays, places results in third 2d array:
void multiply2d(int array1[][3], int array2[][3], int array3[][3], int SIZE);

// Finds Transpose of a 2d array:
void transpose2d(int array1[][3], int array3[][3], int SIZE);

// Finds the Determinant of a 2d array:
void determinant(int array1[][3]);

// Finds the sum of row 1 of elements:
int row_sum1(int array1[][3], int SIZE);

// Finds the sum of row 2 of elements:
int row_sum2(int array1[][3], int SIZE);

// Finds the sum of row 3 of elements:
int row_sum3(int array1[][3], int SIZE);

// Finds the sum of column 1 of elements:
int col1_sum(int array1[][3], int SIZE);

// Finds the sum of column 2 of elements:
int col2_sum(int array1[][3], int SIZE);

// Finds the sum of column 3 of elements:
int col3_sum(int array1[][3], int SIZE);

// Finds the sum of diagonal 1 of elements:
int diag1_sum(int array1[][3], int SIZE);

// Finds the sum of diagonal 2 of elements:
int diag2_sum(int array1[][3], int SIZE);

// Calculates the Special Number then calls the row/column/diagonal functions:
void special_num(int array1[][3], int n);

// Program loop:
void loop();

/*******************************************************************************
*                             Main Function:                                   *
*******************************************************************************/
int main()
{
	loop();
	return 0;
}

/*******************************************************************************
*                           Function Definitions:                              *
*******************************************************************************/

// Gets a random number between 1 and 12:
int get_random()
{
    int k = rand()%12+1;
    return k;
}

/* Populates a one dimensional array with non-repeating random numbers:
   param int array[]
   param int WIDTH
*/
void populate_1d(int array0[], int WIDTH)
{
    int i = 1;
	int j = 0;

    array0[0] = get_random();

    do
    {
        array0[i] = get_random();
        j = 0;
        while(j<i)
        {
            if(array0[j] == array0[i])
            {
				i--;
				break;
            }
			j++;
        }
		i++;
    }
    while(i<WIDTH);
}

/* Populates a two-dimensional array using a one-dimensional array:
   param int array[]
   param int array[3][3]
   param int SIZE
*/
void populate_2d(int array1d[], int array2d[][3], int SIZE)
{
	int k = 0;
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			array2d[i][j] = array1d[k];
			k++;
		}
	}
}

/* Displays a two-dimensional array:
   param int array[3][3]
   param int SIZE
*/
void display_2d(int array[][3], int SIZE)
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Display the greeting:
void greeting()
{
    cout << endl
    	 << "Welcome to my array program. The function of the program is to"
         << endl << endl
    	 << "1. Create 2 Arrays (Array_1, Array_2). Each array is of size "
         << "3x3." << endl
    	 << "2. Populate both Arrays with distinct random numbers that are "
         << "between 1 and 12. " << endl << "   Display both Arrays." << endl
    	 << "3. Adding and multiplying Array_1 and Array_2." << endl
    	 << "4. Displaying the transposed and the determinate of Array_1."
         << endl
    	 << "5. Displaying the sum of elements of each row of Array_1, " 
         << endl
         << "   displaying the sum of elements of each column of Array_1, "
         << endl
         << "   displaying the sum of both diagonal elements of Array_1."
         << endl
    	 << "6. Finally, determining whether or not Array_1 is a special "
         << "array." << endl
    	 << "7. Repeating the above steps until the user terminates the "
         << "program." << endl << endl;
}

/* Adds two 2d arrays, places results in third 2d array:
   param int array[3][3]
   param int array[3][3]
   param int array[3][3]
   param int SIZE
*/
void add2d(int array1[][3], int array2[][3], int array3[][3], int SIZE)
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            array3[i][j] = array1[i][j] + array2[i][j];
        }
    }
}

/* Multiplies two 2d arrays, places results in third 2d array:
   param int array[3][3]
   param int array[3][3]
   param int array[3][3]
   param int SIZE
*/
void multiply2d(int array1[][3], int array2[][3], int array3[][3], int SIZE)
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            array3[i][j] = array1[i][j] * array2[i][j];
        }
    }
}
/* Finds Transpose of a 2d array:
   param int array[3][3]
   param int array[3][3]
   param int SIZE
*/
void transpose2d(int array1[][3], int array3[][3], int SIZE)
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            array3[j][i] = array1[i][j];
        }
    }
}

/* Finds the Determinant of a 2d array:
   param int array[3][3]
*/
void determinant(int array1[][3])
{
	// variables a through i represent values contained in the array
	int a = array1[0][0];
	int b = array1[0][1];
	int c = array1[0][2];
	int d = array1[1][0];
	int e = array1[1][1];
	int f = array1[1][2];
	int g = array1[2][0];
	int h = array1[2][1];
	int i = array1[2][2];

	int determinant = (a*((e*i)-(f*h)))-(b*((d*i)-(f*g)))+(c*((d*h)-(e*g)));

	cout << "Determinant of Array_1: " << determinant << endl << endl;
}

/* Finds the sum of row 1 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int row_sum1(int array1[][3], int SIZE)
{
	int row1 = 0;

	for(int i=0; i<SIZE; i++)
	{
		row1 += array1[0][i];
	}
	cout << "Sum of numbers in Row # 1 in Array_1 = " << row1 << endl;
	return row1;
}

/* Finds the sum of row 2 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int row_sum2(int array1[][3], int SIZE)
{
	int row2 = 0;

	for(int i=0; i<SIZE; i++)
	{
		row2 += array1[1][i];
	}
	cout << "Sum of numbers in Row # 2 in Array_1 = " << row2 << endl;
	return row2;
}

/* Finds the sum of row 3 of elements:
   param int array[3][3]
   return int
*/
int row_sum3(int array1[][3], int SIZE)
{
	int row3 = 0;

	for(int i=0; i<SIZE; i++)
	{
		row3 += array1[2][i];
	}
	cout << "Sum of numbers in Row # 3 in Array_1 = " << row3 << endl << endl;
	return row3;
}

/* Finds the sum of column 1 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int col1_sum(int array1[][3], int SIZE)
{
	int col1 = 0;

	for(int i=0; i<SIZE; i++)
	{
		col1 += array1[i][0];
	}

	cout << "Sum of numbers in Column # 1 in Array_1 = " << col1 << endl;
	return col1;
}

/* Finds the sum of column 2 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int col2_sum(int array1[][3], int SIZE)
{
	int col2 = 0;

	for(int i=0; i<SIZE; i++)
	{
		col2 += array1[i][1];
	}

	cout << "Sum of numbers in Column # 2 in Array_1 = " << col2 << endl;
	return col2;
}

/* Finds the sum of column 3 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int col3_sum(int array1[][3], int SIZE)
{
	int col3 = 0;

	for(int i=0; i<SIZE; i++)
	{
		col3 += array1[i][2];
	}

	cout << "Sum of numbers in Column # 3 in Array_1 = " << col3 << endl 
		 << endl;
	return col3;
}

/* Finds the sum of diagonal 1 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int diag1_sum(int array1[][3], int SIZE)
{
	int diag1 = 0;

	for(int i=0; i<SIZE; i++)
	{
		diag1 += array1[i][i];
	}

	cout << "Sum of numbers in first diagonal in Array_1 = " << diag1 << endl;
	return diag1;
}

/* Finds the sum of diagonal 2 of elements:
   param int array[3][3]
   param int SIZE
   return int
*/
int diag2_sum(int array1[][3], int SIZE)
{
	int diag2 = 0;

	int j = 2;
	for(int i=0; i<SIZE; i++)
	{
		diag2 += array1[i][j];
		j--;
	}

	cout << "Sum of numbers in second diagonal in Array_1 = " << diag2 << endl
		 << endl;
	return diag2;
}

/* Calculates the Special Number then calls the row/column/diagonal functions:
   param int array[3][3]
   param int n // SIZE
*/
void special_num(int array1[][3], int n)
{
	// Calculate the Special Number:
	int sn = 0; // special number
	sn = (n*(n*n+1))/2;

	// Call the adding functions:
	int rs1 = row_sum1(array1, n); // row 1 sum
	int rs2 = row_sum2(array1, n); // row 2 sum
	int rs3 = row_sum3(array1, n); // row 3 sum
	int cs1 = col1_sum(array1, n); // column 1 sum
	int cs2 = col2_sum(array1, n); // column 2 sum
	int cs3 = col3_sum(array1, n); // column 3 sum
	int ds1 = diag1_sum(array1, n); // diagonal 1 sum
	int ds2 = diag2_sum(array1, n); // diagonla 2 sum

	cout << "Special Number = " << sn << endl << endl;

	// Check to see if the array is Special:
	if(sn==rs1 && sn==rs2 && sn==rs3 && sn==cs1 && sn==cs2 && sn==cs3
		&& sn==ds1 && sn==ds2)
	{
		cout << "The above is a Special Array" << endl << endl;
	}
	else
		cout << "The above is not a Special Array" << endl << endl;
}

// Program loop:
void loop()
{
    srand(time(NULL)); // initialize seed from timer

	// initialize variables and arrays:
    const int WIDTH = 9; // one-dimensional array width
	const int SIZE = 3; // two-dimensional array size
	string answer = ""; // stores the answer for the continue prompt
    int array0[WIDTH] = {0}; // one-dimensional array
	int array1[SIZE][SIZE] = {0}; // first two-dimensional array
	int array2[SIZE][SIZE] = {0}; // second two-dimensional array
    int array3[SIZE][SIZE] = {0}; // third two-dimensional array

    greeting(); // say the greeting

	// Initiate the loop:
	do
	{
		// populate a 1D array, then use it to populate 2d array, then display:
	    populate_1d(array0, WIDTH);
		populate_2d(array0, array1, SIZE);
    	cout << "Array_1:" << endl << endl;
		display_2d(array1, SIZE);

		// populate a 1D array, then use it to populate 2d array, then display:
    	populate_1d(array0, WIDTH);
		populate_2d(array0, array2, SIZE);
    	cout << "Array_2:" << endl << endl;
		display_2d(array2, SIZE);

		// add the two arrays together and display:
    	add2d(array1, array2, array3, SIZE);
    	cout << "Sum of Array_1 and Array_2:" << endl << endl;
    	display_2d(array3, SIZE);

		// multiply the two arrays together and display:
    	multiply2d(array1, array2, array3, SIZE);
    	cout << "Product of Array_1 and Array_2:" << endl << endl;
    	display_2d(array3, SIZE);

		// transpose the first array and display:
    	transpose2d(array1, array3, SIZE);
    	cout << "Transpose of Array_1:" << endl << endl;
    	display_2d(array3, SIZE);

		// find the determinant of the first array and display:
		determinant(array1);

		// find the special number of the first array and display:
		special_num(array1, SIZE);

		// prompt the user to ask if they want to play again:
		do
		{
			cout << "Would you like to check another Array?"
				 << endl << "Enter y|Y for yes or n|N for no" << endl;
			getline(cin, answer);
			if(answer!="y" && answer!="Y" && answer!="n" && answer!="N")
			{
				cout << "Error *** Invalid choice - Must enter y|Y | n|N" 
					 << endl;
			}
		}
		while(answer!="y" && answer!="Y" && answer!="n" && answer!="N");
	}
	while(answer=="y" || answer =="Y");

	cout << endl << "This algorithm is implemented by Jeremy Ecker" 
		 << endl << endl;
}






