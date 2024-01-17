package shipping;

import java.io.*;
import java.util.*;
import java.text.*;

/**
	A class to handle displaying useful output for shipping and associated 
	classes.
*/
public class Output
{
	/***************************************************************************
	methods for printing Package things:
	***************************************************************************/

	/** Prints a header for Envelopes. */
	public static void printEnvelopeHeader()
	{
		// Make some useful strings for formatting:
		String tn = "| TRACKING # |";
		String s = " SPECIFICATION |";
		String c = " CLASS |";
		String h = " HEIGHT |";
		String w = " WIDTH |";

		// Print the header:
		printDashLine();
		System.out.println("ENVELOPES:");
		printDashLine();
		System.out.printf("%s%14s%18s%14s%18s\n",tn,s,c,h,w);
		printDashLine();
	}

	/**
		Prints an individual Envelope.
		@param env an Envelope object
	*/
	public static void printEnvelope(Envelope env)
	{
		String tn = Envelope.getTrackingNumber(env);
		String s = Envelope.getSpecification(env);
		String c = Envelope.getMailingClass(env);
		int h = Envelope.getHeight(env);
		int w = Envelope.getWidth(env);

		System.out.printf("|%11s |%14s |%16s |%12d |%16d |\n"
			,tn,s,c,h,w);
	}

