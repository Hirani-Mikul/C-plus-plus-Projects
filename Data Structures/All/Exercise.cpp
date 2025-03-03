#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matrix.h"
#include "Timer.h"
#include "MoreQuestions.h"

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';


void factorial(int n, int & result)
{
	if (n == 0)
	{
		//std::cout << "******************\n";
		result++;
		return;
	}

	for (int i = 0; i < n; i++)
		factorial(n - 1, result);
}

int main()
{
	int n = 5;
	int result = 0;

	factorial(n, result);

	_New(2);
	std::cout << n << "! : " << result << "\n";

	_Wait();
	return 0;
}

int BinarySearch_People()
{
	std::vector<Person> peopleVec;
	peopleVec.reserve(6);

	peopleVec.emplace_back(1, 20, "Mikul Hirani", 'M', 5.77f);
	peopleVec.emplace_back(2, 19, "Devanshi Vaghani", 'F', 5.32f);
	peopleVec.emplace_back(3, 18, "Divyesh Dabasia", 'M', 6.00f);
	peopleVec.emplace_back(4, 18, "Yash Vekaria", 'M', 5.10f);
	peopleVec.emplace_back(5, 21, "Bhavik Hirani", 'M', 5.33f);
	peopleVec.emplace_back(6, 20, "Nirav Rabadia", 'M', 5.93f);

	OrderedCollection<Person> People{ peopleVec };

	Person p = People[3];
	Person p2{ 2, 19, "Devanshi Vaghani", 'F', 5.32f};

	std::cout << "No. of people: " << People.getSize() << '\n';

	int index = People.search(p2);

	std::cout << "Position: " << index << '\n';

	std::cout << "To Search: " << p2.getName() << '\n';
	std::cout << "Found: " << ( index >= 0 ? People[index].getName() : "Not found.") << '\n';

	_Wait();
	return 0;
}

int BinarySearch_Ex1()
{
	std::vector<int> numVec(100000);

	for (int i = 1; i <= numVec.size(); i++)
		numVec[i - 1] = i;

	OrderedCollection<int> nums{ numVec };


	std::cout << "Size of collection: " << nums.getSize() << '\n';
	//std::cout << "Collection: ";
	//nums.print();

	_New(2);

	int value = 3232;

	std::cout << "Position of " << value << ": " << nums.search(value) << '\n';

	_Wait();
	return 0;
}

int Q1_14()
{
	std::vector<Person> peopleVec;
	peopleVec.reserve(6);

	peopleVec.emplace_back(1, 20, "Mikul Hirani", 'M', 5.77f);
	peopleVec.emplace_back(2, 19, "Devanshi Vaghani", 'F', 5.32f);
	peopleVec.emplace_back(3, 18, "Divyesh Dabasia", 'M', 6.00f);
	peopleVec.emplace_back(4, 18, "Yash Vekaria", 'M', 5.10f);
	peopleVec.emplace_back(5, 21, "Bhavik Hirani", 'M', 5.33f);
	peopleVec.emplace_back(6, 20, "Nirav Rabadia", 'M', 5.93f);


	std::cout << "Original ID's: [ ";
	for (auto& p : peopleVec)
	{
		int id = p.getAge();
		std::cout << id << ", ";

	}

	std::cout << "]";

	_New(2);
	

	OrderedCollection<Person> People{ peopleVec };

	std::cout << "No. of people: " << People.getSize() << '\n';

	std::cout << "Max: " << People.findMax() << '\n';
	std::cout << "Min: " << People.findMin() << '\n';
	
	_New(2);

	std::cout << "People: ";

	People.print();

	_New(2);

	People[0].setAge(100);

	std::cout << "After change ID's: [ ";
	for (auto& p : peopleVec)
	{
		int id = p.getAge();
		std::cout << id << ", ";

	}
	std::cout << "]";
	_New(2);

	
	_Wait();
	return 0;
}

