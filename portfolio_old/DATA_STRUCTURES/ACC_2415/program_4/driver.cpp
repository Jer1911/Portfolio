// driver.cpp

//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <iostream>
#include <string>
#include "LinkedBag.h"
using namespace std;

void displayBag(LinkedBag<std::string>& bag)
{
   std::cout << "The bag contains " << bag.getCurrentSize()
   << " items:" << std::endl;
   std::vector<std::string> bagItems = bag.toVector();
   
   int numberOfEntries = (int) bagItems.size();
   for (int i = 0; i < numberOfEntries; i++)
   {
      std::cout << bagItems[i] << " ";
   }  // end for
   std::cout << std::endl << std::endl;
}  // end displayBag

void copyConstructorTester()
{
   LinkedBag<std::string> bag;
   std::string items[] = {"zero", "one", "two", "three", "four", "five"};
   for (int i = 0; i < 6; i++)
   {
      std::cout << "Adding " << items[i] << std::endl;
      bool success = bag.add(items[i]);
      if (!success)
         std::cout << "Failed to add " << items[i] << " to the bag." << std::endl;
   }
   displayBag(bag);
   
   LinkedBag<std::string> copyOfBag(bag);
   std::cout << "Copy of bag: ";
   displayBag(copyOfBag);
   
   std::cout << "The copied bag: ";
   displayBag(bag);
}  // end copyConstructorTester

void bagTester()
{
   LinkedBag<std::string> bag;
   std::cout << "Testing the Link-Based Bag:" << std::endl;
   std::cout << "isEmpty: returns " << bag.isEmpty()
   << "; should be 1 (true)" << std::endl;
   displayBag(bag);
   
   std::string items[] = {"one", "two", "three", "four", "five", "one"};
   std::cout << "Add 6 items to the bag: " << std::endl;
   for (int i = 0; i < 6; i++)
   {
      bag.add(items[i]);
   }  // end for
   
   displayBag(bag);
   
   std::cout << "isEmpty: returns " << bag.isEmpty()
   << "; should be 0 (false)" << std::endl;
   
   std::cout << "getCurrentSize: returns " << bag.getCurrentSize()
   << "; should be 6" << std::endl;
   
   std::cout << "Try to add another entry: add(\"extra\") returns "
   << bag.add("extra") << std::endl;
   
   std::cout << "contains(\"three\"): returns " << bag.contains("three")
   << "; should be 1 (true)" << std::endl;
   std::cout << "contains(\"ten\"): returns " << bag.contains("ten")
   << "; should be 0 (false)" << std::endl;
   std::cout << "getFrequencyOf(\"one\"): returns "
   << bag.getFrequencyOf("one") << " should be 2" << std::endl;
   std::cout << "remove(\"one\"): returns " << bag.remove("one")
   << "; should be 1 (true)" << std::endl;
   std::cout << "getFrequencyOf(\"one\"): returns "
   << bag.getFrequencyOf("one") << " should be 1" << std::endl;
   std::cout << "remove(\"one\"): returns " << bag.remove("one")
   << "; should be 1 (true)" << std::endl;
   std::cout << "remove(\"one\"): returns " << bag.remove("one")
   << "; should be 0 (false)" << std::endl;
   std::cout << std::endl;
   
   displayBag(bag);
   
   std::cout << "After clearing the bag, ";
   bag.clear();
   
   std::cout << "isEmpty: returns " << bag.isEmpty()
   << "; should be 1 (true)" << std::endl;
}  // end bagTester

void myTest() // MY TESTING FUNCTION
{
    // test of add method:
    std::cout<<"----------------------------------------\n";
    std::cout<<"This is a test of the 'add' method:   \n\n";
    LinkedBag<std::string> bag;
    std::string items[] = {"zero", "one", "two", "three", "four", "five"};
    for (int i = 0; i < 6; i++)
    {
        std::cout << "Adding " << items[i] << std::endl;
        bool success = bag.add(items[i]);
        if (!success)
            std::cout << "Failed to add " << items[i] << " to the bag." << std::endl;
        else
        {
            std::cout << "success, added " << items[i] << std::endl;
            displayBag(bag);
        }
    }
    std::cout<<"'add' method test concluded.            \n";
    std::cout<<"----------------------------------------\n";

    // test of remove method:
    std::cout<<"This is a test of the 'remove' method:\n\n";
    srand(time(NULL)); // for seeding rand()
    displayBag(bag);   
    for(int k=0; k<6; k++)
    {
        bag.remove();
        displayBag(bag);
    }
    std::cout<<"'remove' method test concluded.         \n";
    std::cout<<"----------------------------------------\n";
}

int main()
{
    myTest();
    return 0;
}  // end main

