package shipping;

import java.io.*;

/**
	A class to make employee objects. This is a subclass of User.
*/
public class Employee extends User
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Employee()
	{}

	/**
		Parameterized constructor.
		@param id int
		@param ln String
		@param fn String
		@param ssn int
		@param sal double
		@param acct int
	*/
	public Employee(int id, String ln, String fn, int ssn, double sal, int acct)
	{
		super(id, ln, fn);
		setSsn(ssn);
		setSalary(sal);
		setAcctNum(acct);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the social security number.
		@param x Employee
		@return int
	*/
	public static int getSsn(Employee x)
	{return x.social;}

	/**
		Gets the ssalary.
		@param x Employee
		@return double
	*/
	public static double getSalary(Employee x)
	{return x.salary;}

	/**
		Gets the bank account number.
		@param x Employee
		@return int
	*/
	public static int getAcctNum(Employee x)
	{return x.acctNum;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the social security number
		@param int
	*/
	private void setSsn(int ssn)
	{social = ssn;}

	/**
		Sets the salary
		@param double
	*/
	private void setSalary(double sal)
	{salary = sal;}

	/**
		Sets the bank account number
		@param int
	*/
	private void setAcctNum(int acct)
	{acctNum = acct;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private int social, acctNum;
	private double salary;
}

