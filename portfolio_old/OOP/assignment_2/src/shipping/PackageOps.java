package shipping;

import java.io.*;
import java.util.*;

/**
	A class to handle Package operations.
*/
public class PackageOps
{
	/**
		Sorts an ArrayList of Packages by tracking number.
		@param listIn Arraylist of type Package
	*/
	public static void sortPackageList(ArrayList<Package> listIn)
	{
		Collections.sort(listIn);
	}

	/**
		Adds a new Package to the ArrayList.
		@param listIn ArrayList of type Package
	*/
	public static void addPackage(ArrayList<Package> listIn)
	{
		boolean keepLooping = true;

		Output.printDashLine();

		// prompt user for a type:
		System.out.print("Enter package type: ");
		Scanner type = new Scanner(System.in);
		String t = type.nextLine();
		if(!t.equals("Envelope") && !t.equals("Box") && 
			!t.equals("Crate") && !t.equals("Drum"))
		{
			Output.printError();
			System.out.println("Remember, valid package types are as follows:\n"
				+ "Envelope, Box, Crate, Drum,");
			return;
		}

		// all Packages get tracking number, specification, and mailing class:

		// prompt user for a tracking number:
		System.out.print("Enter a 5-digit tracking number: ");
		Scanner trackingNumber = new Scanner(System.in);
		String tn = trackingNumber.nextLine();
		if(tn.length() != 5)
		{
			Output.printError();
			return;
		}

		// prompt user for a specification:
		System.out.print("Enter package specification: ");
		Scanner specification = new Scanner(System.in);
		String s = specification.nextLine();
		if(!s.equals("Fragile") && !s.equals("Books") && !s.equals("Catalogs")
			&& !s.equals("Do-not-Bend") && !s.equals("N/A"))
		{
			Output.printError();
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
			Output.printError();
			System.out.println("Remember, valid package classes are as follows:"
				+ "\nFirst-Class, Priority, Retail, Ground, Metro");
			return;
		}

		// Envelopes get height and width:
		if(t.equals("Envelope"))
		{
			// prompt for height:
			System.out.print("Enter envelope height: ");
			Scanner height = new Scanner(System.in);
			int h = 0;
			while(keepLooping == true)
			{
				try
				{
					h = height.nextInt();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					height.nextLine();
					Output.printError();
					System.out.print("That's not an integer. Try again: ");
				}
			}
			// prompt for width:
			System.out.print("Enter envelope width: ");
			Scanner width = new Scanner(System.in);
			int w = 0;
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					w = width.nextInt();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					width.nextLine();
					Output.printError();
					System.out.print("That's not an integer. Try again: ");
				}
			}
			// catch negative numbers in input:
			if(h < 0 || w < 0)
			{
				Output.printError();
				System.out.println("One or more values was negative. "
					+ " That won't work.");
				return;
			}
			// create a new Envelope object and add it to the list:
			Envelope env = new Envelope(tn, s, m, h, w);
			listIn.add(env);
			System.out.println("\nNew record added.");
		} // end of Envelope specific adder.

		// Boxes get largest dimension and volume:
		else if(t.equals("Box"))
		{
			// prompt for largest dimension:
			System.out.print("Enter largest dimension: ");
			Scanner largestDimension = new Scanner(System.in);
			int ld = 0;
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					ld = largestDimension.nextInt();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					largestDimension.nextLine();
					Output.printError();
					System.out.print("That's not an integer. Try again: ");
				}
			}
			// prompt for volume:
			System.out.print("Enter box volume: ");
			Scanner volume = new Scanner(System.in);
			int v = 0;
			keepLooping = true;
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
					Output.printError();
					System.out.print("That's not an integer. Try again: ");
				}
			}
			// catch negative numbers in input:
			if(ld < 0 || v < 0)
			{
				Output.printError();
				System.out.println("One or more values was negative. "
					+ " That won't work.");
				return;
			}
			// create a new Box object and add it to the list:
			Box box = new Box(tn, s, m, ld, v);
			listIn.add(box);
			System.out.println("\nNew record added.");
		} // end of Box specific adder.

		// Crates get max load weight and content:
		else if(t.equals("Crate"))
		{
			// prompt for max load weight:
			System.out.print("Enter maximum load weight: ");
			Scanner maxLoadWeight = new Scanner(System.in);
			double mlw = 0;
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					mlw = maxLoadWeight.nextDouble();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					maxLoadWeight.nextLine();
					Output.printError();
					System.out.print("That's not a float. Try again: ");
				}
			}
			// prompt for content:
			System.out.print("Enter crate content: ");
			Scanner content = new Scanner(System.in);
			String c = "";
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					c = content.nextLine();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					content.nextLine();
					Output.printError();
					System.out.print("Bad input. Try again: ");
				}
			}
			// catch negative numbers in input:
			if(mlw < 0)
			{
				Output.printError();
				System.out.println("One or more values was negative. "
					+ " That won't work.");
				return;
			}
			// create a new Crate object and add it to the list:
			Crate crate = new Crate(tn, s, m, mlw, c);
			listIn.add(crate);
			System.out.println("\nNew record added.");
		} // end of Crate specific adder.

		// Drums get diameter and material:
		else if(t.equals("Drum"))
		{
			// prompt for diameter:
			System.out.print("Enter diameter: ");
			Scanner diameter = new Scanner(System.in);
			double d = 0;
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					d = diameter.nextDouble();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					diameter.nextLine();
					Output.printError();
					System.out.print("That's not a float. Try again: ");
				}
			}
			// prompt for material:
			System.out.print("Enter drum material: ");
			Scanner material = new Scanner(System.in);
			String mat = "";
			keepLooping = true;
			while(keepLooping == true)
			{
				try
				{
					mat = material.nextLine();
					keepLooping = false;
				}
				catch (InputMismatchException e)
				{
					material.nextLine();
					Output.printError();
					System.out.print("Bad input. Try again: ");
				}
			}
			// catch negative numbers in input:
			if(d < 0)
			{
				Output.printError();
				System.out.println("One or more values was negative. "
					+ " That won't work.");
				return;
			}
			// create a new Drum object and add it to the list:
			Drum drum = new Drum(tn, s, m, mat, d);
			listIn.add(drum);
			System.out.println("\nNew record added.");
		} // end of Crate specific adder.
	} // end of addPackage method.

	/** Call the appropriate print methods for each type of Package.
		@param listIn ArrayList of type Package
	*/
	public static void printPackageList(ArrayList<Package> listIn)
	{
		ArrayList<Envelope> envList = getEnvelopeList(listIn);
		Output.printEnvelopeList(envList);
		ArrayList<Box> boxList = getBoxList(listIn);
		Output.printBoxList(boxList);
		ArrayList<Crate> crateList = getCrateList(listIn);
		Output.printCrateList(crateList);
		ArrayList<Drum> drumList = getDrumList(listIn);
		Output.printDrumList(drumList);
	}

	/** Get a list of Drums.
		@param listIn ArrayList of type Package
		@return drumList ArrayList of type Drum
	*/
	public static ArrayList<Drum> getDrumList(ArrayList<Package>
					listIn)
	{
		// get Drum list:
		ArrayList<Drum> drumList = new ArrayList<Drum>();
		for (Object o : listIn) 
		{
		    if (o instanceof Drum)
			{
		        drumList.add((Drum)o);
		    }
		}
		return drumList;
	}

	/** Get a list of Crates.
		@param listIn ArrayList of type Package
		@return crateList ArrayList of type Crate
	*/
	public static ArrayList<Crate> getCrateList(ArrayList<Package>
					listIn)
	{
		// get Crate list:
		ArrayList<Crate> crateList = new ArrayList<Crate>();
		for (Object o : listIn) 
		{
		    if (o instanceof Crate)
			{
		        crateList.add((Crate)o);
		    }
		}
		return crateList;
	}

	/** Get a list of Boxes.
		@param listIn ArrayList of type Package
		@return envList ArrayList of type Box
	*/
	public static ArrayList<Box> getBoxList(ArrayList<Package>
					listIn)
	{
		// get Box list:
		ArrayList<Box> boxList = new ArrayList<Box>();
		for (Object o : listIn) 
		{
		    if (o instanceof Box)
			{
		        boxList.add((Box)o);
		    }
		}
		return boxList;
	}

	/** Get a list of Envelopes.
		@param listIn ArrayList of type Package
		@return envList ArrayList of type Envelope
	*/
	public static ArrayList<Envelope> getEnvelopeList(ArrayList<Package>
					listIn)
	{
		// get Envelope list:
		ArrayList<Envelope> envList = new ArrayList<Envelope>();
		for (Object o : listIn) 
		{
		    if (o instanceof Envelope)
			{
		        envList.add((Envelope)o);
		    }
		}
		return envList;
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
				// Set private class variable findPackageHelper to true. This 
                //   will prevent removePackage() from deleting the first record 
                //   accidentally. 
				findPackageHelper = true;
			}
			else // default behavior:
			{
				Package x = listIn.get(j);
				// print the correct type of header and item:
				if(x instanceof Envelope)
				{
					Envelope env = (Envelope)listIn.get(j); // CAST IT!
					Output.printEnvelopeHeader();
					Output.printEnvelope(env);
					Output.printDashLine();
					System.out.println();
				}
				else if(x instanceof Box)
				{
					Box box = (Box)listIn.get(j); // CAST IT!
					Output.printBoxHeader();
					Output.printBox(box);
					Output.printDashLine();
					System.out.println();
				}
				else if(x instanceof Crate)
				{
					Crate crate = (Crate)listIn.get(j); // CAST IT!
					Output.printCrateHeader();
					Output.printCrate(crate);
					Output.printDashLine();
					System.out.println();
				}
				else if(x instanceof Drum)
				{
					Drum drum = (Drum)listIn.get(j); // CAST IT!
					Output.printDrumHeader();
					Output.printDrum(drum);
					Output.printDashLine();
					System.out.println();
				}
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

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/
	private static boolean findPackageHelper = false;
}
