#include<iostream>
#include<cmath>
using namespace std;

// encryption function:
int f(int x)
{
	int y;
	y = (3*x + 17) % 26;
	return y;
}

// decryption function:
int g(int x)
{
	int y;
	y = (9*(x-17)) % 26;
	if(y<0)
	{
		y+=26;
	}
	return y;
}

// main function:
int main()
{
	int choice, x, y;
	cout << "1 to encrypt, 2 to decrypt: " << endl;
	cin >> choice;

	if(choice == 1)
	{
		cout << "Enter int: " << endl;
		cin >> x;
		y = f(x);
		cout << "Encrypted: " << y << endl;
	}

	if(choice == 2)
	{
		cout << "Enter int: " << endl;
		cin >> x;
		y = g(x);
		cout << "Decrypted: " << y << endl;
	}

	return 0;
}