int Q1_13()
{
	std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	Collection<int> collection{ nums };

	std::cout << "Is collection empty: " << std::boolalpha << collection.isEmpty() << '\n';
	std::cout << "Size of collection: " << collection.getSize() << '\n';

	std::cout << "collection: ";
	collection.print();

	_New(2);

	collection.insert(99);
	collection.remove(4);
	collection.remove(7);
	collection.remove(1);

	std::cout << "collection: ";
	collection.print();
	_New(1);
	std::cout << "Size of collection: " << collection.getSize() << '\n';

	_New(2);

	int val = 4;
	std::cout << "Contains " << val << ": " << collection.contains(val);

	_New(2);
	collection.makeEmpty();

	std::cout << "Is collection empty: " << std::boolalpha << collection.isEmpty() << '\n';




	_Wait();
	return 0;
}

int vecAlgorithm()
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };

	for (auto& v : vec)
		std::cout << v << ", ";

	_New(2);
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](int n) { return n == 2; }), vec.end());

	for (auto& v : vec)
		std::cout << v << ", ";

	_New(2);

	auto i = std::find(vec.begin(), vec.end(), 5);

	if (i == vec.end())
		std::cout << "Element not found.\n";
	else {
		std::cout << "Element is at position: " << (i - vec.begin()) << '\n';
	}

	_Wait();
	return 0;
}

void permute(const std::string& str)
{
	std::cout << str << "\n";
}
void permute(std::string& str, int low, int high)
{
	// base case
	if (low == high) std::cout << str << "\n";

	else {
		for (int i = low; i <= high; i++)
		{
			std::swap(str[low], str[i]); // abc abc

			permute(str, low + 1, high); // 

			std::swap(str[low], str[i]); //
		}
	}

}

int Q3()
{
	{

		std::string str = "abc";

		int high = str.length() - 1;
		permute(str, 0, high);
	}


	_Wait();

	return 0;
}

int Q2()
{
	int wordSize = 4;
	std::string str = "gamgamebirdxkillameysame", word, text;

	std::ifstream dictonary("dictonary.txt");

	{
		Timer timer{ "Search Word" };

		for (int i = 0; i < str.length(); i++)
		{
			if (i == str.length() - (wordSize - 1)) break;
			text = str.substr(i, wordSize);

			while (!dictonary.eof())
			{
				dictonary >> word;

				if (word == text)
				{
					std::cout << text << '\n';
					break;
				}
			}

			dictonary.clear();
			dictonary.seekg(0, std::ios::beg);

		}
	}


	_Wait();
	return 0;
}












/*
	QUESTION 1
	FINDING OUT HOW MUCH TIME DOES IT TAKE FOR K = N / D;
	DEPENDING ON DIFFERENT VALUES OF N.
*/




int Q1()
{
	float N = 103230.4321f;
	float D = 2.0f;

	{
		Timer timer{ "First" };
		std::cout << "N = " << std::fixed << std::setprecision(4) << N << ": ";
		float K = N / D;
	}
	N = 2.0f;
	{
		Timer timer{ "Second" };
		std::cout << "N = " << std::fixed << std::setprecision(4) << N << ": ";
		float K = N / D;
	}
	N = 2232.43242f;
	{
		Timer timer{ "Third" };
		std::cout << "N = " << std::fixed << std::setprecision(4) << N << ": ";
		float K = N / D;
	}
	N = 9992332.32f;
	{
		Timer timer{ "Forth" };
		std::cout << "N = " << std::fixed << std::setprecision(4) << N << ": ";
		float K = N / D;
	}

	{
		Timer timer{ "SecondLast" };
		float K = N / D;
		float sin = std::sin(0.23);
		float sqr = std::sqrtf(N);

	}

	{
		Timer timer{ "Last" };

		std::vector<std::vector<int>> nums(10);

		for (auto& n : nums)
			n.resize(4);

		int n = 1;
		for (int i = 0; i < nums.size(); i++)
		{
			for (int j = 0; j < nums[i].size(); j++)
			{
				nums[i][j] = std::sqrt(10 + (n - 1) * 10);
				n++;
			}
		}

		_New(2);

		matrix<float> dimension{ 10, 4 };

		matrix<int> arr{ nums };
	}

	_Wait();

	return 0;
}