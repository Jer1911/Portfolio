/***************************************************************
driver.cpp
Author: Jeremy Ecker
Assignment: 3, part 2
COSC-2436 (Programming Fundamentals III: Data Structures, 18736)
Date: 2/25/2017
***************************************************************/

//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <iostream>
#include <string>
#include "ArraySet.h"
using namespace std;
    
void displaySet(ArraySet<string>& set)
{
    cout << "The set contains " << set.getCurrentSize()
         << " items:" << endl;
    vector<string> setItems = set.toVector();
    int numberOfEntries = (int) setItems.size();
    for (int i = 0; i < numberOfEntries; i++)
    {
       cout << setItems[i] << " ";
    }  // end for
    cout << endl << endl;
}  // end displaySet

void setTester(ArraySet<string>& set)
{
    cout << "isEmpty: returns " << set.isEmpty() 
         << "; should be 1 (true)" << endl;
    displaySet(set);
    string items[] = {"one", "two", "three", "four", "five", "one"};
    cout << "Add 6 items to the set: " << endl;
    for (int i = 0; i < 6; i++)
    {
        set.add(items[i]);
    }  // end for
    displaySet(set);
    cout << "isEmpty: returns " << set.isEmpty() 
         << "; should be 0 (false)" << endl;
    cout << "getCurrentSize: returns " << set.getCurrentSize() 
         << "; should be 5" << endl;
    cout << "Try to add another entry: add(\"extra\") returns " 
         << set.add("extra") << endl;      
    cout << "contains(\"three\"): returns " << set.contains("three")
         << "; should be 1 (true)" << endl;
    cout << "contains(\"ten\"): returns " << set.contains("ten")
         << "; should be 0 (false)" << endl;
    cout << "remove(\"one\"): returns " << set.remove("one")
         << "; should be 1 (true)" << endl;
    cout << "remove(\"one\"): returns " << set.remove("one")
         << "; should be 0 (false)" << endl;
    cout << "remove(\"one\"): returns " << set.remove("one")
         << "; should be 0 (false)" << endl;
    cout << endl;
    displaySet(set);
    cout << "After clearing the set, ";
    set.clear();
    cout << "isEmpty: returns " << set.isEmpty()
         << "; should be 1 (true)" << endl;
}  // end setTester

void setTester2(ArraySet<string>& set2)
{
    displaySet(set2);
    cout << "isEmpty: returns " << set2.isEmpty()
         << "; should be 0 (false)" << endl;
    cout << "getCurrentSize: returns " << set2.getCurrentSize()
         << "; should be 6" << endl;
    cout << "Try to add another entry: add(\"extra\") returns "
         << set2.add("extra") << endl;
    cout << "contains(\"eenie\"): returns " << set2.contains("eenie")
         << "; should be 1 (true)" << endl;
    cout << "contains(\"ten\"): returns " << set2.contains("ten")
         << "; should be 0 (false)" << endl;
    cout << "remove(\"meenie\"): returns " << set2.remove("meenie")
         << "; should be 1 (true)" << endl;
    cout << "remove(\"minie\"): returns " << set2.remove("minie")
         << "; should be 1 (true)" << endl;
    cout << "remove(\"one\"): returns " << set2.remove("one")
         << "; should be 0 (false)" << endl;
    cout << endl;
    displaySet(set2);
    cout << "After clearing the set, ";
    set2.clear();
    cout << "isEmpty: returns " << set2.isEmpty()
         << "; should be 1 (true)" << endl;
}  // end setTester2


int main()
{
    ArraySet<string> set;
    cout << "Testing the Array-Based Set:" << endl;
    cout << "The initial set is empty." << endl;
    setTester(set);
    cout << "All done!" << endl;

    // create instance for parameterized constructor:
    int count = 6;
    string items[] = {"eenie", "meenie", "minie", "moe", "catcha", "tiger"};
    ArraySet<string> set2(items, count);

    // testing the constructor:
    cout << "------------------------------------"<< endl << "Testing our new constructor: " << endl;
    setTester2(set2);

    return 0;
}  // end main

