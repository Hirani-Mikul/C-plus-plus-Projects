// Auto Scan And Print System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "FileWatcher.h"

/*
	-------------------------------------- PROBLEM --------------------------------------
	
	
	The document needs to be scanned and then required to move to other folder and then print to the specified printer



	------------------------------------ SOLUTION ---------------------------------------


	When the scan button is pressed on the printer, it sends the file to a specified folder. A program needs to be built that is always running
	and watching a specified folder. The program watches for changes in the folder, when the change is detected. Therefore, the program automatically
	moves the file to the new specified foler and prints the file.

	*********************************** REQUIRED ***********************************************

	1. The program starts after the windows boot.
	2. The program always watch the specified folder.
	3. The program must exit if user authenticate.
	4. The program must save the details so there is no need of retyping the details.
	5. The program should let the user update the details any time.
	6. The program should warn the user of any action taken by user.


	----------------------------------------- STEPS -------------------------------------------
	1. Press the scan button
	 - The printer sends the file to the specified folder.
	2. When the file is dumped into the specified folder by the printer, the program should detect it.
	3. Verify the file.
	4. Move to the another folder.
	5. Print a copy to the printer.

*/


/*
	1. Include all libraries that are needed.

*/


void printFile() {

}


int main()
{


	return 0;

	std::filesystem::path fileName = "/Trial.txt";
	std::filesystem::path fileInPath = "./IN";
	std::filesystem::path fileOutPath = "./OUT";
	std::filesystem::path errorPath = "./ERROR";


	


	FileWatcher filewatcher { fileInPath.string(), std::chrono::milliseconds(3000)};

	std::cout << "Program started.\n";

	filewatcher.start([&](std::string path_to_watch, FileStatus status) -> void {

		// Process only regular files, all other file types are ignored

		if (!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != FileStatus::erased) {

			return;
		}
		
	switch (status)
	{	
	case FileStatus::created:
		std::cout << "File Created " << std::filesystem::path(path_to_watch).filename() << "\n";

	try
	{
		std::filesystem::path fileName = std::filesystem::path(path_to_watch).filename();
		std::filesystem::path target = fileOutPath / fileName;
		std::filesystem::create_directories(fileOutPath);
		std::filesystem::copy_file(fileInPath / fileName , target, std::filesystem::copy_options::overwrite_existing);
		std::filesystem::remove(fileInPath / fileName);

		// SEND A COPY TO THE PRINTER
	}
	catch (const std::exception& err)
	{
		std::filesystem::path fileName = std::filesystem::path(path_to_watch).filename();

		std::filesystem::create_directories(errorPath);
		std::filesystem::path targetError = errorPath / fileName;

		std::filesystem::copy_file(fileInPath / fileName, targetError, std::filesystem::copy_options::overwrite_existing);

		std::cout << err.what();
	}

		break;
	case FileStatus::modified:
		std::cout << "File Modified " << std::filesystem::path(path_to_watch).filename() << "\n";

		break;
	case FileStatus::erased:
		std::cout << "File Erased " << std::filesystem::path(path_to_watch).filename() << "\n";

		break;
	default:
		std::cout << "Error! Unknown file status.\n";

		break;
	}

	});


}