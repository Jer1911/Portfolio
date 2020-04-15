#include <iostream>
using namespace std;

int f(int k) // compute the collatz sequence
{
    cout << k << ", "; // comment this line out if not needed.
    if(k==1) // the sequence is done when 1 is encountered.
    {
        return 1;
    }
    else
    {
        if(k%2==0) // test for even.
        {
            return(f(k/2)+1); // get the next value using even function.
        }
        else // if it isn't even, it's odd.
        {
            return(f(3*k+1)+1); // get the next value using odd function.
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

		// remember to decrement, because of the way k is counted.
        y = f(x);
        y -= 1;
 
        cout << endl << "The number of iterations was: " << y << endl;
        cout << "Do you wish to continue? ('y' for yes, 'n' for no): ";
        cin >> c;
    }
}

int main()
{
	get_input();
	return 0;
}
