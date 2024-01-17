package shippingstore;

import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.AfterClass;
import org.hamcrest.*;
import static org.hamcrest.CoreMatchers.*;
import java.util.*;
import java.io.*;

/**
	Tests all methods of the class ShippingStore using JUnit framework and
	hamcrest matchers. There should not be any data file existing prior to use,
	in order to ensure accurate tests. Mock datafile will be automatically
	created and removed by the testing program.

	@author Jeremy Ecker
*/
public class ShippingStoreTest
{
	/**
		Cleans up after tests by deleting the data file.
	*/
	@AfterClass
	public static void cleanUp()
	{
		System.out.println("Cleaning up: removing data file...");
		File dataFile = new File("PackageOrderDB.txt");
		dataFile.delete();
	}

	/**
		Quiets output of addOrder so that it will be easier to see our
		more important output of tests.
		@param shippingstore ShippingStore object to be operated on
		@param tn String Tracking Number
		@param t String Type
		@param s String Specification
		@param m String Mailing Class
		@param w String Weight
		@param v String Volume
	*/
	public void quietAdd(ShippingStore shippingstore,String tn, String t, 
							String s, String m, String w, String v)
	{
		String result = null;
    	PrintStream originalOut = System.out;
	    try
		{
    	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
    	    PrintStream ps = new PrintStream(os);
    	    System.setOut(ps);
    	    shippingstore.addOrder(tn,t,s,m,w,v);
    	    ps.flush();
    	    result = os.toString();
		}
	    finally
		{
	        System.setOut(originalOut);
	    }
	}

	/**
		Tests ShippingStore constructor to see if a new file is created.
	*/
	@Test
	public void ShippingStoreTest() throws IOException
	{
		System.out.println("Testing constructor...");

		String result = null;
    	PrintStream originalOut = System.out;
   	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
   	    PrintStream ps = new PrintStream(os);
   	    System.setOut(ps);
		ShippingStore shippingstore = new ShippingStore();
   	    ps.flush();
   	    result = os.toString();
	    System.setOut(originalOut);

		File dataFile = new File("PackageOrderDB.txt");
		if(!dataFile.exists())
		{
			fail("Test failed - PackageOrderDB.txt was not created.");
		}
	}

	/**
		Tests getDataFile method. See if object is created.
	*/
	@Test
	public void getDataFileTest() throws IOException
	{
		System.out.println("Testing getDataFile...");

		String result = null;
    	PrintStream originalOut = System.out;
   	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
   	    PrintStream ps = new PrintStream(os);
   	    System.setOut(ps);
		ShippingStore shippingstore = new ShippingStore();
   	    ps.flush();
   	    result = os.toString();
	    System.setOut(originalOut);

   	    FileReader dataReader = new FileReader(shippingstore.getDataFile());
		assertNotNull("Test failed - dataReader object is null.",dataReader);
	}

	/**
		Tests addOrder method. First, see if an object is added by asserting
		if findPackageOrder returns a correct index value. Then test input 
		validation functionality by attempting to add objects with incorrect
		values (if objects are not added successfully, then input validation
		is working properly). For weight and volume, test NaN values. Weight
		will throw exception since input validation does not occur.
	*/
	@Test
	public void addOrderTest() throws IOException
	{
		System.out.println("Testing addOrder...");

		ShippingStore shippingstore = new ShippingStore();

		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		int po0 = shippingstore.findPackageOrder("GFR23");
		assertEquals(0, po0);

		quietAdd(shippingstore,"badnumber","Box","Books","Retail","9500.00","45");
		int po1 = shippingstore.findPackageOrder("badnumber");
		assertEquals(-1, po1);

		quietAdd(shippingstore,"AFK74","badtype","Books","Retail","9500.00","45");
		int po2 = shippingstore.findPackageOrder("AFK74");
		assertEquals(-1, po2);

		quietAdd(shippingstore,"GGP22","Box","badspec","Retail","9500.00","45");
		int po3 = shippingstore.findPackageOrder("GGP22");
		assertEquals(-1, po3);

		quietAdd(shippingstore,"AAR97","Box","Books","badclass","9500.00","45");
		int po4 = shippingstore.findPackageOrder("AAR97");
		assertEquals(-1, po4);

		quietAdd(shippingstore,"BB8WR","Box","Books","Retail","-62","45");
		int po5 = shippingstore.findPackageOrder("BB8WR");
		assertEquals(-1, po5);

		quietAdd(shippingstore,"ZED99","Box","Books","Retail","9500.00","-45");
		int po6 = shippingstore.findPackageOrder("ZED99");
		assertEquals(-1, po6);

		try
		{
			quietAdd(shippingstore,"ARP11","Box","Books","Retail","badweight","45");
		}
		catch (NumberFormatException nfe)
		{
			System.out.println("NumberFormatException found. Input validation"
				+ " needed for NaN inputs, for Weight in addOrder method.");
		}
		int po7 = shippingstore.findPackageOrder("ARP11");
		assertEquals(-1, po7);

		try
		{
			quietAdd(shippingstore,"WWF01","Box","Books","Retail","9500.00","badvolume");
		}
		catch (NumberFormatException nfe)
		{
			System.out.println("NumberFormatException found. Input validation"
				+ " needed for NaN inputs, for Volume in addOrder method.");
		}
		int po8 = shippingstore.findPackageOrder("WWF01");
		assertEquals(-1, po8);
	}

