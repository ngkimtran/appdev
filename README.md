# Application development project 2020

# This project is for I-IT-1N students to understand what procedure and what tools are needed in an application development.

General description of the application:
	This application will display sounds as barchart as well as send data to the server through a PHP file.

Table of contetns:
1. Configuration instructions
2. Installation instructions
3. Operating instructions
4. File manifest
5. Copyright and license information
6. Contact information
7. Credits and acknowledgements


----

1. Configuration instructions:
	You will need access to a shell server to run this program.

2. Installation instructions:
	Run 
		$git clone https://github.com/ngkimtran/appdev
	to copy the project into your local repository.

3. Operating instructions:
	Go to the directory you just cloned the project into (e.g $cd appdev) and run
		$make
		$./sound
	to start the program.

4. File manifest:
		README.md	 :	this file
		screen.c	 :	contains screen manipulation functions
		screen.h	 :	contains screen funtion declarations and related constants
		testscreen.c :	contains testing usage of functions in screen.c and comm.c
		makefile	 :	contains command lines to run the application
		comm.c		 :	contains all the functions for the client-server comunication
		comm.h		 :	contains client-server communication functions declaration and related constants
		testcurl.c	 :	contains testing function of client-server communication
		main.c		 :	contains the final version of the program
		sound.c		 :	contains functions to read the WAV file data and calculate them into dB values
		sound.h		 :	contains sound data functions  declaration and related constants
		sound.php	 :	contains the module to send data to the PHP program as a HTTP POST string

5. Copyright and license information:
	This application follows GPLv2 license.
