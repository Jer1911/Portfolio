package Shipping;

import java.util.ArrayList;

/**
    A wrapper class for Package and InputOutput.
*/
public class PackageWrapper
{
    public static void main(String[] args) throws Exception
    {
		// Populate an ArrayList from a text file:		
        ArrayList<Package> mainList = InputOutput.createFile();

		// Display the interactive menu and get a choice:
		int choice = 0;
		while(choice != 6)
		{
			choice = InputOutput.showMenu();
			if(choice == 1)
			{
				// Display the list:
				InputOutput.printList(mainList);
			}
			else if(choice == 2)
			{
				// Add a new record to mainList:
				InputOutput.addPackage(mainList);
			}
			else if(choice == 3)
			{
				// Remove a package:
				InputOutput.removePackage(mainList);
			}
			else if(choice == 4)
			{
				// Search for a package:
				String caller = "main";
				InputOutput.findPackage(mainList, caller);
			}
			else if(choice == 5)
			{
				// Show packages within a weight range:
				InputOutput.listByWeight(mainList);
			}
			else
			{
				if(choice != 6)
				{
					InputOutput.printError();
				}
			}
		}

		// Save changes to the text file:
		InputOutput.writeFile(mainList);

		// Say goodbye:
		System.out.println("Exiting program. Have a nice day!\n");
    }
}

