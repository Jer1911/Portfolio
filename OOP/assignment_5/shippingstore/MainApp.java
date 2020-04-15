package shippingstore;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.util.logging.*;

/**
	Class to handle the interface for the shipping store.
	@author Jeremy Ecker
*/
public class MainApp
{
	private final static Logger logger = Logger.getLogger(MainApp.class.getName());

	/**
		Constructor. Creates the GUI and buttons for the shipping store interface.
	*/
	MainApp()
	{
		// make shipping store object:
		ShippingStore ss = ShippingStore.readDatabase();
		logger.log(Level.INFO, "Shipping store accessed.");

		// create the main window:
		JFrame frame = new JFrame("Shipping Store Manager v1.0");

		// add top label:
		JLabel welcome = new JLabel("Shipping Store Manager v1.0");

		// create main menu panel:
		JPanel menuPanel = new JPanel();
		menuPanel.setLayout(new GridLayout(0,1));

		// create info panel:
		JPanel infoPanel = new JPanel();
		JTextArea display = new JTextArea(40, 80);
		display.setEditable(false);
		JScrollPane scroll = new JScrollPane(display);
		scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		infoPanel.add(scroll);

		// create show packages button:
		JButton showAllPackages = new JButton("Show all packages");
		showAllPackages.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				String text = ss.getAllPackagesFormatted();
				display.setText(null);
				display.insert(text, 0);
				logger.log(Level.INFO, "show packages button pressed.");
			}
		});

		// create add package button:
		JButton addNewPackage = new JButton("Add new package");
		addNewPackage.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				display.setText(null);
				boolean inputAccepted = false;
				String t = "";
				String tn = "";
				String s = "";
				String mc = "";
				String c = "";
				String m = "";
				int h = 0;
				int w = 0;
				int d = 0;
				int v = 0;
				float weight = 0.0f;
				float diameter = 0.0f;

				// type dialogue:
				Object[] types = {"Envelope", "Box", "Crate", "Drum"};
				t = (String)JOptionPane.showInputDialog
					(frame,
                    "Select package type: ",
                    "package type dialogue",
                    JOptionPane.PLAIN_MESSAGE,
					null,
                    types,
                    null);
				display.append(t + " ");

				// tracking number dialogue:
				while(!inputAccepted)
				{
					tn = (String)JOptionPane.showInputDialog
						(frame, "Enter tracking number: ");
					if(tn.length() == 5 && !ss.packageExists(tn))
					{
						display.append(tn + " ");
						inputAccepted = true;
					}
				}
				inputAccepted = false;

				// specification dialogue:
				Object[] specs = {"Fragile", "Books", "Catalogs", "Do-not-bend", "N/A"};
				s = (String)JOptionPane.showInputDialog
					(frame,
                    "Select package specification: ",
                    "package specification dialogue",
                    JOptionPane.PLAIN_MESSAGE,
					null,
                    specs,
                    null);
				display.append(s + " ");

				// mailing class dialogue:
				Object[] mailingClass = {"First-Class", "Priority", "Retail", "Ground", "Metro"};
				mc = (String)JOptionPane.showInputDialog
					(frame,
                    "Select package mailing class: ",
                    "package mailing class dialogue",
                    JOptionPane.PLAIN_MESSAGE,
					null,
                    mailingClass,
                    null);
				display.append(mc + " ");

				// envelope height and width dialogues:
				if(t.equals("Envelope"))
				{
					while(!inputAccepted)
					{
						h = Integer.parseInt(JOptionPane.showInputDialog
							(frame, "Enter envelope height: "));
						if(h>0)
						{
							display.append(h + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					while(!inputAccepted)
					{
						w = Integer.parseInt(JOptionPane.showInputDialog
							(frame, "Enter envelope width: "));
						if(w>0)
						{
							display.append(w + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					ss.addEnvelope(tn, s, mc, h, w);
				}

				// box dialogue:
				else if(t.equals("Box"))
				{
					while(!inputAccepted)
					{
						d = Integer.parseInt(JOptionPane.showInputDialog
							(frame, "Enter box largest dimension: "));
						if(d>0)
						{
							display.append(d + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					while(!inputAccepted)
					{
						v = Integer.parseInt(JOptionPane.showInputDialog
							(frame, "Enter box volume: "));
						if(v>0)
						{
							display.append(v + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					ss.addBox(tn, s, mc, d, v);
				}

				// crate dialogue:
				else if(t.equals("Crate"))
				{
					while(!inputAccepted)
					{
						weight = Float.parseFloat(JOptionPane.showInputDialog
								(frame, "Enter crate max load: "));
						if(weight>0)
						{
							display.append(weight + " ");
							inputAccepted = true;
						}
					}
					c = (String)JOptionPane.showInputDialog
					(frame,
                    "Enter crate contents: ");
					display.append(c + " ");
					ss.addCrate(tn, s, mc, w, c);
				}

				// drum dialogue:
				else if(t.equals("Drum"))
				{
					m = (String)JOptionPane.showInputDialog
							(frame, "Enter drum material: ");
					display.append(m + " ");
					while(!inputAccepted)
					{
						diameter = Float.parseFloat(JOptionPane.showInputDialog
								(frame, "Enter drum diameter: "));
						if(diameter>0)
						{
							display.append(diameter + " ");
							inputAccepted = true;
						}
					}
					ss.addDrum(tn, s, mc, m, diameter);
					inputAccepted = false;
				}
				logger.log(Level.INFO, "add package button pressed.");
			}
		});

		// create delete package button:
		JButton deletePackage = new JButton("Delete package");
		deletePackage.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				String tn = "";
				boolean inputAccepted = false;
				display.setText(null);
				while(!inputAccepted)
				{
					tn = (String)JOptionPane.showInputDialog
						(frame, "Enter tracking number of package to delete: ");
					if(tn.length() == 5 && ss.packageExists(tn))
					{
						display.append(tn + " ");
						inputAccepted = true;
					}
				}
				if(ss.deletePackage(tn))
				{
					display.append("Package deleted!");
				}
				logger.log(Level.INFO, "delete package button pressed.");
			}
		});

		// create search package button:
		JButton searchPackage = new JButton("Search package");
		searchPackage.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				String tn = "";
				boolean inputAccepted = false;
				display.setText(null);
				while(!inputAccepted)
				{
					tn = (String)JOptionPane.showInputDialog
						(frame, "Enter tracking number of package to find: ");
					if(tn.length() == 5 && ss.packageExists(tn))
					{
						display.append(tn + " ");
						inputAccepted = true;
					}
				}
				if(ss.packageExists(tn))
				{
					display.append("Package found!\n");
					String pkg = ss.getPackageFormatted(tn);
					display.append(pkg);
				}
				logger.log(Level.INFO, "search package button pressed.");
			}
		});

		// create show users button:
		JButton showAllUsers = new JButton("Show all users");
		showAllUsers.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				String text = ss.getAllUsersFormatted();
				display.setText(null);
				display.insert(text, 0);
				logger.log(Level.INFO, "show users button pressed.");
			}
		});

		// create add user button:
		JButton addNewUser = new JButton("Add new users");
		addNewUser.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				display.setText(null);
		        int userType = 0;
				boolean check = false;
				String firstName = "";
				String lastName = "";
				String phoneNumber = "";
				String address = "";
				float monthlySalary = 0.0f;
				int ssn = 0;
				boolean inputAccepted = false;
				int bankAccNumber = 0;
				while(!check)
				{
					userType = Integer.parseInt(JOptionPane.showInputDialog
						(frame, "Enter user type (1 for customer, 2 for employee): "));
					if(userType == 1 || userType == 2)
					{
						display.append(userType + " ");
						check = true;
					}
				}
				check = false;
				firstName = (String)JOptionPane.showInputDialog
					(frame, "Enter first name: ");
				display.append(firstName);
				lastName = (String)JOptionPane.showInputDialog
					(frame, "Enter last name: ");
				display.append(lastName);
				if(userType == 1)
				{
					phoneNumber = (String)JOptionPane.showInputDialog
						(frame, "Enter phone number: ");
					display.append(phoneNumber);
					address = (String)JOptionPane.showInputDialog
						(frame, "Enter address: ");
					display.append(address);
					ss.addCustomer(firstName, lastName, phoneNumber, address);
				}
				else if (userType == 2)
				{
					while(!inputAccepted)
					{
						monthlySalary = Float.parseFloat(JOptionPane.showInputDialog
								(frame, "Enter employee monthly salary: "));
						if(monthlySalary>0)
						{
							display.append(monthlySalary + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					while(!inputAccepted)
					{
						ssn = Integer.parseInt(JOptionPane.showInputDialog
							(frame, "Enter employee ssn (9 digits): "));
						if(ssn>=10000000 && ssn <=999999999)
						{
							display.append(ssn + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					while(!inputAccepted)
					{
						bankAccNumber = Integer.parseInt(JOptionPane.showInputDialog
							(frame, "Enter employee bank account number: "));
						if(bankAccNumber>0)
						{
							display.append(bankAccNumber + " ");
							inputAccepted = true;
						}
					}
					inputAccepted = false;
					ss.addEmployee(firstName, lastName, ssn, monthlySalary, bankAccNumber);
				}
				logger.log(Level.INFO, "add user button pressed.");
			}
		});

		// create update user button:
		JButton updateUser = new JButton("Update a user");
		updateUser.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				int userID = 0;
				display.setText(null);
		        int userType = 0;
				String firstName = "";
				String lastName = "";
				String phoneNumber = "";
				String address = "";
				float monthlySalary = 0.0f;
				int ssn = 0;
				boolean inputAccepted = false;
				int bankAccNumber = 0;

				while(!inputAccepted)
				{
					userID = Integer.parseInt(JOptionPane.showInputDialog
						(frame, "Enter user ID number: "));
					if(ss.userExists(userID))
					{
						firstName = (String)JOptionPane.showInputDialog
							(frame, "Enter first name: ");
						display.append(firstName);
						lastName = (String)JOptionPane.showInputDialog
							(frame, "Enter last name: ");
						display.append(lastName);
						if (ss.isCustomer(userID))
						{
							phoneNumber = (String)JOptionPane.showInputDialog
								(frame, "Enter phone number: ");
							display.append(phoneNumber);
							address = (String)JOptionPane.showInputDialog
								(frame, "Enter address: ");
							display.append(address);
							ss.updateCustomer(userID, firstName, lastName, phoneNumber, address);
						}
						else
						{
							while(!inputAccepted)
							{
								monthlySalary = Float.parseFloat(JOptionPane.showInputDialog
										(frame, "Enter employee monthly salary: "));
								if(monthlySalary>0)
								{
									display.append(monthlySalary + " ");
									inputAccepted = true;
								}
							}
							inputAccepted = false;
							while(!inputAccepted)
							{
								ssn = Integer.parseInt(JOptionPane.showInputDialog
									(frame, "Enter employee ssn (9 digits): "));
								if(ssn>=10000000 && ssn <=999999999)
								{
									display.append(ssn + " ");
									inputAccepted = true;
								}
							}
							inputAccepted = false;
							while(!inputAccepted)
							{
								bankAccNumber = Integer.parseInt(JOptionPane.showInputDialog
									(frame, "Enter employee bank account number: "));
								if(bankAccNumber>0)
								{
									display.append(bankAccNumber + " ");
									inputAccepted = true;
								}
							}
							inputAccepted = false;
							ss.updateEmployee(userID, firstName, lastName, ssn,
								monthlySalary,bankAccNumber);
						}
					}
					inputAccepted = true;
				}
				logger.log(Level.INFO, "update user button pressed.");
			}
		});

		// create deliver package button:
		JButton deliverPackage = new JButton("Deliver package");
		deliverPackage.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				display.setText(null);
				Date currentDate = new Date(System.currentTimeMillis());
				int employeeID = 0;
				int customerID = 0;
				String trackingNumber = "";
				boolean inputAccepted = false;
				float price = 0.0f;

				customerID = Integer.parseInt(JOptionPane.showInputDialog
					(frame, "Enter customer ID number: "));
				display.append(customerID + " ");
				employeeID = Integer.parseInt(JOptionPane.showInputDialog
					(frame, "Enter employee ID number: "));
				display.append(employeeID + " ");
				if(ss.userExists(customerID) && ss.userExists(employeeID))
				{
					trackingNumber = (String)JOptionPane.showInputDialog
						(frame, "Enter tracking number: ");
					display.append(trackingNumber + " ");
					if(ss.packageExists(trackingNumber))
					{
						price = Float.parseFloat(JOptionPane.showInputDialog
								(frame, "Enter price: "));
						display.append(price + " ");
						if(price >= 0.0f)
						{
							ss.addShppingTransaction(customerID, employeeID,
							trackingNumber, currentDate, currentDate, price);
					        ss.deletePackage(trackingNumber);
							display.append("\nSuccess! Transaction completed.\n");
						}
						else
						{
							display.append("\nFailure. Incorrect price.\n");
						}
					}
					else
					{
						display.append("\nFailure. Incorrect tracking number.\n");
					}
				}
				else
				{
					display.append("\nFailure. Incorrect ID detected.\n");
				}
				logger.log(Level.INFO, "deliver package button pressed.");
			}
		});

		// create show transactions button:
		JButton showAllTransactions = new JButton("Show all transactions");
		showAllTransactions.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				display.setText(null);
				String text = ss.getAllTransactionsText();
				display.insert(text, 0);
				logger.log(Level.INFO, "show transactions button pressed.");
			}
		});

		// create save and quit button:
		JButton saveAndQuit = new JButton("Save and quit");
		saveAndQuit.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				display.setText(null);
				ss.writeDatabase();
				logger.log(Level.INFO, "save and quit button pressed.");
				System.exit(0);
			}
		});

		// emplace buttons:
		menuPanel.add(showAllPackages);
		menuPanel.add(addNewPackage);
		menuPanel.add(deletePackage);
		menuPanel.add(searchPackage);
		menuPanel.add(showAllUsers);
		menuPanel.add(addNewUser);
		menuPanel.add(updateUser);
		menuPanel.add(deliverPackage);
		menuPanel.add(showAllTransactions);
		menuPanel.add(saveAndQuit);

		// fire up display:
		frame.add(infoPanel, BorderLayout.CENTER);
		frame.add(menuPanel, BorderLayout.LINE_START);
		frame.add(welcome, BorderLayout.PAGE_START);
		frame.setSize(1250, 650);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

	/**
		Main method. Sets up the logger, then calls the constructor.
	*/
	public static void main(String[] args) throws IOException
	{		
		logger.setLevel(Level.INFO);
		FileHandler fh = new FileHandler("shippinglog.%u.%g.txt");
		fh.setFormatter(new SimpleFormatter());
		ConsoleHandler ch = new ConsoleHandler();
		ch.setFormatter(new SimpleFormatter());
		logger.addHandler(ch);
		logger.addHandler(fh);
		SwingUtilities.invokeLater(new Runnable()
		{
			public void run()
			{
				MainApp app = new MainApp();
			}
		});
	}
}

