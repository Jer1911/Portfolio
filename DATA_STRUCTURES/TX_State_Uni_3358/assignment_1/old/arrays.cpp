#include<iostream>
#include<random>
#include<chrono>

using namespace std;

int generate_int(default_random_engine my_engine, uniform_int_distribution<int> my_distribution)
{
    int my_int = my_distribution(my_engine);
    return my_int;
}

int main()
{
    // initialize number generator:
    unsigned my_seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine my_engine(my_seed);
    uniform_int_distribution<int> my_distribution(1,12);

    cout << "Testing some 2d arrays:" << endl;

    int array1[3][3];
    int array2[3][3];

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            array1[i][j] = generate_int(my_engine, my_distribution);
            cout << array1[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}
