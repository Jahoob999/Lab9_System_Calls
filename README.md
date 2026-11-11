# Lab9_System_Calls
This program contains 4 different executable files all using different kinds of system calls

## info.c
runs a series of system calls and prints the following information
- current time in nanoseconds
- the system's network name
- OS name
- OS release and version
- the system's hardware type
- The number of CPUs on the system
- The total amount of physical memory in bytes
- The total amount of free memory in bytes

## pinfo.c
enter a pid in the command line when starting this program then the program prints out the pid along with its priority and scheduling method. If no pid is provided the program will print the information for the current executing process

## pmod.c
when calling this program it will reduce its own priority by 10 by adding 10 to its nice value it will then sleep for 1,837,272,638 nano seconds (about 1.8 seconds) and print goodbye before closing the program

## finfo.c
run the program by entering a filename including the file extension the program will then print out a information about the file including
- type of file
- permissions on file
- owner of the file (user id number)
- size of file in bytes
- date and time of last modification (in format mm/dd/yyyy HH:MM:SS where the time of day is in military time)
