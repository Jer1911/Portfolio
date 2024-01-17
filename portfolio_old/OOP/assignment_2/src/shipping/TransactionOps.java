package shipping;

import java.io.*;
import java.util.*;

/**
	A class to handle Transaction operations.
*/
public class TransactionOps
{
	/**
		Gets a date using Calendar.
		@param yy int year
		@param mm int month
		@param dd int day
		@return Calendar
	*/
	public static Calendar getDate(int yy, int mm, int dd)
	{
		mm -=1; // decrement month because it is zero-ordered.
		Calendar cal = new Calendar.Builder().setCalendarType("iso8601")
                        .setDate(yy, mm, dd).build();
		return cal;
	}

	public static void test()
	{				
		// create a test Transaction object:
		int cid = 1;
		String tn = "hhh33";

		int y1 = 2016;
		int m1 = 8;
		int d1 = 25;
		Calendar sd = getDate(y1, m1, d1);

		int y2 = 2017;
		int m2 = 10;
		int d2 = 1;
		Calendar dd = getDate(y2, m2, d2);

		double cs = 3.14;
		int eid = 1;

		Transaction tran = new Transaction(cid, tn, sd, dd, cs, eid);

		Output.printTransactionHeader();
		Output.printTransaction(tran);
	}

	/**
		Adds a new Transaction to the list.
		@param transactionList ArrayList of type Transaction
		@param userList ArrayList of type User
		@param packageList ArrayList of type Package
	*/
	public static void addTransaction(ArrayList<Transaction> transactionList,
		ArrayList<User> userList, ArrayList<Package> packageList)
	{
		boolean keepLooping = true;

		// prompt for customer id:
		System.out.print("Enter customer ID #: ");
		Scanner customerId = new Scanner(System.in);
		int cid = -1;
		while(keepLooping == true)
		{
			try
			{
				cid = customerId.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				customerId.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;

		// prompt for employee id:
		System.out.print("Enter employee ID #: ");
		Scanner employeeId = new Scanner(System.in);
		int eid = -1;
		while(keepLooping == true)
		{
			try
			{
				eid = employeeId.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				employeeId.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;

		// prompt for package tracking number:
		System.out.print("Enter package tracking #: ");
		Scanner tracking = new Scanner(System.in);
		String tn = "";
		while(keepLooping == true)
		{
			try
			{
				tn = tracking.nextLine();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				employeeId.nextLine();
				Output.printError();
				System.out.print("Invalid input. Try again: ");
			}
		}
		keepLooping = true;

		// prompt for shipping date:
		// get shipping year:
		System.out.println("Now please enter shipping date as integers, "
			+ "starting with the year:");
		Scanner year1 = new Scanner(System.in);
		int y1 = -1;
		while(keepLooping == true)
		{
			try
			{
				y1 = year1.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				year1.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;
		// get shipping month:
		System.out.print("Month: ");
		Scanner month1 = new Scanner(System.in);
		int m1 = -1;
		while(keepLooping == true)
		{
			try
			{
				m1 = month1.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				month1.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;
		// get shipping day:
		System.out.print("Day: ");
		Scanner day1 = new Scanner(System.in);
		int d1 = -1;
		while(keepLooping == true)
		{
			try
			{
				d1 = day1.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				day1.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;

		// prompt for delivery date:
		// get delivery year:
		System.out.println("Now please enter delivery date as integers, "
			+ "starting with the year:");
		Scanner year2 = new Scanner(System.in);
		int y2 = -1;
		while(keepLooping == true)
		{
			try
			{
				y2 = year2.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				year2.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;
		// get delivery month:
		System.out.print("Month: ");
		Scanner month2 = new Scanner(System.in);
		int m2 = -1;
		while(keepLooping == true)
		{
			try
			{
				m2 = month2.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				month2.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;
		// get delivery day:
		System.out.print("Day: ");
		Scanner day2 = new Scanner(System.in);
		int d2 = -1;
		while(keepLooping == true)
		{
			try
			{
				d2 = day2.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				day2.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}
		keepLooping = true;

		// check the date inputs:
		if(y1<0 || y2<0 || m1<0 || m2<0 || d1<0 || d2<0)
		{
			System.out.println("One or more date values was negative.");
			System.out.println("Returning to main menu.");
			return;
		}

		// construct date Calendar objects from the above information:
		Calendar sd = getDate(y1, m1, d1);
		Calendar dd = getDate(y2, m2, d2);

		// prompt for shipping cost:
		System.out.print("Enter shipping cost: ");
		Scanner cost =  new Scanner(System.in);
		double cs = 0;
		while(keepLooping == true)
		{
			try
			{
				cs = cost.nextDouble();
				keepLooping = false;
			}
			catch(InputMismatchException e)
			{
				cost.nextLine();
				Output.printError();
				System.out.print("That's not a float. Try again: ");
			}
		}

		// check the inputs:		
		boolean customerExists = customerCheck(userList, cid);
		boolean employeeExists = employeeCheck(userList, eid);
		boolean packageExists = packageCheck(packageList, tn);
		if(customerExists == true && employeeExists == true 
			&& packageExists == true)
		{
			// make a new transaction:
			Transaction tran = new Transaction(cid, tn, sd, dd, cs, eid);

			// add it to the list:
			transactionList.add(tran);

			// remove the relevant package:
			killPackage(packageList, tn);
		}
		else
		{
			System.out.println("Some input did not match the database. "
				+ "Please double check your information and "
				+ "try again later.");
			return;
		}
	} // end of addTransaction method.

	/**
		Checks to see if a customer id is valid.
		@param userList ArrayList of type User
		@param cid int
		@return boolean
	*/
	public static boolean customerCheck(ArrayList<User> userList, int cid)
	{
		// check that the customer id exists:
		ArrayList<Customer> customerList = UserOps.getCustomerList(userList);
		boolean customerExists = false;
		for(int k=0; k<customerList.size(); k++)
		{
			Customer cust = customerList.get(k);
			int i = Customer.getId(cust);
			if(i == cid)
			{
				System.out.println("Customer found!");
				customerExists = true;
			}
		}
		return customerExists;
	} // end of customerCheck method.

	/**
		Checks to see if an employee id is valid.
		@param userList ArrayList of type User
		@param eid int
		@return boolean
	*/
	public static boolean employeeCheck(ArrayList<User> userList, int eid)
	{
		// check that the employee id exists:
		ArrayList<Employee> employeeList = UserOps.getEmployeeList(userList);
		boolean employeeExists = false;
		for(int k=0; k<employeeList.size(); k++)
		{
			Employee emp = employeeList.get(k);
			int i = Employee.getId(emp);
			if(i == eid)
			{
				System.out.println("Employee found!");
				employeeExists = true;
			}
		}
		return employeeExists;
	} // end of employeeCheck method.

	/**
		Checks to see if a tracking number is valid.
		@param packageList ArrayList of type Package
		@param tn String
		@return boolean
	*/
	public static boolean packageCheck(ArrayList<Package> packageList, 
		String tn)
	{
		boolean found = false;
		for(int k=0; k<packageList.size(); k++)
		{
			Package pkg = packageList.get(k);
			String tracking = Package.getTrackingNumber(pkg);
			
			if(tracking.equals(tn))
			{
				System.out.println("Package found!");
				found = true;
			}
		}
		return found;
	} // end of packageCheck method.

	/**
		Removes the package from the list.
		@param packageList ArrayList of type Package
		@param tn String
	*/
	public static void killPackage(ArrayList<Package> packageList, String tn)
	{
		for(int k=0; k<packageList.size(); k++)
		{
			Package pkg = packageList.get(k);
			String tracking = Package.getTrackingNumber(pkg);
			if(tracking.equals(tn))
			{
				packageList.remove(k);
			}
		}
	}
}









