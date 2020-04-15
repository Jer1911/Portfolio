package Shipping;

import java.io.*;
import java.util.*;

/**
	A class to handle input and output operations for Package.
*/
public class InputOutput
{
    /**
        Reads the text file into an ArrayList of Packages.
		@return ArrayList of type Package
		@throws IOException - caught by calling method.
    */
	public static ArrayList<Package> readFile() throws IOException
    {
        FileReader fr = new FileReader("packages.txt");
        Scanner inFile = new Scanner(fr);
		ArrayList<Package> newList = new ArrayList<Package>();

		while(inFile.hasNextLine())
		{
	        String line = inFile.nextLine();
	        String[] words = line.split(" ");
	        String tn = words[0];
	        String t = words[1];
			String s = words[2];
			String m = words[3];
			double w = Double.parseDouble(words[4]);
	        int v = Integer.parseInt(words[5]);

			Package pkg = new Package(tn, t, s, m, w, v);
			newList.add(pkg);
		}
        inFile.close();
		return newList;
    }

	/**
		Creates a new text file if no file exists.
		@return ArrayList of type Package
		@throws IOException is caught within method
	*/
	public static ArrayList<Package> createFile() throws IOException
	{
		ArrayList<Package> newList = new ArrayList<Package>();
		try
		{
			newList = readFile();
		}
		catch (FileNotFoundException e)
		{
			try
			{
				System.out.println("File not found. Attempting to create one.");
				new File("packages.txt").createNewFile();
				System.out.println("File created. Initializing list.");
				newList = readFile();
			}
			catch (IOException ioe)
			{
				throw new RuntimeException("File creation failure. Check your"
							+ " permissions. Terminating program.");
			}
		}
		return newList;
	}

	/**
		Adds a new Package to the ArrayList.
		@param listIn ArrayList of type Package
	*/
	public static void addPackage(ArrayList<Package> listIn)
	{
		boolean keepLooping = true;

		printDashLine();

		// prompt user for a tracking number:
		System.out.print("Enter a 5-digit tracking number: ");
		Scanner trackingNumber = new Scanner(System.in);
		String tn = trackingNumber.nextLine();
		if(tn.length() != 5)
		{
			printError();
			return;
		}

		// prompt user for a type:
		System.out.print("Enter package type: ");
		Scanner type = new Scanner(System.in);
		String t = type.nextLine();
		if(!t.equals("Postcard") && !t.equals("Letter") && !t.equals("Envelope")
			&& !t.equals("Packet") && !t.equals("Box") && !t.equals("Crate") && 
			!t.equals("Drum") && !t.equals("Roll") && !t.equals("Tube"))
		{
			printError();
			System.out.println("Remember, valid package types are as follows:\n"
				+ "Postcard, Letter, Envelope, Packet, Box, Crate, Drum, Roll, "
				+ "Tube");
			return;
		}

		// prompt user for a specification:
		System.out.print("Enter package specification: ");
		Scanner specification = new Scanner(System.in);
		String s = specification.nextLine();
		if(!s.equals("Fragile") && !s.equals("Books") && !s.equals("Catalogs")
			&& !s.equals("Do-not-Bend") && !s.equals("N/A"))
		{
			printError();
			System.out.println("Remember, valid package specifications are as "
				+ "follows:\n"
				+ "Fragile, Books, Catalogs, Do-not-Bend, N/A");
			return;
		}

		// prompt user for a mailing class:
		System.out.print("Enter mailing class: ");
		Scanner mailingClass = new Scanner(System.in);
		String m = mailingClass.nextLine();
		if(!m.equals("First-Class") && !m.equals("Priority") && 
			!m.equals("Retail") && !m.equals("Ground") && !m.equals("Metro"))
		{
			printError();
			System.out.println("Remember, valid package classes are as follows:\n"
				+ "First-Class, Priority, Retail, Ground, Metro");
			return;
		}

		// prompt user for a weight:
		System.out.print("Enter weight: ");
		Scanner weight = new Scanner(System.in);
		double w = 0;
		while(keepLooping == true)
		{
			try
			{
				w = weight.nextDouble();
				keepLooping = false;				
			}
			catch (InputMismatchException e)
			{
				weight.nextLine();
				printError();
				System.out.print("That's not a float. Try again: ");
			}
		}

		// prompt user for a volume:
		System.out.print("Enter volume: ");
		Scanner volume = new Scanner(System.in);
		keepLooping = true;
		int v = 0;
		while(keepLooping == true)
		{
			try
			{
				v = volume.nextInt();
				keepLooping = false;
			}
			catch (InputMismatchException e)
				{
					volume.nextLine();
					printError();
					System.out.print("That's not an integer. Try again: ");
				}
		}

		// catch negative numbers in input:
		if(w < 0 || v < 0)
		{
			printError();
			System.out.println("One or more values was negative. Weight and "
				+ "volume cannot be negative.");
			return;
		}

		// create a new Package object and add it to the list:
		Package pkg = new Package(tn, t, s, m, w, v);
		listIn.add(pkg);
		System.out.println("\nNew record added.");
	}

