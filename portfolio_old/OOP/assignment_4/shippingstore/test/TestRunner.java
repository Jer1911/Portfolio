package shippingstore;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

/**
	This class runs the ShippingStoreTest methods.

	@author Jeremy Ecker
*/
public class TestRunner
{
	public static void main(String[] args)
	{
		System.out.println("Initializing tests of ShippingStore class methods...");

		Result result = JUnitCore.runClasses(ShippingStoreTest.class);

		for (Failure failure : result.getFailures())
		{
			System.out.println(failure.toString());
		}

		if (result.wasSuccessful())
		{
			System.out.println("All tests finished successfully...");
		}
	}
}

