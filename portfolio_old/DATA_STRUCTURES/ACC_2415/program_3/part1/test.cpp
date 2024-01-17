/************************************************************************
test.cpp: A simple power() function, which disregards negative exponents.
Author: Jeremy Ecker
Assignment: 3 (part 1)
COSC-2436 (Programming Fundamentals III: Data Structures, 18736)
Date: 2/15/2017
************************************************************************/

#include<iostream>
using namespace std;

double power(double a, int n)
{
    if(n <= 0)
        return 1;
    else if(n==1)
        return a;
    else if(n>0)
        return(a*power(a, n-1));
}

int main()
{
    double base;
    int exponent;

    // intro
    cout << endl << "This program computes a power function." << endl;
    cout << "A base may be entered as a double precision float value." << endl;
    cout << "An exponent may be entered as an integer." << endl << endl;

    cout << "Enter a base: ";
    cin >> base;
    cout << "Enter an exponent: ";
    cin >> exponent;
    
    double test = power(base, exponent);

    cout << "Result of power function = " << test << endl << endl;

    return 0;
}

