package shipping;

import java.io.*;

/**
	A class to manage shipping package inventory.
*/
public class Package implements Serializable, Comparable<Package>
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Package()
	{}

	/**
		Parameterized constructor.
		@param tn String
		@param s String
		@param m String
	*/
	public Package(String tn, String s, String m)
	{
		setTrackingNumber(tn);
		setSpecification(s);
		setMailingClass(m);
	}

	/*-------------------------------------------------------------------------
	Redefined compareTo method:
	-------------------------------------------------------------------------*/

	public int compareTo(Package rhs)
	{
		String rhsTrackingNumber = ((Package)rhs).trackingNumber;
		return trackingNumber.compareTo(rhsTrackingNumber);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the tracking number.
		@param x Package
		@return String
	*/
	public static String getTrackingNumber(Package x)
	{return x.trackingNumber;}

	/**
		Gets the specification.
		@param x Package
		@return String
	*/
	public static String getSpecification(Package x)
	{return x.specification;}

	/**
		Gets the mailing class.
		@param x Package
		@return String
	*/
	public static String getMailingClass(Package x)
	{return x.mailingClass;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the tracking number.
		@param String
	*/
	private void setTrackingNumber(String tn)
	{trackingNumber = tn;}

	/**
		Sets the specification.
		@param String
	*/
	private void setSpecification(String s)
	{specification = s;}

	/**
		Sets the mailing class.
		@param String
	*/
	private void setMailingClass(String m)
	{mailingClass = m;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private String trackingNumber;
	private String specification;
	private String mailingClass;
}