	/**
		Tests showPackageOrders method. Make sure output is as expected.
	*/
	@Test
	public void showPackageOrdersTest() throws IOException
	{
		System.out.println("Testing showPackageOrders...");

		ShippingStore shippingstore = new ShippingStore();

		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");

		String result = null;
    	PrintStream originalOut = System.out;
	    try
		{
    	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
    	    PrintStream ps = new PrintStream(os);
    	    System.setOut(ps);
    	    shippingstore.showPackageOrders();
    	    ps.flush();
    	    result = os.toString();
		}
	    finally
		{
	        System.setOut(originalOut);
	    }

		if(!result.contains(" -------------------------------------------------------------------------- ")
		|| !result.contains("| Tracking # | Type    | Specification | Class       | Weight(oz) | Volume |") || !result.contains("| GFR23      | Box     | Books         | Retail      | 9500.00    | 45     |"))
		{
			fail("incorrect output detected for showPackageOrders.");
		}
	}

	/**
		Tests showPackageOrdersRange method lower bound. Make sure that orders
		below the specified limit will not be displayed.
	*/
	@Test
	public void showPackageOrdersRangeLowTest() throws IOException
	{
		System.out.println("Testing showPackageOrdersRange lower bound...");

		ShippingStore shippingstore = new ShippingStore();

		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

		String result = null;
    	PrintStream originalOut = System.out;
	    try
		{
    	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
    	    PrintStream ps = new PrintStream(os);
    	    System.setOut(ps);
    	    shippingstore.showPackageOrdersRange(5000,10000);
    	    ps.flush();
    	    result = os.toString();
		}
	    finally
		{
	        System.setOut(originalOut);
	    }

		if(result.contains("6"))
		{
			fail("failed: lower bound exceeded for showPackageOrdersRange.");
		}
	}

	/**
		Tests showPackageOrdersRange method upper bound. Make sure that orders
		above the specified limit will not be displayed.
	*/
	@Test
	public void showPackageOrdersRangeUpTest() throws IOException
	{
		System.out.println("Testing showPackageOrdersRange upper bound...");

		ShippingStore shippingstore = new ShippingStore();
		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

		String result = null;
    	PrintStream originalOut = System.out;
	    try
		{
    	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
    	    PrintStream ps = new PrintStream(os);
    	    System.setOut(ps);
    	    shippingstore.showPackageOrdersRange(500,1000);
    	    ps.flush();
    	    result = os.toString();
		}
	    finally
		{
	        System.setOut(originalOut);
	    }

		if(result.contains("9"))
		{
			fail("failed: upper bound exceeded for showPackageOrdersRange.");
		}
	}

	/**
		Tests findPackageOrder method. Make sure that the correct index for a
		specified package is returned.
	*/
	@Test
	public void findPackageOrderTest() throws IOException
	{
		System.out.println("Testing findPackageOrder...");

		ShippingStore shippingstore = new ShippingStore();

		int tnDefault = shippingstore.findPackageOrder("543GQ");

		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

		int tn0 = shippingstore.findPackageOrder("GFR23");
		int tn1 = shippingstore.findPackageOrder("PTSD1");

		if(tnDefault != -1 || tn0 != 0 || tn1 != 1)
		{
			fail("failure: incorrect index detected");
		}
	}

