#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
    cout << "testing out some shit, in this bitch:" << endl;

    int array0[9] = 0; // one dimensional array for testing numbers
    int array1[3][3]; // first two dimensional array
    int array2[3][3]; // second two dimensional array
    srand(time(NULL)); // seed for rand()
    bool match = true; // flag to test if numbers repeat
    int count = 0; // counter for testing repeating numbers

    for(int i=0; i<9; i++)
    {
        int temp = -1;
        while(match == true)
        {
            temp = rand()%12+1;
            for(int j=0; j<=count; j++)
            {
                if(!temp == array0[j])
                {
                    match == false;
                    array0[i] = temp;
                }
            }
        }
    }

    /*
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            int k = rand() % 12 + 1;
            array1[i][j] = rand() % 12 + 1;
            cout << array1[i][j] << ", ";
        }
        cout << endl;
    }
    */

    return 0;
}
