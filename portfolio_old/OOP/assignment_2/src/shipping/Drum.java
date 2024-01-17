package shipping;

import java.io.*;

/**
	A class to make Drum objects. This is a subclass of Package.
*/
public class Drum extends Package
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Drum()
	{}

	/**
		Parameterized constructor.
		@param tn String
		@param s String
		@param m String
		@param mat String
		@param d double		
	*/
	public Drum(String tn, String s, String m, String mat, double d)
	{
		super(tn, s, m);
		setMaterial(mat);
		setDiameter(d);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the diameter.
		@param x Drum
		@return double
	*/
	public static double getDiameter(Drum x)
	{return x.diameter;}

	/**
		Gets the material.
		@param x Drum
		@return String
	*/
	public static String getMaterial(Drum x)
	{return x.material;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the diameter.
		@param double
	*/
	private void setDiameter(double d)
	{diameter = d;}

	/**
		Sets the material.
		@param String
	*/
	private void setMaterial(String mat)
	{material = mat;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private double diameter;
	private String material;
}