	/**
		Search for a Package in the ArrayList.
		@param listIn ArrayList of type Package
		@param caller A String which tells the method who the caller was. If
		the caller was "removePackage", the private member variable
		findPackageHelper is changed to "true". This aids the method
		removePackage() so that it does not accidentally delete	the first
		ArrayList item.
		@return int representing the ArrayList index of the found package
	*/
	public static int findPackage(ArrayList<Package> listIn, String caller)
	{
		// prompt user for the tracking number:
		System.out.print("Enter an item tracking number: ");
		Scanner trackingNumber = new Scanner(System.in);
		String userString = trackingNumber.nextLine();
		System.out.print("Searching... ");

		boolean found = false;
		int j = 0;

		// search for the package:
		for(int k=0; k<listIn.size(); k++)
		{
			Package pkg = listIn.get(k);
			String tn = Package.getTrackingNumber(pkg);
			
			if(tn.equals(userString))
			{
				System.out.println("Package found!");
				found = true;
				j = k;
			}
		}

		if(found == true)
		{
			if(caller.equals("removePackage"))
			{
				/* Set private class variable findPackageHelper to true. This 
                   will prevent removePackage() from deleting the first record 
                   accidentally. */
				findPackageHelper = true;
			}
			else // default behavior:
			{
				// display the item:
				Package x = listIn.get(j);
				printHeader();
				printPackage(x);
				printDashLine();
				System.out.println();
			}
		}
		else
		{
			System.out.println("Sorry, I could not find that package.");
		}
		return j;
	}

	/**
		Removes a Package from the ArrayList.
		@param listIn ArrayList of type Package
	*/
	public static void removePackage(ArrayList<Package> listIn)
	{
		System.out.println("Which record do you want to delete?");
		String method = "removePackage";
		int x = findPackage(listIn, method);
		if(findPackageHelper == true) // If findPackage() reports package found:
		{
			System.out.print("Removing record... ");
			listIn.remove(x);
			System.out.println("Record removed.");
			findPackageHelper = false; // Reset variable to default state.
		}
		else
		{
			System.out.println("Unable to remove record.");
		}
	}

