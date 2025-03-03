#include "Hash.h"

#define _LOG(args) std::cout << args << std::endl
#define _NewLine(count) for (int i = 1; i < count; i++) { _LOG('\n'); }

namespace Utils
{
	void Wait()
	{
		std::cout << "\nPress enter to continue...";
		std::cin.get();
	}
}

int main()
{
	Hash::HASHTABLE HT;

	//
}


void Test()
{

	Hash::HASHTABLE HT;

	if (HT.isEmpty())
		_LOG("HASH TABLE IS EMPTY...");


	else _LOG("SOMETHING IS NOT RIGHT...");

	_NewLine(2);

	HT.Insert(1, "Mikul");
	HT.Insert(2, "Bhavik");
	HT.Insert(3, "Nirav");
	HT.Insert(4, "Harshad");
	HT.Insert(5, "Yash");
	HT.Insert(6, "Mann");
	HT.Insert(7, "Millan");
	HT.Insert(8, "Preet");
	HT.Insert(9, "Deep");
	HT.Insert(10, "Kunjal");
	HT.Insert(11, "Rohit");
	HT.Insert(12, "Kishan");
	HT.Insert(13, "Shyam");

	_NewLine(2);
	HT.PrintTable();

	HT.Insert(3, "Divyesh");

	_NewLine(2);

	HT.PrintTable();

	_NewLine(2);

	HT.Remove(4);

	_NewLine(2);

	HT.PrintTable();

	_NewLine(2);

	if (HT.isEmpty())
		_LOG("HASH TABLE IS EMPTY...");

	else _LOG("HASH TABLE IS NOT EMPTY...");

	_NewLine(2);

	std::string found = HT.Search(4);

	_LOG("Found: " + found);

	Utils::Wait();

}