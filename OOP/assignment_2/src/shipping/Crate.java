package shipping;

import java.io.*;

/**
	A class to make Crate objects. This is a subclass of Package.
*/
public class Crate extends Package
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Crate()
	{}

	/**
		Parameterized constructor.
		@param tn String
		@param s String
		@param m String
		@param mlw double
		@param c String		
	*/
	public Crate(String tn, String s, String m, double mlw, String c)
	{
		super(tn, s, m);
		setMaxLoadWeight(mlw);
		setContent(c);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the maximum load weight.
		@param x Crate
		@return double
	*/
	public static double getMaxLoadWeight(Crate x)
	{return x.maxLoadWeight;}

	/**
		Gets the content.
		@param x Crate
		@return String
	*/
	public static String getContent(Crate x)
	{return x.content;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the maximum load weight.
		@param double
	*/
	private void setMaxLoadWeight(double mlw)
	{maxLoadWeight = mlw;}

	/**
		Sets the content.
		@param String
	*/
	private void setContent(String c)
	{content = c;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private double maxLoadWeight;
	private String content;
}

