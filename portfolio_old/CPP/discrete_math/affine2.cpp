#include<iostream>
#include<cmath>
using namespace std;

// encryption function:
int f(int x)
{
	int y;
	y = (5*x+4) % 26;
	return y;
}

// decryption function:
int g(int x)
{
	int y;
	y = (21*(x-4)) % 26;
	if(y<0)
	{
		y+=26;
	}
	return y;
}

// main function:
int main()
{
	int x, y;
	cout << "enter int: " << endl;
	cin >> x;

	y = g(x);

	cout << "decrypted: " << y << endl;

	return 0;
}
