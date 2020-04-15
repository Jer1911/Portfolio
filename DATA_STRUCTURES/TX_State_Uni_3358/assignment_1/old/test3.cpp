#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

// Gets a random number:
int get_random()
{
    int k = rand()%12+1;
    return k;
}

// Displays a one dimensional array:
void display_1d(int array[], int WIDTH)
{
    for(int k=0; k<WIDTH; k++)
    {
        cout << array[k] << " ";
    }
    cout << endl;
}

// Populates a one dimensional array with non-repeating random numbers:
void populate_1d(int array[], int WIDTH)
{
    int i = 1;
    bool good_num = true;
    int temp = 0;

    array[0] = get_random();

    while(i<WIDTH)
    {
        do
        {
            good_num = true;
            temp = get_random();
            
            for(int j=0; j<i; j++)
            {
                if(temp == array[j])
                {
					temp = get_random();
                    good_num = false;
                    j=0;
                }
            }
        }
        while(good_num = false);

        array[i] = temp;
        i++;
    }
}

// Populates a two-dimensional array using a one-dimensional array:
void populate_2d(int array1d[], int array2d[3][3])
{
	int k = 0;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			array2d[i][j] = array1d[k];
			k++;
		}
	}
}

// Displays a two-dimensional array:
void display_2d(int array[3][3])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Main:
int main()
{
    srand(time(NULL)); // initialize seed from timer
    const int WIDTH = 9; // one-dimensional array width
    int array0[WIDTH] = {0}; // one-dimensional array
	int array1[3][3] = {0}; // first two-dimensional array
	int array2[3][3] = {0}; // second two-dimensional array

    populate_1d(array0, WIDTH);
	populate_2d(array0, array1);
	display_2d(array1);

    populate_1d(array0, WIDTH);
	populate_2d(array0, array2);
	display_2d(array2);

    return 0;
}
