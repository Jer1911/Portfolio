package shipping;

import java.util.ArrayList;

/**
    A wrapper for all classes within the Shipping package.
*/
public class ShippingWrapper
{
    public static void main(String[] args) throws Exception
    {
		// Populate ArrayLists from the serial files:
        ArrayList<Package> packageList = FileIO.createPackageFile();
		ArrayList<User> userList = FileIO.createUserFile();
		ArrayList<Transaction> transactionList = FileIO.createTransactionFile();

		// Display the interactive menu and get a choice:
		int choice = 0;
		while(choice != 10)
		{
			choice = Output.showMenu();
			if(choice == 1)
			{
				// Display the (sorted) package list:
				PackageOps.sortPackageList(packageList);
				PackageOps.printPackageList(packageList);
				
			}
			else if(choice == 2)
			{
				// Add a new record to package list:
				PackageOps.addPackage(packageList);
			}
			else if(choice == 3)
			{
				// Remove a package:
				PackageOps.removePackage(packageList);
			}
			else if(choice == 4)
			{
				// Search for a package:
				String caller = "main";
				PackageOps.findPackage(packageList, caller);
			}
			else if(choice == 5)
			{
				// Display the user list:
				UserOps.printUserList(userList);
			}
			else if(choice == 6)
			{
				// Add a new user:
				UserOps.addUser(userList);
			}
			else if(choice == 7)
			{
				// Update a user:
				UserOps.updateUser(userList);
			}
			else if(choice == 8)
			{
				// Complete a transaction:
				TransactionOps.addTransaction(transactionList, userList,
					packageList);
			}
			else if(choice == 9)
			{
				// Show completed transactions:
				Output.printTransactionList(transactionList);
			}
			else
			{
				if(choice != 10)
				{
					Output.printError();
				}
			}
		}

		// Save changes to file:
		FileIO.writePackageFile(packageList);
		FileIO.writeUserFile(userList);
		FileIO.writeTransactionFile(transactionList);

		// Say goodbye:
		System.out.println("Exiting program. Have a nice day!\n");
    }
}

