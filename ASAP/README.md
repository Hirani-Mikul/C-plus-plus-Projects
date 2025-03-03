# ASAP

ASAP
The application (ASAP) is an application that prints the document to a printer automatically. It's a Window Desktop Application.
Purpose
To detect a PDF file, read it and print it.
How it works?
1.	A scanned PDF document is dumped into a folder.
2.	The application auto detects that PDF file.
3.	The detected file is opened and read.
4.	The read data is written on a printer.
5.	The printer prints a copy of a file.
6.	The file is moved to another folder.

Components
1.	The main application which is executed.
2.	A “IN PATH” directory which is monitored for any new file.
3.	A “OUT PATH” directory where printed files are moved to.
4.	An “Application” class that handles everything.
5.	A “Directory Watcher” class that detects a file.
6.	A “Printer” that prints the detected file.
7.	A “List” custom class.
Details of components
Main application
Creates an application object and starts it job.
Directory Watcher
It continuously and simultaneously watches over an input folder (IN PATH) in the background.  When a file is detected it stores it’s path in the container.
