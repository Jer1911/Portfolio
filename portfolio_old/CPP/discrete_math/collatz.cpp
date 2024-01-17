#include <iostream>

using namespace std;

int f(int k) // compute the collatz sequence
{
    cout << k << ", ";
    if(k==1)
    {
        return 1;
    }
    else
    {
        if(k%2==0)
        {
            return(f(k/2)+1);
        }
        else
        {
            return(f(3*k+1)+1);
        }
    }
}

void get_input() // invoke f for a user input value
{
    int x, y;
    char c = 'y';
    while(c == 'y')
    {
        cout << "Enter a positive integer: ";
        cin >> x;
        y = f(x);
        y -= 1;
        cout << endl << "The number of iterations was: " << y << endl;
        cout << "Do you wish to continue? ('y' for yes, 'n' for no): ";
        cin >> c;
    }
}

void print_k(int n, int k) // print f for n
{
    cout << endl << "f(" << n << ") -> k = " << k << endl;
}

void sequence_length(int n) // invoke f n times
{
    for(int j=1; j<=n; j++)
    {
        int k = f(j)-1;
        print_k(j, k);
    }
}

void find_specific_length(int n) // find a value where k > n
{
	int k = 1;
	int j = 1;
	while(k<=n)
	{
		k = f(j)-1;
		j++;
	}
	j--;
	print_k(j, k);
}

void two_to_k(int k) // find successions of 2^k
{
	int x;
	int y;
	for(int j=2; j<=k; j*=2)
	{
		x = j;
		y = f(x)-1;
		print_k(x,y);
	}
}

int main()
{
	two_to_k(1000000);
    //sequence_length(30);
	//find_specific_length(200);
	//get_input();

    return 0;
}

