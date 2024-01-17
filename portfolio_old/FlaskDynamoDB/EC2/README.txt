Basic Steps to spin up EC2 server:

- In the NOTES folder, examine server_command_history.txt
	It contains a curated list of commands used for the example server.

- file_path_info.txt shows the locations of where the files should live
	on the example server.

- useful_links.txt contains links to the basic guides I used.

- This is not "plug 'n play". Read and understand the examples, and you
	should be able to have a ready to go EC2 within a relatively short
	time. (DISCLAIMER: 'relatively short time' is relative to all commands
	except the diffie-hellman generation - go ahead and go for a coffee
	after you run that command.)

IMPORTANT:
The main deviation from the guide was that I elected to use a self-signed
SSL certificate rather than the recommended certbot method. This decision
came after the realization that certbot does not allow naked IP's, and I am
using naked IP's for clarity. In a production environment, there would
naturally be a DNS with a legit SSL instead.
