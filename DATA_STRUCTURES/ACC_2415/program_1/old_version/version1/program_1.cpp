/***************************************************************
program_1.cpp
Author: Jeremy Ecker
Assignment: 1
COSC-2436 (Programming Fundamentals III: Data Structures, 18736)
Date: 1/17/2017
***************************************************************/

#include<iostream>
#include<string>
#include "encrypt.h"
using namespace std;

int main(int argc, char *argv[])
{
    string input, output;

    cout << "Enter a string to encrypt: ";
    getline(cin, input);

    ENCRYPT test;
    //cout << "The adjusted string is: " << test.set(input) << endl;
    cout << "The adjusted string is: " << test.EncryptedString(input) << endl;

    return 0;
}