	/**
		Prints formatted contents of an ArrayList of Envelopes.
		@param listIn ArrayList of type Envelope
	*/
	public static void printEnvelopeList(ArrayList<Envelope> listIn)
		{
			printEnvelopeHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Envelope env = listIn.get(k);
				printEnvelope(env);
			}
				printDashLine();
				System.out.println();
		}

	/** Prints a header for Boxes. */
	public static void printBoxHeader()
	{
		// Make some useful strings for formatting:
		String tn = "| TRACKING # |";
		String s = " SPECIFICATION |";
		String c = " CLASS |";
		String ld = " LARGEST DIMENSION |";
		String v = " VOLUME |";

		// Print the header:
		printDashLine();
		System.out.println("BOXES:");
		printDashLine();
		System.out.printf("%s%14s%18s%14s%12s\n",tn,s,c,ld,v);
		printDashLine();
	}

	/**
		Prints an individual Box.
		@param box a Box object
	*/
	public static void printBox(Box box)
	{
		String tn = Box.getTrackingNumber(box);
		String s = Box.getSpecification(box);
		String c = Box.getMailingClass(box);
		int ld = Box.getLargestDimension(box);
		int v = Box.getVolume(box);

		System.out.printf("|%11s |%14s |%16s |%18d |%10d |\n"
			,tn,s,c,ld,v);
	}

	/**
		Prints formatted contents of an ArrayList of Boxes.
		@param listIn ArrayList of type Box
	*/
	public static void printBoxList(ArrayList<Box> listIn)
		{
			printBoxHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Box box = listIn.get(k);
				printBox(box);
			}
				printDashLine();
				System.out.println();
		}

	/** Prints a header for Crates. */
	public static void printCrateHeader()
	{
		// Make some useful strings for formatting:
		String tn = "| TRACKING # |";
		String s = " SPECIFICATION |";
		String m = " CLASS |";
		String mlw = " MAX LOAD WEIGHT |";
		String c = " CONTENT |";

		// Print the header:
		printDashLine();
		System.out.println("CRATES:");
		printDashLine();
		System.out.printf("%s%14s%14s%14s%18s\n",tn,s,m,mlw,c);
		printDashLine();
	}

	/**
		Prints an individual Crate.
		@param crate a Crate object
	*/
	public static void printCrate(Crate crate)
	{
		String tn = Crate.getTrackingNumber(crate);
		String s = Crate.getSpecification(crate);
		String m = Crate.getMailingClass(crate);
		double mlw = Crate.getMaxLoadWeight(crate);
		String c = Crate.getContent(crate);

		System.out.printf("|%11s |%14s |%12s |%16.2f |%16s |\n"
			,tn,s,m,mlw,c);
	}

	/**
		Prints formatted contents of an ArrayList of Crates.
		@param listIn ArrayList of type Crate
	*/
	public static void printCrateList(ArrayList<Crate> listIn)
		{
			printCrateHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Crate crate = listIn.get(k);
				printCrate(crate);
			}
				printDashLine();
				System.out.println();
		}

	/** Prints a header for Drums. */
	public static void printDrumHeader()
	{
		// Make some useful strings for formatting:
		String tn = "| TRACKING # |";
		String s = " SPECIFICATION |";
		String m = " CLASS |";
		String mat = " MATERIAL |";
		String d = " DIAMETER |";

		// Print the header:
		printDashLine();
		System.out.println("DRUMS:");
		printDashLine();
		System.out.printf("%s%14s%14s%19s%17s\n",tn,s,m,mat,d);
		printDashLine();
	}

	/**
		Prints an individual Drum.
		@param drum a Drum object
	*/
	public static void printDrum(Drum drum)
	{
		String tn = Drum.getTrackingNumber(drum);
		String s = Drum.getSpecification(drum);
		String m = Drum.getMailingClass(drum);
		String mat = Drum.getMaterial(drum);
		Double d = Drum.getDiameter(drum);

		System.out.printf("|%11s |%14s |%12s |%16s |%16.2f |\n"
			,tn,s,m,mat,d);
	}

	/**
		Prints formatted contents of an ArrayList of Crates.
		@param listIn ArrayList of type Crate
	*/
	public static void printDrumList(ArrayList<Drum> listIn)
		{
			printDrumHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Drum drum = listIn.get(k);
				printDrum(drum);
			}
				printDashLine();
				System.out.println();
		}

	/***************************************************************************
	methods for printing User things:
	***************************************************************************/

	/** Prints a header for Employees. */
	public static void printEmployeeHeader()
	{
		// Make some useful strings for formatting:
		String id = "|  ID # |";
		String fn = "FIRST |";
		String ln = "LAST |";
		String ssn = "SSN |";
		String sal = "SALARY |";
		String acct = "ACCOUNT |";

		// Print the header:
		printDashLine();
		System.out.println("EMPLOYEES:");
		printDashLine();
		System.out.printf("%s%14s%14s%14s%14s%15s\n",id,fn,ln,ssn,sal,acct);
		printDashLine();
	}

	/** Prints a header for Customers. */
	public static void printCustomerHeader()
	{
		// Make some useful strings for formatting:
		String id = "|  ID # |";
		String fn = "FIRST |";
		String ln = "LAST |";
		String p = "PHONE |";
		String adr = "ADDRESS |";

		// Print the header:
		printDashLine();
		System.out.println("CUSTOMERS:");
		printDashLine();
		System.out.printf("%s%14s%14s%13s%30s\n",id,fn,ln,p,adr);
		printDashLine();
	}

	/**
		Prints an individual Employee.
		@param emp An Employee object
	*/
	public static void printEmployee(Employee emp)
	{
		int id = User.getId(emp);
		String fn = User.getFirstName(emp);
		String ln = User.getLastName(emp);
		int ssn = Employee.getSsn(emp);
		double sal = Employee.getSalary(emp);
		int acct = Employee.getAcctNum(emp);

		System.out.printf("|%6s |%12s |%12s |%12s |%12.2f |%13d |\n"
			,id,fn,ln,ssn,sal,acct);
	}

	/**
		Prints an individual Customer.
		@param cust A Customer object
	*/
	public static void printCustomer(Customer cust)
	{
		int id = User.getId(cust);
		String fn = User.getFirstName(cust);
		String ln = User.getLastName(cust);
		String p = Customer.getPhone(cust);
		String adr = Customer.getAddress(cust);

		System.out.printf("|%6s |%12s |%12s |%11s |%28s |\n"
			,id,fn,ln,p,adr);
	}

	/**
		Prints formatted contents of an ArrayList of Employees.
		@param listIn ArrayList of type Employees
	*/
	public static void printEmployeeList(ArrayList<Employee> listIn)
		{
			printEmployeeHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Employee emp = listIn.get(k);
				printEmployee(emp);
			}
				printDashLine();
				System.out.println();
		}

	/**
		Prints formatted contents of an ArrayList of Customers.
		@param listIn ArrayList of type Customer
	*/
	public static void printCustomerList(ArrayList<Customer> listIn)
		{
			printCustomerHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Customer cust = listIn.get(k);
				printCustomer(cust);
			}
				printDashLine();
				System.out.println();
		}

	/***************************************************************************
	methods for Transaction things:
	***************************************************************************/

	/**
		Prints a header for Transactions:
	*/
	public static void printTransactionHeader()
	{
		// Make some useful strings for formatting:
		String cid = "| CUST ID |";
		String tn = "TRACKING # |";
		String sd = " SHIPPING DATE |";
		String dd = " DELIVERY DATE |";
		String cs = " COST |";
		String eid = "EMP ID |";

		// Print the header:
		printDashLine();
		System.out.println("TRANSACTIONS:");
		printDashLine();
		System.out.printf("%s%14s%14s%13s%10s%13s\n",cid,tn,sd,dd,cs,eid);
		printDashLine();
	}

	/**
		Prints an individual Transaction.
		@param tran a Transaction object
	*/
	public static void printTransaction(Transaction tran)
	{
		int cid = Transaction.getCustomerId(tran);
		String tn = Transaction.getTrackingNumber(tran);

		DateFormat df = new SimpleDateFormat("MM-dd-yyyy");

		Calendar sd1 = Transaction.getShippingDate(tran);		
		Date sd2 = sd1.getTime();
		String sd = df.format(sd2);

		Calendar dd1 = Transaction.getDeliveryDate(tran);
		Date dd2 = dd1.getTime();
		String dd = df.format(dd2);

		double cs = Transaction.getCost(tran);
		int eid = Transaction.getEmployeeId(tran);

		System.out.printf("|%8d |%12s |%14s |%14s |%8.2f |%11d |\n"
			,cid,tn,sd,dd,cs,eid);
	}

	/**
		Prints a formatted list of Transactions.
		@param listIn ArrayList of type Transaction
	*/
	public static void printTransactionList(ArrayList<Transaction> listIn)
		{
			printTransactionHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Transaction tran = listIn.get(k);
				printTransaction(tran);
			}
				printDashLine();
				System.out.println();
		}

	/***************************************************************************
	generally useful methods:
	***************************************************************************/

	/** Prints an error message. */
	public static void printError()
	{
		System.out.println("\nError: Invalid input. "
			+ "Your incompetance has been reported to your supervisor.\n");
	}

	/** Prints a line of dashes. */
	public static void printDashLine()
	{
		String dash = "-";
		int n = 80; // a nice number of dashes for our purposes
		String dashLine = new String(new char[n]).replace("\0", dash);
		System.out.println(dashLine);
	}	

	/**
		Prints the main menu and returns a choice.
		@return int
	*/
	public static int showMenu()
	{
		Scanner sc = new Scanner(System.in);
		boolean keepLooping = true;
		int x = 0;
		while(keepLooping == true)
		{
			try
			{
				printDashLine();
				System.out.println("Please select from these options:\n");
				System.out.println("1 - Show all package records");
				System.out.println("2 - Add a new package record");
				System.out.println("3 - Delete a package record");
				System.out.println("4 - Search for a package");
				System.out.println("5 - Show all user records");
				System.out.println("6 - Add a new user to the database");
				System.out.println("7 - Update user info");
				System.out.println("8 - Complete a shipping transaction");
				System.out.println("9 - Show completed shipping transactions");
				System.out.println("10 - Save and exit");
				printDashLine();
		
				x = sc.nextInt();
				System.out.println();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				printError();
				sc.nextLine();
			}
		}
		return x;
	}	

}

