package shipping;

import java.util.*;
import java.io.*;

/**
    A class to handle User operations.
*/
public class UserOps
{
	/**
		Adds a new User to the ArrayList.
		@param listIn ArrayList of type User
	*/
    public static void addUser(ArrayList<User> listIn)
    {
		boolean keepLooping = true;
		Output.printDashLine();
		
		// prompt user for a type:
		System.out.print("Enter user type: ");
		Scanner type = new Scanner(System.in);
		String t = type.nextLine();

		// check validity of type:
		if(!t.equals("Employee") && !t.equals("Customer"))
		{
			Output.printError();
			System.out.println("Remember, valid user types are as follows:\n"
				+ "Employee, Customer");
			return;
		}

		// all Users get id and names:

		// generate user ID:
		int userId = 1; // the very first employee ever added will be #1
		if(listIn.size() > 0) // otherwise other employees exist
		{
			for(int k=0; k<listIn.size(); k++)
			{
				User emp = listIn.get(k);
				int lastId = User.getId(emp);
				userId = lastId + 1; // so make sure the ID number will be ok.
			}
		}
		System.out.println("New user's ID# is: " + userId);

		// prompt for first name:
		System.out.print("Enter first name: ");
		Scanner firstName = new Scanner(System.in);
		String fn = firstName.nextLine();

		// prompt for last name:
		System.out.print("Enter last name: ");
		Scanner lastName = new Scanner(System.in);
		String ln = lastName.nextLine();

		// Employees get ssn, salary, and bank account info:
		if(t.equals("Employee"))
		{
			// prompt for social security number:
			System.out.print("Enter social security number: ");
			Scanner social = new Scanner(System.in);
			int s = 0;
			while(keepLooping == true)
			{
				try
				{
					s = social.nextInt();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					social.nextLine();
					Output.printError();
					System.out.print("That's not an integer. Try again: ");
				}
			}

			// prompt for monthly salary:
			System.out.print("Enter monthly salary: ");
			Scanner salary = new Scanner(System.in);
			double sal = 0;
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					sal = salary.nextDouble();
					keepLooping = false;				
				}
				catch (InputMismatchException e)
				{
					salary.nextLine();
					Output.printError();
					System.out.print("That's not a float. Try again: ");
				}
			}

