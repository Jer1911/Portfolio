package shipping;

import java.io.*;

/**
	A class to make Customer objects. This is a subclass of User.
*/
public class Customer extends User
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Customer()
	{}

	/**
		Parameterized constructor.
		@param id int
		@param ln String
		@param fn String
		@param pn String
		@param adr String
	*/
	public Customer(int id, String ln, String fn, String pn, String adr)
	{
		super(id, ln, fn);
		setPhone(pn);
		setAddress(adr);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the phone number.
		@param x Customer
		@return String
	*/
	public static String getPhone(Customer x)
	{return x.phone;}

	/**
		Gets the address.
		@param x Customer
		@return String
	*/
	public static String getAddress(Customer x)
	{return x.address;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the phone number
		@param String
	*/
	private void setPhone(String pn)
	{phone = pn;}

	/**
		Sets the address
		@param String
	*/
	private void setAddress(String adr)
	{address = adr;}


	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private String phone;
	private String address;
}

