package sorting;

import java.util.*;
import java.util.concurrent.*;

/**
	Tests the parallel merge sort.
	@author Jeremy Ecker
*/
public class ParallelSortTester
{
    /**
	    Creates an array of the given length filled with random non-negative
		integers.
    	@param length number of elements in the array 
		@return a int[]
	*/
    public static int[] createRandomArray(int length) {
        int[] a = new int[length];
        Random rand = new Random(System.currentTimeMillis());
        for (int i = 0; i < length; i++)
		{
            a[i] = rand.nextInt(1000000);
        }
        return a;
    }

	/**
		Checks to see if the array is sorted.
		@param a int[]
		@return boolean value
	*/
    public static boolean isSorted(int[] a)
	{
        for (int i = 0; i<a.length-1; i++)
		{
            if (a[i] > a[i+1])
			{
                System.out.println(a[i]+" > "+a[i+1]);
                return false;
            }
        }
        return true;
    }

	/**
		Tests out the merge sorting with different numbers of
		threads up to the max for the system and shows how long each operation
		takes.
	*/
	public static void runParallelSortTester()
	{
		// see how many processors the system has:
		int procNum = Runtime.getRuntime().availableProcessors();
		System.out.printf("\nNumber of available processors: %d\n", procNum);

		// main loop:
		for(int k = 1; k<=procNum; k*=2)
		{
			// initialize variables:
			int size = 1000;
			int[] a;

			// initialize thread pool which uses k threads:
			ForkJoinPool p = new ForkJoinPool(k);

			// tell the user how many threads he/she is using:
			System.out.printf("\nUsing %d threads:\n\n", k);

			// sort some arrays:
			for(int i = 0; i<15; i++)
			{
				// make array:
				a = createRandomArray(size);

		        // start the timer:
    		    long startTime = System.currentTimeMillis();

				// create an object for sorting:
				ParallelMergeSorter pms = 
					new ParallelMergeSorter(a, 0, a.length-1);

				// invoke the object:
				p.invoke(pms);

				// end the timer:
    		    long endTime = System.currentTimeMillis();

				// make sure it actually got sorted:
		        if (!isSorted(a))
				{
		            throw new RuntimeException("not sorted afterward: "
						+ Arrays.toString(a));
		        }

				// display the results:
				System.out.printf("%8d elements: %8d ms\n", 
					size, endTime - startTime);

				// double the array size:
				size *= 2;
			} // end inner for loop.
		} // end outer for loop.
		System.out.println();
	} // end method: ParallelMergeSorter

	/**
		Main method. Calls the runParallelSortTester method.
	*/
	public static void main(String[] args)
	{
		runParallelSortTester();
	}

}

