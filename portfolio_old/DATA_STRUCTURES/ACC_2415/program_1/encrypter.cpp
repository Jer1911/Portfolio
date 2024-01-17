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
    // variable declaractions
    int choice;
    string input, input2;

    // welcome message
    cout << "\n-------------------------------------------------\n";
    cout << "Welcome to the Encrypter\n";
    cout << "Author: Jeremy Ecker\n";
    cout << "This program encrypts strings.\n";
    cout << "-------------------------------------------------\n\n";

    do
    { // Display menu, for easily trying the different methods
        cout << "-------------------------------------------------\n";
        cout << "Encrypter main menu:\n";
        cout << "-------------------------------------------------\n";
        cout << "1 Default constructor\n";
        cout << "2 Constructor with string argument\n";
        cout << "3 Get() method\n";    
        cout << "4 Quit program\n";
        cout << "-------------------------------------------------\n";
        cout << "Type your choice number and press enter: ";
        cin >> choice;
        cout << "\n";

        if (choice < 1 || choice > 4) // Error handler
        {
            cout << "You have entered an invalid input. Try again.\n\n";
        }
        else if (choice == 1) // default constructor
        {
            EncryptedString test0;
            cout << "The default constructor returns: " << test0.getEncrypted() << "\n\n";
        }
        else if (choice == 2) // constructor with string argument
        {
            cout << "Now we will test a non-empty private member string." << endl;
            cout << "Enter a string to encrypt: ";
            if (cin.peek() == '\n') //handler for trailing newlines in stream
                cin.ignore();
            getline(cin, input);
            EncryptedString test(input);
            cout << "Your string is now encrypted as:\n" << test.getEncrypted() << "\n\n";
        }
        else if (choice == 3) // get() method test
        {
            cout << "Now we will test the get() method." << endl;
            cout << "Enter a string to excercise get(): ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, input2);
            EncryptedString test2(input2);
            cout << "Your string after get() is:\n" << test2.get() << "\n\n";
        }
    }
    while (choice != 4);

    // goodbye message
    cout << "-------------------------------------------------\n";
    cout << "Thank you for using Encrypter\n";
    cout << "Written by Jeremy Ecker\n";
    cout << "-------------------------------------------------\n\n";  
            
    return 0;
}