			// prompt for direct deposit bank account number:
			System.out.print("Enter bank account number for direct deposit: ");
			Scanner acctNum = new Scanner(System.in);
			int acct = 0;
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					acct = acctNum.nextInt();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					acctNum.nextLine();
					Output.printError();
					System.out.print("That's not an integer. Try again: ");
				}
			}

			// catch negative numbers in input:
			if(userId < 0 || s < 0 || sal < 0 || acct < 0)
			{
				Output.printError();
				System.out.println("One or more values was negative. "
					+"That won't work.");
				return;
			}

			// create a new Employee and add it to the list:
			Employee emp = new Employee(userId, ln, fn, s, sal, acct);
			listIn.add(emp);
			System.out.println("New record added.");

		} // end of employee specific adder.

		// Customers get phone and address:
		if(t.equals("Customer"))
		{
			// prompt for phone #:
			System.out.print("Enter phone number: ");
			Scanner phone = new Scanner(System.in);
			String pn = phone.nextLine();
			
			// prompt for address:
			System.out.print("Enter address: ");
			Scanner address = new Scanner(System.in);
			String adr = address.nextLine();
			
			// create a new Customer and add it to the list:
			Customer cust = new Customer(userId, ln, fn, pn, adr);
			listIn.add(cust);
			System.out.println("New record added.");
		}
    } // end addUser method.

	/** Call the appropriate print methods for each type of User.
		@param listIn ArrayList of type User
	*/
	public static void printUserList(ArrayList<User> listIn)
	{
		ArrayList<Employee> empList = getEmployeeList(listIn);
		ArrayList<Customer> cusList = getCustomerList(listIn);
		Output.printEmployeeList(empList);
		Output.printCustomerList(cusList);
	}

	/** Get a list of Employees.
		@param listIn ArrayList of type User
		@return ArrayList
	*/
	public static ArrayList<Employee> getEmployeeList(ArrayList<User> listIn)
	{
		// get Employee list:
		ArrayList<Employee> empList = new ArrayList<Employee>();
		for (Object o : listIn) 
		{
		    if (o instanceof Employee)
			{
		        empList.add((Employee)o);
		    }
		}
		return empList;
	}

	/** Get a list of Customers.
		@param listIn ArrayList of type User
		@return ArrayList
	*/
	public static ArrayList<Customer> getCustomerList(ArrayList<User> listIn)
	{
		// get Customer list:
		ArrayList<Customer> custList = new ArrayList<Customer>();
		for (Object o : listIn) 
		{
		    if (o instanceof Customer)
			{
		        custList.add((Customer)o);
		    }
		}
		return custList;
	}

	/**
		Search for a user by ID#.
		@param listIn ArrayList of type User
		@return index int
	*/
	public static int findUser(ArrayList<User> listIn) throws InputMismatchException
	{
		// prompt user for the id#:
		System.out.print("Enter the user ID# : ");
		Scanner idNum = new Scanner(System.in);
		boolean keepLooping = true;
		int id = 0;
		int index = -1;
		boolean found = false;

		// make sure id# is possible:
		while(keepLooping == true)
		{
			try
			{
				id = idNum.nextInt();
				System.out.print("Searching... ");
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				idNum.nextLine();
				Output.printError();
				System.out.print("That's not an integer. Try again: ");
			}
		}

		// search for the user:
		for(int k=0; k<listIn.size(); k++)
		{
			User usr = listIn.get(k);
			int i = User.getId(usr);
			if(i == id)
			{
				System.out.println("User found!");
				found = true;
				index = k;
			}
		}

		// if user was found, print it:
		if(found == true)
		{
			User usr = listIn.get(index);
			if(usr instanceof Employee)
			{
				Employee emp = (Employee)listIn.get(index);
				Output.printEmployeeHeader();
				Output.printEmployee(emp);
				Output.printDashLine();
				System.out.println();
			}
			else if(usr instanceof Customer)
			{
				Customer cus = (Customer)listIn.get(index);
				Output.printCustomerHeader();
				Output.printCustomer(cus);
				Output.printDashLine();
				System.out.println();
			}
		}
		else
		{
			System.out.println("Sorry, I could not find that user.");
		}

		return index;
	}

	/**
		Update a User's info.
		@param listIn ArrayList of type User
	*/
	public static void updateUser(ArrayList<User> listIn)
	{
		int i = findUser(listIn);
		boolean keepLooping = true;

		try
		{
			Object o = listIn.get(i);

		    if (o instanceof Employee)
			{
				// get the employee's current data:
				Employee emp = (Employee)listIn.get(i); // YOU HAVE TO CAST IT!
				int id = Employee.getId(emp);
				String ln = Employee.getLastName(emp);
				String fn = Employee.getFirstName(emp);
				int ssn = Employee.getSsn(emp);
				double sal = Employee.getSalary(emp);
				int acct = Employee.getAcctNum(emp);
				System.out.printf("current data is: %d %s %s %d %f %d\n"
					,id, ln, fn, ssn, sal, acct);

		        System.out.println("Which field do you want to update?");
				System.out.println("1 - Social security number");
				System.out.println("2 - Monthly salary");
				System.out.println("3 - Direct deposit account");
				System.out.println("4 - First name");
				System.out.println("5 - Last name");
				Scanner choice = new Scanner(System.in);
				String x = choice.nextLine();
	
				if(x.equals("1"))
				{
					// prompt for social security number:
					System.out.print("Enter social security number: ");
					Scanner social = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							ssn = social.nextInt();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							social.nextLine();
							Output.printError();
							System.out.print("Not an integer. Try again: ");
						}
					}
					// update the employee with new ssn:
					Employee newEmp = new Employee(id,ln,fn,ssn,sal,acct);
					listIn.set(i, newEmp);
					System.out.println("Record changed.");
				}
				else if(x.equals("2"))
				{
					// prompt for salary:
					System.out.print("Enter new salary: ");
					Scanner salary = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							sal = salary.nextDouble();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							salary.nextLine();
							Output.printError();
							System.out.print("Not a double. Try again: ");
						}
					}
					// update the employee with new salary:
					Employee newEmp = new Employee(id,ln,fn,ssn,sal,acct);
					listIn.set(i, newEmp);
					System.out.println("Record changed.");
				}
				else if(x.equals("3"))
				{
					// prompt for account #:
					System.out.print("Enter new account number: ");
					Scanner account = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							acct = account.nextInt();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							account.nextLine();
							Output.printError();
							System.out.print("Not an integer. Try again: ");
						}
					}
					// update the employee with new account:
					Employee newEmp = new Employee(id,ln,fn,ssn,sal,acct);
					listIn.set(i, newEmp);
					System.out.println("Record changed.");
				}
				else if(x.equals("4"))
				{
					// prompt for first name:
					System.out.print("Enter new first name: ");
					Scanner firstName = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							fn = firstName.nextLine();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							firstName.nextLine();
							Output.printError();
							System.out.print("Incorrect input. Try again: ");
						}
					}
					// update the employee with new account:
					Employee newEmp = new Employee(id,ln,fn,ssn,sal,acct);
					listIn.set(i, newEmp);
					System.out.println("Record changed.");
				}
				else if(x.equals("5"))
				{
					// prompt for last name:
					System.out.print("Enter new last name: ");
					Scanner lastName = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							ln = lastName.nextLine();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							lastName.nextLine();
							Output.printError();
							System.out.print("Incorrect input. Try again: ");
						}
					}
					// update the employee with new account:
					Employee newEmp = new Employee(id,ln,fn,ssn,sal,acct);
					listIn.set(i, newEmp);
					System.out.println("Record changed.");
				}
		    }
			else if (o instanceof Customer)
			{
	        
				// get the employee's current data:
				Customer cus = (Customer)listIn.get(i); // YOU HAVE TO CAST IT!
				int id = Customer.getId(cus);
				String ln = Customer.getLastName(cus);
				String fn = Customer.getFirstName(cus);
				String pn = Customer.getPhone(cus);
				String adr = Customer.getAddress(cus);
				System.out.printf("current data is: %d %s %s %s %s\n"
					,id, ln, fn, pn, adr);

		        System.out.println("Which field do you want to update?");
				System.out.println("1 - First name");
				System.out.println("2 - Last name");
				System.out.println("3 - Phone number");
				System.out.println("4 - Address");
				Scanner choice = new Scanner(System.in);
				String x = choice.nextLine();

				if(x.equals("1"))
				{
					// prompt for first name:
					System.out.print("Enter new first name: ");
					Scanner firstName = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							fn = firstName.nextLine();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							firstName.nextLine();
							Output.printError();
							System.out.print("Incorrect input. Try again: ");
						}
					}
					// update the customer with new first name:
					Customer newCus = new Customer(id,ln,fn,pn,adr);
					listIn.set(i, newCus);
					System.out.println("Record changed.");
				}
				else if(x.equals("2"))
				{
					// prompt for last name:
					System.out.print("Enter new last name: ");
					Scanner lastName = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							ln = lastName.nextLine();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							lastName.nextLine();
							Output.printError();
							System.out.print("Incorrect input. Try again: ");
						}
					}
					// update the customer with new last name:
					Customer newCus = new Customer(id,ln,fn,pn,adr);
					listIn.set(i, newCus);
					System.out.println("Record changed.");
				}
				else if(x.equals("3"))
				{
					// prompt for phone number:
					System.out.print("Enter new phone number: ");
					Scanner phone = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							pn = phone.nextLine();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							phone.nextLine();
							Output.printError();
							System.out.print("Incorrect input. Try again: ");
						}
					}
					// update the customer with new phone number:
					Customer newCus = new Customer(id,ln,fn,pn,adr);
					listIn.set(i, newCus);
					System.out.println("Record changed.");
				}
				else if(x.equals("4"))
				{
					// prompt for address:
					System.out.print("Enter new address: ");
					Scanner address = new Scanner(System.in);
					while(keepLooping == true)
					{
						try
						{
							adr = address.nextLine();
							keepLooping = false;
						}
						catch (InputMismatchException e)
						{
							address.nextLine();
							Output.printError();
							System.out.print("Incorrect input. Try again: ");
						}
					}
					// update the customer with new address:
					Customer newCus = new Customer(id,ln,fn,pn,adr);
					listIn.set(i, newCus);
					System.out.println("Record changed.");
				}
		    }
		}
		catch (IndexOutOfBoundsException e)
		{
			Output.printError();
			System.out.println("That's not a user I know of.");
			return;
		}
	} // end method updateUser.
} // end of class










