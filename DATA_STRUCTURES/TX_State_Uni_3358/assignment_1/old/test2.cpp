#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int get_random()
{
    int k = rand()%12+1;
    return k;
}

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
                    cout << "bad number found: " << temp << endl;
                    good_num = false;
                    i--;
                }
            }
        }
        while(good_num = false);

        array[i] = temp;
        i++;
    }
}

void display_1d(int array[], int WIDTH)
{
    for(int k=0; k<WIDTH; k++)
    {
        cout << array[k] << " ";
    }
    cout << endl;
}

int main()
{
    srand(time(NULL));
    const int WIDTH = 9;
    int array0[WIDTH] = {0};

    populate_1d(array0, WIDTH);

    display_1d(array0, WIDTH);

    return 0;
}