	/**
		Shows packages within a user-specified weight range.
		@param listIn ArrayList of type Package
		@throws InputMismatchException is caught within method.
	*/
	public static void listByWeight(ArrayList<Package> listIn) 
						throws InputMismatchException
	{
		boolean keepLooping = true;

		// get the minimum weight value:
		System.out.println("Enter minimum weight:");
		Scanner minWeight = new Scanner(System.in);
		double min = 0;
		while(keepLooping == true)
		{
			try
			{
				min = minWeight.nextDouble();
				keepLooping = false;
			}
			catch (InputMismatchException e)
			{
				minWeight.nextLine();
				printError();
				System.out.print("That's not a float. Try again: ");
			}
		}

		// get the maximum weight value:
		System.out.println("Enter maximum weight:");
		Scanner maxWeight = new Scanner(System.in);
		double max = 0;
		keepLooping = true;
		while(keepLooping == true)
		{
			try
			{
				max = maxWeight.nextDouble();
				keepLooping = false;
			}
			catch(InputMismatchException e)
			{
				maxWeight.nextLine();
				printError();
				System.out.print("That's not a float. Try again: ");
			}
		}

		// prevent negative weight values:
		if(min < 0 || max < 0) 
		{
			printError();
			System.out.println("One or more values was negative. "
				+ "A weight can't be negative?\n"
				+ "Exiting to main menu.");
			return;
		}

		// report input values:
		System.out.printf("Searching for packages weighing between ");
		System.out.printf("%.2f and %.2f oz...\n",min,max);

		// search value range:
		ArrayList<Package> weightList = new ArrayList<Package>();
		for(int k=0; k<listIn.size(); k++)
		{
			Package pkg = listIn.get(k);
			double weight = Package.getWeight(pkg);
			if(weight >= min && weight <= max)
			{
				weightList.add(pkg);
			}
		}

		// report results of search:
		System.out.println("Here is what I found:\n");
		printList(weightList);
	}

	/*-------------------------------------------------------------------------
	Methods for displaying various kinds of text on the screen:
	-------------------------------------------------------------------------*/

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

	/** Prints a header for Packages. */
	public static void printHeader()
	{
		// Make some useful strings for formatting:
		String tn = "| TRACKING # |";
		String t = "TYPE |";
		String s = "SPECIFICATION |";
		String c = "CLASS |";
		String w = "WEIGHT |";
		String v = "VOLUME |";

		// Print the header:
		printDashLine();
		System.out.printf("%s%12s%18s%14s%13s%9s\n",tn,t,s,c,w,v);
		printDashLine();
	}

	/**
		Prints an individual package.
		@param pkg A Package object
	*/
	public static void printPackage(Package pkg)
	{
		String tn = Package.getTrackingNumber(pkg);
		String t = Package.getType(pkg);
		String s = Package.getSpecification(pkg);
		String c = Package.getMailingClass(pkg);
		double w = Package.getWeight(pkg);
		int v = Package.getVolume(pkg);

		System.out.printf("|%11s |%10s |%16s |%12s |%11.2f |%7d |\n"
			,tn,t,s,c,w,v);
	}

	/**
		Prints formatted contents of an ArrayList of Packages.
		@param listIn ArrayList of type Package
	*/
	public static void printList(ArrayList<Package> listIn)
		{
			printHeader();
			for(int k=0; k<listIn.size(); k++)
			{
				Package pkg = listIn.get(k);
				printPackage(pkg);
			}
				printDashLine();
				System.out.println();
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
				System.out.println("2 - Add a new record to the database");
				System.out.println("3 - Delete a record from the database");
				System.out.println("4 - Search for a package using tracking "
									+ "number");
				System.out.println("5 - Show packages by a specified weight "
									+ "range");
				System.out.println("6 - Save and exit");
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

	/*-------------------------------------------------------------------------
	Method for writing to file:
	-------------------------------------------------------------------------*/

    /**
		Writes a new entry to the file.
		@param listIn ArrayList of type Package
		@throws IOException which is caught within method.
	*/
	public static void writeFile(ArrayList<Package> listIn) throws IOException
	{
		try
		{
			FileWriter fw = new FileWriter("packages.txt");
    	    PrintWriter outFile = new PrintWriter(fw);

			System.out.println("Saving changes...");

			for(int k=0; k<listIn.size(); k++)
			{
				Package pkg = listIn.get(k);

				String tn = Package.getTrackingNumber(pkg);
				String t = Package.getType(pkg);
				String s = Package.getSpecification(pkg);
				String m = Package.getMailingClass(pkg);
				double w = Package.getWeight(pkg);
				int v = Package.getVolume(pkg);

		        outFile.println(tn+" "+t+" "+s+" "+m+" "+w+" "+v);
			}

    	    outFile.flush();
    	    outFile.close();
		}
		catch (IOException ioe)
			{
				throw new RuntimeException("File write failure. Check your"
							+ " permissions. Terminating program.");
			}
	}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/
	private static boolean findPackageHelper = false;
} // End of class.

