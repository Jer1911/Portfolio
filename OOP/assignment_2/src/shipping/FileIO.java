package shipping;

import java.io.*;
import java.util.*;

/**
	A class to handle file operations for Shipping. Handles Package, User,
	and Transaction ArrayLists.
*/
public class FileIO
{
	/***************************************************************************
	Methods for User file operations:
	***************************************************************************/

    /**
        Reads a serial file into ArrayList of Users.
		@return ArrayList of type User
		@throws IOException - caught by calling method.
		@throws ClassNotFoundException - caught here.
    */
	@SuppressWarnings("unchecked") // needed for erroneous IOE.
	public static ArrayList<User> readUserFile() throws IOException,
		ClassNotFoundException
    {
        FileInputStream fis = new FileInputStream("users.ser");
        ObjectInputStream ois = new ObjectInputStream(fis);
		ArrayList<User> newList = new ArrayList<User>();
		try
		{
			newList = (ArrayList<User>)ois.readObject();
		}
		catch (ClassNotFoundException e)
		{
			System.out.println("Class not found. Your computer will "
				+ "explode in 3... 2... 1...");
		}
		finally
		{
	        fis.close();
		}
		return newList;
    }

	/**
		Creates a new User serial file if no file exists.
		@return ArrayList of type User
		@throws IOException is caught within method
		@throws ClassNotFoundException - caught here.
	*/
	public static ArrayList<User> createUserFile() throws IOException,
		ClassNotFoundException
	{
		ArrayList<User> newList = new ArrayList<User>();
		try
		{
			newList = readUserFile();
		}
		catch (FileNotFoundException e)
		{
			try
			{
				System.out.println("users.ser not found. Creating...");
				new File("users.ser").createNewFile();
				System.out.println("File created. Initializing list.");
				try
				{
					newList = readUserFile();
				}
				catch (ClassNotFoundException ce)
				{
					throw new RuntimeException("Class not found. Your computer "
						+ " will explode in 3... 2... 1...");
				}
			}
			catch (IOException ioe) // here is where the erroneous IOE is caught
			{
				System.out.println();
			}
		}
		return newList;
	}

    /**
		Writes to the User serial file.
		@param userList ArrayList of type User
		@throws IOException which is caught within method.
	*/
	public static void writeUserFile(ArrayList<User> userList)
		throws IOException
	{
		FileOutputStream fos = new FileOutputStream("users.ser");
		try
		{
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(userList);
		}
		catch (IOException ioe)
		{
			throw new RuntimeException("File write failure. Check your"
						+ " permissions. Terminating program.");
		}
		finally
		{
			fos.close();
		}
	}

	/***************************************************************************
	Methods for Package file operations:
	****************************************************************************

    /**
        Reads a serial file into ArrayList of Packages.
		@return ArrayList of type Package
		@throws IOException - caught by calling method.
		@throws ClassNotFoundException - caught here.
    */
	@SuppressWarnings("unchecked") // needed for erroneous IOE.
	public static ArrayList<Package> readPackageFile() throws IOException,
		ClassNotFoundException
    {
        FileInputStream fis = new FileInputStream("packages.ser");
        ObjectInputStream ois = new ObjectInputStream(fis);
		ArrayList<Package> newList = new ArrayList<Package>();
		try
		{
			newList = (ArrayList<Package>)ois.readObject();
		}
		catch (ClassNotFoundException e)
		{
			System.out.println("Class not found. Your computer will "
				+ "explode in 3... 2... 1...");
		}
		finally
		{
	        fis.close();
		}
		return newList;
    }

	/**
		Creates a new Package serial file if no file exists.
		@return ArrayList of type Package
		@throws IOException is caught within method
		@throws ClassNotFoundException - caught here.
	*/
	public static ArrayList<Package> createPackageFile() throws IOException,
		ClassNotFoundException
	{
		ArrayList<Package> newList = new ArrayList<Package>();
		try
		{
			newList = readPackageFile();
		}
		catch (FileNotFoundException e)
		{
			try
			{
				System.out.println("packages.ser not found. Creating...");
				new File("packages.ser").createNewFile();
				System.out.println("File created. Initializing list.");
				try
				{
					newList = readPackageFile();
				}
				catch (ClassNotFoundException ce)
				{
					throw new RuntimeException("Class not found. Your computer "
						+ " will explode in 3... 2... 1...");
				}
			}
			catch (IOException ioe) // here is where the erroneous IOE is caught
			{
				System.out.println();
			}
		}
		return newList;
	}

	/**
		Writes to the Package serial file.
		@param packageList ArrayList of type Package
		@throws IOException which is caught within method.
	*/
	public static void writePackageFile(ArrayList<Package> packageList)
		throws IOException
	{
		FileOutputStream fos = new FileOutputStream("packages.ser");
		try
		{
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(packageList);
		}
		catch (IOException ioe)
		{
			System.out.println();
		}
		finally
		{
			fos.close();
		}
	}


	/***************************************************************************
	Methods for Transaction file operations:
	****************************************************************************

    /**
        Reads a serial file into ArrayList of Transactions.
		@return ArrayList of type Transaction
		@throws IOException - caught by calling method.
		@throws ClassNotFoundException - caught here.
    */
	@SuppressWarnings("unchecked") // needed for erroneous IOE.
	public static ArrayList<Transaction> readTransactionFile() throws IOException,
		ClassNotFoundException
    {
		ArrayList<Transaction> newList = new ArrayList<Transaction>();
		try
		{
	        FileInputStream fis = new FileInputStream("transactions.ser");
    	    ObjectInputStream ois = new ObjectInputStream(fis);
			try
			{
				newList = (ArrayList<Transaction>)ois.readObject();
				fis.close();
				return newList;
			}
			catch (ClassNotFoundException e)
			{
				System.out.println("Class not found. Your computer will "
					+ "explode in 3... 2... 1...");
			}
			finally
			{
		        fis.close();
				return newList;
			}
		}
		catch (EOFException e)
		{
			System.out.println();
		}
		return newList;
    }

	/**
		Creates a new Transaction serial file if no file exists.
		@return ArrayList of type Transaction
		@throws IOException is caught within method
		@throws ClassNotFoundException - caught here.
	*/
	public static ArrayList<Transaction> createTransactionFile() throws IOException,
		ClassNotFoundException
	{
		ArrayList<Transaction> newList = new ArrayList<Transaction>();
		try
		{
			newList = readTransactionFile();
		}
		catch (FileNotFoundException e)
		{
			try
			{
				System.out.println("transactions.ser not found. Creating...");
				new File("transactions.ser").createNewFile();
				System.out.println("File created. Initializing list.");
				try
				{
					newList = readTransactionFile();
				}
				catch (ClassNotFoundException ce)
				{
					throw new RuntimeException("Class not found. Your computer "
						+ " will explode in 3... 2... 1...");
				}
			}
			catch (IOException ioe) // here is where the erroneous IOE is caught
			{
				System.out.println();
			}
		}
		return newList;
	}

	/**
		Writes to the Transaction serial file.
		@param transactionList ArrayList of type Transaction
		@throws IOException which is caught within method.
	*/
	public static void writeTransactionFile(ArrayList<Transaction> 
			transactionList) throws IOException
	{
		FileOutputStream fos = new FileOutputStream("transactions.ser");
		try
		{
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(transactionList);
		}
		catch (IOException ioe)
		{
			System.out.println();
		}
		finally
		{
			fos.close();
		}
	}
}
