
/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *====================================================================================== 
Hint:
----
This is an interactive commandline version of the Colossal Cave adventure Game.
It is developed and tested on a 32 bit linux OS. 
It takes a verb-noun pair. You are presented with the prose description of the setting.
Then you type short, paired or some times one word command. 
e.g enter water
	take key
	go out
	walk down, left, west, and soon. 	
For more information, you can open the data.txt and see all the data.

Installation and connection to the server:
------------------------------------------
1. Unzip this archieve in a folder where you want to install the server
2. Use the Makefile file included here to setup and run the server. Use this command:
	'make Makefile'
3. To connect to the server and start playing, use telnet or ssh on port 4242.
	e.g. 'telnet server_IP_address 4242'
4. That is it and enjoy the adventure.
