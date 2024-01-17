package shipping;

import java.io.*;

/**
	A class to make Envelope objects. This is a subclass of Package.
*/
public class Envelope extends Package
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Envelope()
	{}

	/**
		Parameterized constructor.
		@param tn String
		@param s String
		@param m String
		@param h int
		@param w int		
	*/
	public Envelope(String tn, String s, String m, int h, int w)
	{
		super(tn, s, m);
		setHeight(h);
		setWidth(w);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the height.
		@param x Envelope
		@return int
	*/
	public static int getHeight(Envelope x)
	{return x.height;}

	/**
		Gets the width.
		@param x Envelope
		@return int
	*/
	public static int getWidth(Envelope x)
	{return x.width;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the height
		@param int
	*/
	private void setHeight(int h)
	{height = h;}

	/**
		Sets the width
		@param int
	*/
	private void setWidth(int w)
	{width = w;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private int height, width;
}

