/** @file driver.cpp */

/***************************************************************
driver.cpp
Author: Jeremy Ecker
Assignment: 2
COSC-2436 (Programming Fundamentals III: Data Structures, 18736)
Date: 2/3/2017
***************************************************************/


#include <iostream>
#include "Rectangle.h"
using namespace std;

int main()
{
    // variable declarations
    int choice;
    double linput, winput;

    do
    { // Menu
        cout << "-------------------------------------------------\n";
        cout << "Rectangle main menu:\n";
        cout << "-------------------------------------------------\n";
        cout << "1 Run the program\n";
        cout << "2 Quit program\n";
        cout << "-------------------------------------------------\n";
        cout << "Type your choice number and press enter: ";
        cin >> choice;
        cout << "\n";

        if (choice < 1 || choice > 2) // Error handler
        {
            cout << "You have entered an invalid input. Try again.\n\n";
        }
        else if (choice == 1) // Run the program
        {
            Rectangle theRectangle;
    
            cout << "Intital state of the Rectangle" << endl;
            cout << "   length = " << theRectangle.getLength() << endl;
            cout << "   width = " << theRectangle.getWidth() << endl;
            cout << "   area = " << theRectangle.getArea() << endl << endl;

            cout << "Enter a new length value: ";
            cin >> linput;
            cout << "Enter a new width value: ";
            cin >> winput;
            cout << endl;

            theRectangle.set(linput, winput);
    
            cout << "Current state of the Rectangle" << endl;
            cout << "   length = " << theRectangle.getLength() << endl;
            cout << "   width = " << theRectangle.getWidth() << endl;
            cout << "   area = " << theRectangle.getArea() << endl << endl;
        }
    }
    while (choice !=2);
    return 0;
}

