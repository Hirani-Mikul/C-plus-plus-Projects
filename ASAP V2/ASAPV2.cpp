#include <iostream>
#include "DirectoryWatcher.h"
#include <mutex>

#define BUFFERSIZE 32

struct Setting {

	std::string input_dir;
	std::string output_dir;
	TCHAR* printer = nullptr;
	std::chrono::milliseconds waiting;

	std::string log_path;

	~Setting()
	{
		if (printer) delete[] printer;
	}
};

bool getApplicationSetting();

bool writeApplicationSetting();

bool writeDefaultApplicationSettings();

bool verifyApplicationSettings();

bool InitiateApp();

bool readAndPrint(const std::filesystem::path&);

void monitorDirectory();

void moveSuccessFile(const std::filesystem::path&);
void moveFailedFile(const std::filesystem::path&);

Setting setting;

bool isEnded = false;

void showCommands()
{
	std::cout << "Valid acceptable commands:\n";
	std::cout << "~pause: pauses all the activities.\n";
	std::cout << "~resume: resumes all the activities.\n";
	std::cout << "~pausedir: pauses watching the \"IN\" directory.\n";
	std::cout << "~resumedir: resumes watching the \"IN\" directory.\n";
	std::cout << "~exit: exit the application.\n";

}

bool verifyCommands(char* command)
{
	std::string strcommand(command);

	if (strcommand == "resume" || strcommand == "pause" || strcommand == "pausedir" || strcommand == "resumedir" || strcommand == "exit")
		return true;
	else
		showCommands();

	return false;
}

