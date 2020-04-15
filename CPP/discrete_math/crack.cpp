#include<iostream>
#include<cmath>

using namespace std;

int p_calc(int n, int k)
{
	int p = k;
	while(p != 1)
	{
		if(n%p==0)
		{
			return p;
		}
		else
		{
			p -= 1;
		}
	}
}

int main()
{
	// get starting values:
	double n_in, sqrt_n;
	int p, q;
	cout << "enter n: " << endl;
	cin >> n_in;

	// find the square root of n:
	sqrt_n = sqrt(n_in);
	cout << "the square root of n is: " << sqrt_n << endl;

	// find the floor of sqrt_n:
	sqrt_n = floor(sqrt_n);
	int k = (int) sqrt_n; // cast it to int.
	int n = (int) n_in; // go ahead and cast n as well.
	cout << "the floor of the sqrt of n is: " << k << endl;

	// find p:
	p = p_calc(n, k);
	cout << "p is: " << p << endl;

	// find q:
	q = n/p;
	cout << "q is: " << q << endl;

	// find pq;
	int pq = (p-1)*(q-1);
	cout << "(p-1)(q-1) is: " << pq << endl;

	return 0;
}
