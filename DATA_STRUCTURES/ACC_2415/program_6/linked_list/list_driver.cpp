/***************************************************************
array_driver.cpp
Author: Jeremy Ecker
Assignment: 6 (part two, lists)
COSC-2436 (Programming Fundamentals III: Data Structures, 18736)
Date: 4/1/2017
***************************************************************/
#include<iostream>
#include<string>
#include "LinkedList.h"
using namespace std;

// function displayList : displays the contents of the list
void displayList(ListInterface<string>* listPtr)
{
    if (listPtr->isEmpty())
        cout << "The list is empty" << endl;
    else
    {
        cout << "The list contains: " << endl;
        for (int pos = 1; pos <= listPtr->getLength(); pos++)
        {
            cout << listPtr->getEntry(pos) << " ";
        }
        cout << endl;
    }
}

// function filler : fills up the list
void filler(ListInterface<string>* listPtr, string local_array[])
{
    cout << endl << "Filling list: " << endl;
    for(int k=0; k<5; k++)
    {
        listPtr->insert((k+1), local_array[k]);
        cout << local_array[k] << " ";
    }
    cout << endl;
    cout << "List created." << endl;
    displayList(listPtr);
}

// function tester : tests the new methods getPosition and remove
void tester(ListInterface<string>* listPtr, string local_array[])
{
    // test of getPosition:
    for(int k=0; k<5; k++)
    {
        cout << "The position of item " << local_array[k] << " is: ";
        cout << listPtr->getPosition(local_array[k]) << endl;
    }
    // test of remove:
    for(int k=0; k<5; k++)
    {
        cout << "Removing item " << local_array[k] << "... " << endl;
        if(listPtr->remove(local_array[k]))
        {
            cout << "Item successfully removed. " << endl;
            displayList(listPtr);
        }
    }
    cout << endl;
}

// function main :
int main()
{
    ListInterface<string>* listPtr = new LinkedList<string>();
    string local_array[5] = {"one", "two", "three", "four", "five"};
    filler(listPtr, local_array);
    tester(listPtr, local_array);
    return 0;
}