bool isFirstInstance()
{
	// Create a mutex with a unique name for the program
	HANDLE hSingleInstanceMutex = CreateMutex(NULL, TRUE, L"ASAPV2");

	// Check if the mutex already exists
	if (hSingleInstanceMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
		return false; // The mutex exists, so this is the seconds instance
	else
		return true; // The mutex does not exist, so this is the first instance

}

void ReadFromPipe(const HANDLE& hStdIn)
{

	// Wait for a connection from the second instance
	std::cout << "Waiting for connection...\n";
	BOOL result = ConnectNamedPipe(hStdIn, NULL);

	// Check if the connection succeeded
	if (!result)
	{
		std::cout << "Error: failed to connect pipe.\n";
		isEnded = true;
		return;
	}
	std::cout << "Pipe connected.\n";
	// Wait for messages from the second instance
	while (true)
	{
		char message[BUFFERSIZE];
		DWORD bytesRead;

		// Read a message from the pipe
		result = ReadFile(hStdIn, message, sizeof(message), &bytesRead, NULL);

		// Check if the read operation succeeded
		// Print the received message

		if (!result || bytesRead == 0)
		{
			std::cout << "Error: failed to read from pipe. Code: " << GetLastError() << "\n";
			break;
		}

		std::cout << "Received message: " << message << "\n";

		if      (std::strcmp(message, "pause") == 0)
			std::cout << "Application paused.\n";

		else if (std::strcmp(message, "resume") == 0)
			std::cout << "Application resumed.\n";

		else if (std::strcmp(message, "pausedir") == 0)
			std::cout << "Paused watching directory.\n";

		else if (std::strcmp(message, "resumedir") == 0)
			std::cout << "Resumed watching directory.\n";

		else if (std::strcmp(message, "exit") == 0)
		{
			std::cout << "Exiting application.\n";
			isEnded = true;
		}
		else std::cout << "Invalid command.\n";

		// Perform some action based on the message
	}

}

void WriteToPipe(char* arg)
{
	// Open an existing named pipe with a name
	HANDLE hStdOut = CreateFile(L"\\\\.\\pipe\\my_pipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	// Check if the pipe is valid
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error: failed to open pipe.\n";
		return;
	}

	// Write to the pipe
	DWORD bytesWritten;
	BOOL result = WriteFile(hStdOut, arg, BUFFERSIZE, &bytesWritten, NULL);

	// Check if the write operation succeeded
	if (!result)
	{
		std::cout << "Error: failed to write to pipe.\n";
		CloseHandle(hStdOut);
		return;
	}
	// Close the pipe handle
	std::cout << "Successfully wrote to pipe. Closing write handle.\n";
	CloseHandle(hStdOut);
}

int main(int argc, char *argv[])
{
	
	// Check if the program is the first or the second instance
	if (!isFirstInstance())
	{
		// Take command line arguements
		if (argc == 2)
		{
			if (!verifyCommands(argv[1]))
				return 0;

			if (std::strlen(argv[1]) <= BUFFERSIZE)
			{
				WriteToPipe(argv[1]);
			}

		}
		
		return 0;
	}

	// Create a named pipe with a name and a maximum message size
	HANDLE hStdIn = CreateNamedPipe(L"\\\\.\\pipe\\my_pipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, BUFFERSIZE, BUFFERSIZE, 0, NULL);

	// Check if the pipe is valid
	if (hStdIn == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error: failed to create pipe." << GetLastError() << "\n";
		return 0;
	}

	while (!isEnded)
	{
		ReadFromPipe(hStdIn);
	}

	/*InitiateApp();

	setting.log_path = "./Logs/" + utils::getDate() + " log.txt";


	while (true)
	{
		monitorDirectory();
	}*/

	// Close the pipe handle
	std::cout << "Closing read handle.\n";
	CloseHandle(hStdIn);

    std::cout << "Program Ended!\n";
}

bool InitiateApp()
{
	
	getApplicationSetting();
	verifyApplicationSettings();


	return true;
}


void monitorDirectory()
{

	while (true)
	{
		std::this_thread::sleep_for(setting.waiting);

		// Check if a file was created

		for (auto& file : std::filesystem::recursive_directory_iterator(setting.input_dir))
		{
			// File Creation

			// If not regular file then continue to the next file. 
			if (!std::filesystem::is_regular_file(file.path()))
				continue;
			try
			{
				if (file.path().extension() != ".pdf") {
					moveFailedFile(file.path());
					utils::writeLogFile("Failed - not a pdf file", file.path().filename().string(), setting.log_path);
					continue;
				}

				bool printStatus = readAndPrint(file.path());

				// Move the file to output folder.
				if (printStatus)
				{
					moveSuccessFile(file.path());
					utils::writeLogFile("Success", file.path().filename().string(), setting.log_path);
				}
				else // Move the file to error folder.
				{
					moveFailedFile(file.path());
					utils::writeLogFile("Failed to print", file.path().filename().string(), setting.log_path);
				}

			}
			catch (const std::exception &err)
			{
				std::cout << err.what();
			}

		}
	}



}
bool readAndPrint(const std::filesystem::path &path)
{
	// Read the file
	std::streampos docLength = 0;
	char* buffer = utils::readFile(path, docLength);

	// Print the file
	bool printStatus = false;

	if (buffer)
		printStatus = utils::printFile(setting.printer, path.filename().string(), buffer, docLength);

	delete[] buffer;

	return printStatus;
}


void moveSuccessFile(const std::filesystem::path &path) {

	try
	{
		// Get the file name
		std::filesystem::path fileName = path.filename();

		std::filesystem::path outputDir = setting.output_dir;
		std::filesystem::path targetDir = outputDir / fileName;

		// If the output folder does not exist, then create one.
		std::filesystem::create_directories(outputDir);

		// Copy the file from input to the output folder. Override the file in the output folder.

		std::filesystem::copy_file(path, targetDir, std::filesystem::copy_options::overwrite_existing);


		// Remove the file from input folder.
		std::filesystem::remove(path);

		std::cout << "Moved the document: " << fileName << "\n";
	}
	catch (const std::exception &err )
	{
		std::cout << err.what();
	}

}

void moveFailedFile(const std::filesystem::path& path) {

	try
	{
		// Get the file name
		std::filesystem::path fileName = path.filename();

		std::filesystem::path outputDir = "./ERROR/";
		std::filesystem::path targetDir = outputDir / fileName;

		// If the output folder does not exist, then create one.
		std::filesystem::create_directories(outputDir);

		// Copy the file from input to the output folder. Override the file in the output folder.

		std::filesystem::copy_file(path, targetDir, std::filesystem::copy_options::overwrite_existing);


		// Remove the file from input folder.
		std::filesystem::remove(path);

		std::cout << "Moved to ERROR dir: " << fileName << "\n";
	}
	catch (const std::exception& err)
	{
		std::cout << err.what();
	}

}

bool getApplicationSetting()
{
	std::cout << "Fetching application settings.\n";

	std::ifstream file;
	file.open("./config.txt");

	if (!file)
	{
		// Write default settings
		writeDefaultApplicationSettings();
		return true;
	}

	std::string currentText;

	while (std::getline(file, currentText))
	{
		std::pair<std::string, std::string> parameters = utils::parseRawFileContent(currentText);

		if (parameters.first == "input_directory")
			setting.input_dir = parameters.second;
		else if (parameters.first == "output_directory")
			setting.output_dir = parameters.second;
		else if (parameters.first == "default_printer")
		{
			// Get the size of the printer name.
			int len = parameters.second.size();

			// Getting reference
			auto& defPrinter = setting.printer;

			// Allocate enough memory to hold printer name
			defPrinter = new TCHAR[len + 1];
			defPrinter[len] = 0;

			// Copy the string printer name to the memory allocated
			std::copy(parameters.second.begin(), parameters.second.end(), defPrinter);

		}
		else if (parameters.first == "waiting_time")
		{
			// Empty string cannot be assigned to std::chrono::milliseconds.
			if (parameters.second.empty())
				setting.waiting = std::chrono::milliseconds(3000);

			// Are all integer values
			if (std::all_of(parameters.second.begin(), parameters.second.end(), ::isdigit))
				setting.waiting = std::chrono::milliseconds(std::stoi(parameters.second));
		}
		else break;
	}

	file.close();

	return true;
}

bool writeApplicationSetting()
{
	std::cout << "Saving application settings.\n";

	std::ofstream file;

	file.open("./config.txt");

	file << "input_directory = " << setting.input_dir << '\n';
	file << "output_directory = " << setting.output_dir << '\n';

	// First convert it to wstring from TCHAR*
	std::wstring wstr(setting.printer);
	// Conver to string from wstring
	file << "default_printer = " << std::string(wstr.begin(), wstr.end()) << '\n';
	file << "waiting_time = " << setting.waiting.count() << '\n';


	file.close();

	return true;
}
bool writeDefaultApplicationSettings()
{

	std::cout << "Writing default settings!!!\n";

	setting.input_dir = ".\\IN";
	setting.output_dir = ".\\OUT\\";
	setting.printer = utils::getSystemDefaultPrinter();
	setting.waiting = std::chrono::milliseconds(3000);

	return writeApplicationSetting();
}

bool verifyApplicationSettings()
{
	std::cout << "Verifying application settings.\n";
	
	bool hasChanged = false;

	// Check if input directory exist
	if (!std::filesystem::exists(setting.input_dir))
	{
		std::filesystem::create_directory(".\\IN");
		setting.input_dir = ".\\IN";
		hasChanged = true;
	}
	if (!std::filesystem::exists(setting.output_dir))
	{
		std::filesystem::create_directory(".\\OUT\\");
		setting.output_dir = ".\\OUT\\";
		hasChanged = true;
	}
	if (setting.waiting < std::chrono::milliseconds(1000))
	{
		setting.waiting = std::chrono::milliseconds(3000);
		hasChanged = true;
	}
	if (!utils::verifyPrinter(setting.printer))
	{
		setting.printer = utils::getSystemDefaultPrinter();
		hasChanged = true;
	}

	if (hasChanged)
		writeApplicationSetting();

	return hasChanged;
}


/*HANDLE hSingleInstanceMutex = CreateMutex(NULL, TRUE, L"ASAPV2");

if (hSingleInstanceMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
{
	HWND existingApp = FindWindow(0, L"ASAPV2");
	if (existingApp) {
		SetForegroundWindow(existingApp);
	}

	return 0;
}*/