	/**
		Tests searchPackageOrder method. If the returned result does not contain
		the correct tracking number, then the test fails.
	*/
	@Test
	public void searchPackageOrderTest() throws IOException
	{
		System.out.println("Testing searchPackageOrder...");
		ShippingStore shippingstore = new ShippingStore();
		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

		int tn0 = shippingstore.findPackageOrder("GFR23");
		int tn1 = shippingstore.findPackageOrder("PTSD1");

		String result = null;
    	PrintStream originalOut = System.out;
	    try
		{
    	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
    	    PrintStream ps = new PrintStream(os);
    	    System.setOut(ps);
    	    shippingstore.searchPackageOrder("GFR23");
    	    ps.flush();
    	    result = os.toString();
		}
	    finally
		{
	        System.setOut(originalOut);
	    }

		if(!result.contains("GFR23"))
		{
			fail("failure: improper output detected.");
		}
	}

	/**
		Tests removeOrder method. See if removing an order results in actual
		order removal. If the index prior to removal is different from the
		index after removal, then the operation was successful. Also make sure
		that after removal, the index is indeed -1.
	*/
	@Test
	public void removeOrderTest() throws IOException
	{
		System.out.println("Testing removeOrder...");
		ShippingStore shippingstore = new ShippingStore();
		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

		int tn1 = shippingstore.findPackageOrder("PTSD1");

				String result = null;
    	PrintStream originalOut = System.out;
   	    ByteArrayOutputStream os = new ByteArrayOutputStream(1000);
   	    PrintStream ps = new PrintStream(os);
   	    System.setOut(ps);
		shippingstore.removeOrder("PTSD1");
   	    ps.flush();
   	    result = os.toString();
	    System.setOut(originalOut);

		int tn2 = shippingstore.findPackageOrder("PTSD1");

		assertThat(tn2, not(equalTo(tn1)));
		assertEquals(-1, tn2);
	}

	/**
		Tests getPackageOrder method. Make sure that all fields are accurate
		after retrieving the object.
	*/
	@Test
	public void getPackageOrderTest() throws IOException
	{
		System.out.println("Testing getPackageOrder...");
		ShippingStore shippingstore = new ShippingStore();
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");
		int tn1 = shippingstore.findPackageOrder("PTSD1");

		PackageOrder pkgorder = shippingstore.getPackageOrder(tn1);
		String tn = pkgorder.getTrackingNumber();
		String t = pkgorder.getType();
		String s = pkgorder.getSpecification();
		String m = pkgorder.getMailingClass();
		float w = pkgorder.getWeight();
		int v = pkgorder.getVolume();

		assertThat(tn, is("PTSD1"));
		assertThat(t, is("Box"));
		assertThat(s, is("Books"));
		assertThat(m, is("Retail"));
		assertThat(w, is(600.0F));
		assertThat(v, is(45));
	}

	/**
		Tests read method. In order to read something, something must first be
		written. Hence, this also tests the flush method by proxy.
	*/
	@Test
	public void readTest() throws IOException
	{
		System.out.println("Testing read...");
		ShippingStore shippingstore = new ShippingStore();

		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

        PrintWriter pw = new PrintWriter("PackageOrderDB.txt");
        shippingstore.flush(pw);

		ShippingStore shippingstore2 = new ShippingStore();

        FileReader dataReader = new FileReader(shippingstore2.getDataFile());
        shippingstore2.read(dataReader);

		int po = shippingstore2.findPackageOrder("PTSD1");

		assertEquals(1, po);
	}

	/**
		Tests flush method. In order to test flush, the read method must be
		employed to verify that data was written to the file. This method is
		actually unneccessary, since the readTest method does exactly the same
		thing. However, this was included for completeness even though it is
		redundant. A better solution would be to test for exceptions, but the
		assignment said not to do this.
	*/
	@Test
	public void flushTest() throws IOException
	{
		System.out.println("Testing flush...");
		ShippingStore shippingstore = new ShippingStore();

		quietAdd(shippingstore,"GFR23","Box","Books","Retail","9500.00","45");
		quietAdd(shippingstore,"PTSD1","Box","Books","Retail","600.00","45");

        PrintWriter pw = new PrintWriter("PackageOrderDB.txt");
        shippingstore.flush(pw);

		ShippingStore shippingstore2 = new ShippingStore();

        FileReader dataReader = new FileReader(shippingstore2.getDataFile());
        shippingstore2.read(dataReader);

		int po = shippingstore2.findPackageOrder("PTSD1");

		assertEquals(1, po);
	}
}











