package shipping;

import java.io.*;

/**
	A class to make Box objects. This is a subclass of Package.
*/
public class Box extends Package
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Box()
	{}

	/**
		Parameterized constructor.
		@param tn String
		@param s String
		@param m String
		@param ld int
		@param v int		
	*/
	public Box(String tn, String s, String m, int ld, int v)
	{
		super(tn, s, m);
		setLargestDimension(ld);
		setVolume(v);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the largest dimension.
		@param x Box
		@return int
	*/
	public static int getLargestDimension(Box x)
	{return x.largestDimension;}

	/**
		Gets the volume.
		@param x Box
		@return int
	*/
	public static int getVolume(Box x)
	{return x.volume;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the largest dimension.
		@param int
	*/
	private void setLargestDimension(int ld)
	{largestDimension = ld;}

	/**
		Sets the volume.
		@param int
	*/
	private void setVolume(int v)
	{volume = v;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private int largestDimension, volume;
}

