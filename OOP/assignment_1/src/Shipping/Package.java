package Shipping;

/**
	A class to manage shipping package inventory.
*/
public class Package
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
		@param t String
		@param s String
		@param m String
		@param w double
		@param v int
	*/
	public Package(String tn, String t, String s, String m, double w,
		int v)
	{
		setTrackingNumber(tn);
		setType(t);
		setSpecification(s);
		setMailingClass(m);
		setWeight(w);
		setVolume(v);
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
		Gets the type.
		@param x Package
		@return String
	*/
	public static String getType(Package x)
	{return x.type;}

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

	/**
		Gets the weight.
		@param x Package
		@return double
	*/
	public static double getWeight(Package x)
	{return x.weight;}

	/**
		Gets the volume.
		@param x Package
		@return int
	*/
	public static int getVolume(Package x)
	{return x.volume;}

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
		Sets the type.
		@param String
	*/
	private void setType(String t)
	{type = t;}

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

	/**
		Sets the weight.
		@param double
	*/
	private void setWeight(double w)
	{weight = w;}

	/**
		Sets the volume.
		@param int
	*/
	private void setVolume(int v)
	{volume = v;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private String trackingNumber;
	private String type;
	private String specification;
	private String mailingClass;
	private double weight;
	private int volume;

}

