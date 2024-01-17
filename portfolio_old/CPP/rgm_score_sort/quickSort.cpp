/*******************************************************************
* quickSort.cpp                                                    *
* Author: Jeremy Ecker                                             *
* Assignment: 7                                                    *
* COSC-2436 (Programming Fundamentals III: Data Structures, 18736) *
* Date: 4/3/2017                                                   *
*******************************************************************/

using namespace std;

const int MIN_SIZE = 4;

/** Sorts the first, middle, and last elements of an array (ascending order).
 @post  theArray's first, middle, and last elements are sorted.
 @param  theArray  The given array.
 @param  first, middle, last  The indeces of first, middle, and last elements. */

template <class ItemType>
void sortFirstMiddleLast(ItemType theArray[], int first, int middle, int last)
{
	if(theArray[first] > theArray[middle])
		swap(theArray[first], theArray[middle]);

	if(theArray[middle] > theArray[last])
		swap(theArray[middle], theArray[last]);

	if(theArray[first] > theArray[middle])
		swap(theArray[first], theArray[middle]);
} // end sortFirstMiddleLast.

/** Partitions an array using median-of-three method.
 @pre  At least four entries are required.
 @post  Pivot entry is placed in its correct sorted position.
 @param  theArray  The given array.
 @param  first, last  The indeces of first and last elements. */

template <class ItemType>
int partition(ItemType theArray[], int first, int last)
{
    // Choose pivot and reposition it:
	int middle = first + (last - first) / 2;
    sortFirstMiddleLast(theArray, first, middle, last);
	swap(theArray[middle], theArray[last-1]);
	int pivotIndex = last-1;
	ItemType pivot = theArray[pivotIndex];

    // Determine regions S1 and S2:
	int indexFromLeft = first+1;
	int indexFromRight = last-2;

	bool done = false;
	while(!done)
	{
        // Locate first entry on left that is >= pivot:
		while(theArray[indexFromLeft] < pivot)
			indexFromLeft = indexFromLeft + 1;
        // Locate first entry on right that is <= pivot:
		while(theArray[indexFromRight] > pivot)
			indexFromRight = indexFromRight - 1;

		if(indexFromLeft < indexFromRight)
		{
			swap(theArray[indexFromLeft], theArray[indexFromRight]);
			indexFromLeft = indexFromLeft + 1;
			indexFromRight = indexFromRight - 1;
		}
		else
			done = true;
	}
    // Place pivot in proper position between S1 and S2, and mark its new location:
	swap(theArray[pivotIndex], theArray[indexFromLeft]);
	pivotIndex = indexFromLeft;

	return pivotIndex;
} // end partition.

//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 11-5. (Modified to print sizes.)

/** Sorts an array into ascending order. Uses the quick sort with
    median-of-three pivot selection for arrays of at least MIN_SIZE
    entries, and uses the insertion sort for other arrays.
 @pre  theArray[first..last] is an array.
 @post  theArray[first..last] is sorted.
 @param theArray  The given array.
 @param first  The index of the first element to consider in theArray.
 @param last  The index of the last element to consider in theArray. */

template <class ItemType>
void quickSort(ItemType theArray[], int first, int last)
{
    if ((last - first + 1) < MIN_SIZE)
	{
		int size = last - first + 1;
		cout << "Calling insertionSort with size = " << size << endl;
        insertionSort(theArray, first, last);
    }
    else
    {
        // Create the partition: S1 | Pivot | S2
        int pivotIndex = partition(theArray, first, last);
        // Print partition sizes:
		int left_size = pivotIndex - first;
        int right_size = last - pivotIndex;
		cout << "Calling quickSort with left size = " << left_size;
        cout << " and right size = " << right_size << endl;
        // Sort subarrays S1 and S2:
        quickSort(theArray, first, pivotIndex - 1);
        quickSort(theArray, pivotIndex + 1, last);
    }
} // end quickSort.

