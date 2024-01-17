package shipping;

import java.io.*;
import java.util.*;

/**
	A class to make Transaction objects.
*/
public class Transaction implements Serializable
{
	/*-------------------------------------------------------------------------
	Constructors:
	-------------------------------------------------------------------------*/

	/** Default constructor */
	public Transaction()
	{}

	/**
		Parameterized constructor.
		@param cid int - customer id
		@param tn String - tracking number
		@param sd Calendar - shipping date
		@param dd Calendar - delivery date
		@param cs double - cost of shipping
		@param eid int - employee id
	*/
	public Transaction(int cid, String tn, Calendar sd, Calendar dd, double cs,
			int eid)
	{
		setCustomerId(cid);
		setTrackingNumber(tn);
		setShippingDate(sd);
		setDeliveryDate(dd);
		setCost(cs);
		setEmployeeId(eid);
	}

	/*-------------------------------------------------------------------------
	Getters:
	-------------------------------------------------------------------------*/

	/**
		Gets the customer id.
		@param x Transaction
		@return int
	*/
	public static int getCustomerId(Transaction x)
	{return x.customerId;}

	/**
		Gets the tracking number.
		@param x Transaction
		@return String
	*/
	public static String getTrackingNumber(Transaction x)
	{return x.trackingNumber;}

	/**
		Gets the shipping date.
		@param x Transaction
		@return Calendar
	*/
	public static Calendar getShippingDate(Transaction x)
	{return x.shippingDate;}

	/**
		Gets the delivery date.
		@param x Transaction
		@return Calendar
	*/
	public static Calendar getDeliveryDate(Transaction x)
	{return x.deliveryDate;}

	/**
		Gets the shipping cost.
		@param x Transaction
		@return double
	*/
	public static double getCost(Transaction x)
	{return x.cost;}

	/**
		Gets the employee id number.
		@param x Transaction
		@return int
	*/
	public static int getEmployeeId(Transaction x)
	{return x.employeeId;}

	/*-------------------------------------------------------------------------
	Setters:
	-------------------------------------------------------------------------*/

	/**
		Sets the customer id.
		@param int
	*/
	private void setCustomerId(int cid)
	{customerId = cid;}

	/**
		Sets the tracking number.
		@param String
	*/
	private void setTrackingNumber(String tn)
	{trackingNumber = tn;}

	/**
		Sets the shipping date.
		@param Calendar
	*/
	private void setShippingDate(Calendar sd)
	{shippingDate = sd;}

	/**
		Sets the delivery date.
		@param Calendar
	*/
	private void setDeliveryDate(Calendar dd)
	{deliveryDate = dd;}

	/**
		Sets the cost.
		@param double
	*/
	private void setCost(double cs)
	{cost = cs;}

	/**
		Sets the employee id.
		@param int
	*/
	private void setEmployeeId(int eid)
	{employeeId = eid;}

	/*-------------------------------------------------------------------------
	Variables:
	-------------------------------------------------------------------------*/

	private int customerId;
	private int employeeId;
	private String trackingNumber;
	private Calendar shippingDate;
	private Calendar deliveryDate;
	private double cost;
}
