/*******************************************************************
* driver.cpp                                                       *
* Author: Jeremy Ecker                                             *
* Assignment: 7                                                    *
* COSC-2436 (Programming Fundamentals III: Data Structures, 18736) *
* Date: 4/3/2017                                                   *
*******************************************************************/

#include<iostream>
#include<string>
#include "insertionSort.cpp"
#include "quickSort.cpp"
using namespace std;

int main()
{
	// Test of integer array:
	cout << endl;
	int int_array[25] = {20, 3, 18, 25, 1, 14, 17, 7, 9, 21, 11, 2, 15,
						 13, 8, 4, 24, 10, 12, 5, 6, 16, 19, 22, 23};
	cout << "Printing unsorted integer array: " << endl;
	for(int k=0; k<25; k++)
		cout << int_array[k] << " ";
	cout << endl << endl;
	quickSort(int_array, 0, 24);
	cout << endl << "Printing sorted integer array: " << endl;
	for(int k=0; k<25; k++)
		cout << int_array[k] << " ";
	cout << endl;

	// Test of string array:
	string str_array[28] = {"wine", "dine", "swine", "vine", "line", "brine", 
							"pine", "gruff", "tough", "enough", "rough",
							"snuff", "bluff", "puff", "plane", "vein", "stain",
							"crane", "lane", "wane", "train", "slate", "plate",
							"gate", "crate", "late", "irate", "elate"};
	cout << endl << "Printing unsorted string array: " << endl;
	for(int k=0; k< 28; k++)
		cout << str_array[k] << " ";
	cout << endl << endl;
	quickSort(str_array, 0, 27);
	cout << endl << "Printing sorted string array: " << endl;
	for (int k=0; k< 28; k++)
		cout << str_array[k] << " ";
	cout << endl << endl;

	return 0;
}

