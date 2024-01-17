package sorting;

import java.util.*;
import java.util.concurrent.*;

/**
	Parallel merge sort class. Extends RecursiveAction (which extends 
	ForkJoinTask in java.util.concurrent). This is most efficient for our
	purpose here. (Although merge by itself is not the most efficient sort,
	depending on circumstances. It may actually be more efficient to use the
	Arrays.sort functionality, but that would defeat the purpose of the
	assignment...)
	@author Jeremy Ecker
*/
public class ParallelMergeSorter extends RecursiveAction
{
	/**
		Default constructor (empty).
	*/
	public ParallelMergeSorter()
	{}

	/**
		Parameterized constructor. Used for making sort objects.
		@param array int[]
		@param left int
		@param right int
	*/
	public ParallelMergeSorter(int[] array, int left, int right)
	{
		setArray(array);
		setLeft(left);
		setRight(right);	
	}

	/***************************************************************************
	*                        Protected methods:                                *
	***************************************************************************/

    /**
		Overrides the compute method of superclass RecursiveAction.
		Computes the midpoint of the array, creates threads to sort the
		array halves, and invokes parallelMerge to put the array back together
		in order.
    */
    @Override
    protected void compute()
	{
        if (l<r)
		{
            int m = (l+r)/2;
            RecursiveAction lSort = new ParallelMergeSorter(arr, l, m);
            RecursiveAction rSort = new ParallelMergeSorter(arr, m+1, r);
            invokeAll(lSort, rSort);
            parallelMerge(l, m, r);
        }
    }

	/***************************************************************************
	*                        Private methods:                                  *
	***************************************************************************/

	/**
		Merges the array back together in order.
		@param left int
		@param right int
	*/
	private void parallelMerge(int left, int middle, int right)
	{
		// Create a temporary local array and initialize local variables:
	    int localArray[] = new int[right-left+1];
        int i = left; // Next element to consider in the first range
        int j = middle+1; // Next element to consider in the second range
        int k = 0; // Next open position in localArray

		// As long as not past the end, move the smaller into localArray:
        while (i <= middle && j <= right)
		{
            if (arr[i] <= arr[j])
			{
                localArray[k] = arr[i];
                k++;
                i++;
            }
			else
			{
                localArray[k] = arr[j];
                k++;
                j++;
            }
        }

		// Note that only one of the two while loops below is executed:

        // Copy any remaining entries of the first half:
        while (j <= right)
		{
            localArray[k++] = arr[j++];
        }

		// Copy any remaining entries of the second half:
        while (i <= middle)
		{
            localArray[k++] = arr[i++];
        }

		// Copy back from the temporary array:
        for (k = 0; k < localArray.length; k++)
		{
            arr[left + k] = localArray[k];
        }	
	} // end of method: parallelMerge

	/**
		Sets the arr variable.
		@param array int[]
	*/
	private void setArray(int[] array)
	{
		arr = array;
	}

	/**
		Sets the left variable.
		@param left int
	*/
	private void setLeft(int left)
	{
		l = left;
	}

	/**
		Sets the right variable.
		@param right int
	*/
	private void setRight(int right)
	{
		r = right;
	}

	/***************************************************************************
	*                        Private member variables:                         *
	***************************************************************************/
	private int l; // left part of array
	private int r; // right part of array
	private int arr[]; // array
}

