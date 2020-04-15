#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

// Gets a random number between 1 and 12:
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

int main()
{
    srand(time(NULL)); // initialize seed from timer
    const int WIDTH = 9; // one-dimensional array width
    int array0[WIDTH] = {0}; // one-dimensional array

	for(int i=0; i<10; i++)
	{
		populate_1d(array0, WIDTH);
		display_1d(array0, WIDTH);
	}
	return 0;
}



