package shipping;

import java.io.*;

/**
	A class to make shipping user objects.
*/
public class User implements Serializable
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public User()
	{}

	/**
		Parameterized constructor.
		@param id int
		@param ln String
		@param fn String
	*/
	public User(int id, String ln, String fn)
	{
		setId(id);
		setLastName(ln);
		setFirstName(fn);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the user id.
		@param x User
		@return int
	*/
	public static int getId(User x)
	{return x.userId;}

	/**
		Gets the last name.
		@param x User
		@return String
	*/
	public static String getLastName(User x)
	{return x.lastName;}

	/**
		Gets the first name.
		@param x User
		@return String
	*/
	public static String getFirstName(User x)
	{return x.firstName;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the user id.
		@param int
	*/
	private void setId(int id)
	{userId = id;}

	/**
		Sets the last name.
		@param String
	*/
	private void setLastName(String ln)
	{lastName = ln;}

	/**
		Sets the first name.
		@param String
	*/
	private void setFirstName(String fn)
	{firstName = fn;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private int userId;
	private String lastName;
	private String firstName;

}

