#include <vector>
#include <string>
#include <algorithm>
#include <functional>

#include "classes.h"
#include "Recursion.h"
#include "Cell.h"
#include "TemplateClass.h"
#include "Square.h"
#include "Matrix.h"

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';



int matrices()
{
	std::vector<std::vector<int>> nums(10);

	for (auto& n : nums)
		n.resize(4);

	int n = 1;
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = 0; j < nums[i].size(); j++)
		{
			nums[i][j] = 10 + (n - 1) * 10;
			n++;
		}
	}

	for (auto& n : nums)
	{
		std::cout << "[ ";
		for (auto& c : n)
			std::cout << c << ", ";

		std::cout << "]\n";

	}

	_New(2);

	matrix<float> dimension{ 10, 4 };

	matrix<int> arr{ nums };

	std::cout << "Num of rows: " << dimension.numOfRows() << '\n';
	std::cout << "Num of cols: " << dimension.numOfCols() << '\n';

	_New(2);
	std::cout << "Num of rows(arr): " << arr.numOfRows() << '\n';
	std::cout << "Num of cols(arr): " << arr.numOfCols() << '\n';

	std::cout << "Element at arr[3][2]: " << arr[3][2] << '\n';

	_Wait();
	return 0;
}


/*
	FUNCTION OBJECT

*/


template<typename Object, typename Comparator>
const Object& findMax(std::vector<Object>& obj, Comparator cmp)
{
	int maxIndex = 0;

	for (int i = 1; i < obj.size(); i++)
	{
		//if (cmp(obj[maxIndex], obj[i]))
		if (cmp.isLessThan(obj[maxIndex], obj[i]))
			maxIndex = i;
	}

	return obj[maxIndex];

}

template<typename Object>
const Object& findMax(std::vector<Object>& obj)
{
	//return findMax(obj, std::less<Object>{});
	return obj[0];
}

template<typename Object, typename Comparator>
void sort(std::vector<Object>& obj, Comparator cmp)
{
	for (int i = 0; i < obj.size(); i++)
	{
		for (int j = 0; j < obj.size() - 1; j++)
		{
			if (!cmp.isLessThan(obj[j], obj[j + 1]))
			{
				std::string temp = std::move(obj[j]);
				obj[j] = std::move(obj[j + 1]);
				obj[j + 1] = std::move(temp);
			}
		}
	}
}

int my_strcmp(const char* lhs, const char* rhs)
{
	if ((int)lhs[0] > (int)rhs[0]) return 1;
	else if ((int)lhs[0] == (int)rhs[0]) return 0;
	else return -1;
}

class CaseInsensitiveCompare
{
public:
	bool isLessThan(const std::string& lhs, const std::string& rhs)
	{
		//std::for_each(lhs.begin(), lhs.end(), [](char& c) { c = ::tolower(c); });
		//std::for_each(rhs.begin(), rhs.end(), [](char& c) { c = ::tolower(c); });

		// Not efficient to copy lhs and rhs

		std::string str1 = lhs;
		std::string str2 = rhs;

		std::for_each(str1.begin(), str1.end(), [](char& c) { c = ::tolower(c); });
		std::for_each(str2.begin(), str2.end(), [](char& c) { c = ::tolower(c); });

		return (my_strcmp(str1.c_str(), str2.c_str()) < 0); // User defined function (my_strcmp)
		//return ( std::strcmp( lhs.c_str(), rhs.c_str() ) < 0); // using strcmp from standard library
	}

};

std::ostream& operator << (std::ostream& out, const std::vector<std::string>& cont)
{
	out << "[ ";
	for (auto& item : cont)
		out << item << ", ";

	out << "]";

	return out;

}

int usingFunctionObejct()
{
	std::vector<std::string> strs = { "MIKUL", "Harshad", "bhavik", "NiRav", "diVYesH", "YasH" };

	std::cout << "Largest: " << findMax(strs, CaseInsensitiveCompare{  }) << '\n';
	//std::cout << "Largest (functional lib): " << findMax(strs) << '\n';

	_New(2);

	std::cout << "Original: ";

	std::cout << strs;

	_New(2);

	sort(strs, CaseInsensitiveCompare{ });

	std::cout << "Sorted: ";

	std::cout << strs;

	_Wait();
	return 0;
}






const Square& findMax(const std::vector<Square>& cont)
{
	int maxIndex = 0;

	for (int i = 0; i < cont.size(); i++)
	{
		if (cont[maxIndex] < cont[i])
			maxIndex = i;
	}

	return cont[maxIndex];
}

std::ostream& operator << (std::ostream& out, const Square& sqr)
{
	sqr.print(out);
	return out;
}

int FindingLargestSquare()
{
	std::vector<Square> squares = { Square{ 10.0 }, Square{ 320.0 }, Square{ 30.0 }, Square{ 10.0 } };


	std::cout << "Largest Square: " << findMax(squares) << '\n';

	_Wait();
	return 0;
}

int TemplateClass()
{
	Value<int> val1;
	Value<float> val2{ 32.632f };
	Value<std::string> val3{ "Hello" };
	Value<Cell> cell{ Cell{ 10 } };
	Value<Cell> cell2 = Value<Cell>{ std::move(Cell{ 20 }) };



	val1.setValue(100);

	val3.setValue(val3.getValue() + " world!");

	std::cout << "Val1: " << val1.getValue() << '\n';
	std::cout << "Val2: " << val2.getValue() << '\n';
	std::cout << "Val3: " << val3.getValue() << '\n';
	std::cout << "Cell: " << cell.getValue().getValue() << '\n';
	std::cout << "Cell2: " << cell2.getValue().getValue() << '\n';

	_Wait();
	return 0;
}


/*
	THE BIG FIVE
		- Destructor
		- Copy Constructor
		- Move Constructor
		- Copy Assignment Operator =
		- Move Assignment Operator =
*/

int BIGFIVE()
{
	Cell c1{ 10 };

	Cell c2 = c1;

	Cell c3 = Cell{ 100 };

	Cell c4 = std::move(c3);

	std::string name = "Mikul";

	std::cout << "Letter: " << name[2] << '\n';


	std::cout << "Num1: { Value: " << c1.getValue() << ", Address: " << c1.getAdd() << " }\n";
	std::cout << "Num1: { Value: " << c2.getValue() << ", Address: " << c2.getAdd() << " }\n";
	//std::cout << "Num1: { Value: " << c3.getValue() << ", Address: " << c3.getAdd() << " }\n";

	_Wait();
	return 0;
}

int NumberPlaying()
{
	Number num1{ 1, 100, 3000 };

	Number num2{ num1 };

	Number num3 = num2;

	Number num4 = Number(2, 200, 5000);

	std::cout << "Num1: " << num1.getID() << '\n';
	std::cout << "Num2: " << num2.getID() << '\n';
	std::cout << "Num3: " << num3.getID() << '\n';
	//std::cout << "Num4: " << num4.getID() << '\n';

	_Wait();
	return 0;
}






void swap(std::vector<Number>& cont1, std::vector<Number>& cont2)
{
	// Makes 3 copies
	std::vector<Number> temp = cont1;

	cont1 = cont2;
	cont2 = temp;

}

void swap2(std::vector<Number>& cont1, std::vector<Number>& cont2)
{
	std::vector<Number> temp = static_cast<std::vector<Number>&&>(cont1);

	cont1 = static_cast<std::vector<Number>&&>(cont2);
	cont2 = static_cast<std::vector<Number>&&>(temp);
}

void swap3(std::vector<Number>& cont1, std::vector<Number>& cont2)
{
	std::vector<Number> temp = std::move(cont1);

	cont1 = std::move(cont2);
	cont2 = std::move(temp);
}

void LogNumbers(const char* cont_name, const std::vector<Number>& cont)
{
	std::cout << cont_name << ": [ ";
	for (auto& item : cont)
		std::cout << item.getID() << ", ";

	std::cout << "]\n";
}

int SwappingTwoVectors()
{
	std::vector<Number> cont1;
	std::vector<Number> cont2;

	cont1.reserve(3);
	cont2.reserve(3);

	cont1.emplace_back(1, 10, 20);
	cont1.emplace_back(2, 30, 40);
	cont1.emplace_back(3, 50, 60);

	cont2.emplace_back(9, 100, 200);
	cont2.emplace_back(8, 300, 400);
	cont2.emplace_back(7, 500, 600);

	_New(2);

	LogNumbers("Original cont1", cont1);

	_New(1);

	LogNumbers("Original cont2", cont2);

	_New(2);

	//swap(cont1, cont2); // Makes 3 copies
	//swap2(cont1, cont2); // Swapping by 3 moves (Using static_cast)

	swap3(cont1, cont2); // Swapping by 3 move (Using std::move)

	std::cout << "After swap.\n\n";

	LogNumbers("Modified cont1", cont1);

	_New(1);

	LogNumbers("Modified cont2", cont2);

	_Wait();

	return 0;
}


/*
	lvalue AND rvalue
	lvalue AND rvalue references
*/

int& findMax(int arr[], int size)
{
	int index = 0;
	int max = 0;
	for (int i = 0; i < size; i++)
		if (arr[i] > max)
		{
			max = arr[i];
			index = i;
		}

	return arr[index];
}

std::string findMax(const std::string& str1, const std::string& str2)
{
	if (str1.size() > str2.size() || str1.size() == str2.size())
		return str1;

	return str2;
}

std::string findMax(const std::string&& str1, const std::string&& str2)
{
	if (str1.size() > str2.size() || str1.size() == str2.size())
		return str1;

	return str2;
}

int lvalue_Application()
{
	// Application of lvalue

	// 1. aliasing complicated names

			/*
					auto& whichList = theLists[myhash(x, theLists.size())];
					if (find(begin(whichList), end(whichList), x) != end(whichList))
						return false;
					whichList.push_back(x);
			*/

			// 2. Range for loops

					/*
					====FROM :
						for (auto x : values)
							++x;

					====> TO :
						for (auto & x : values)
							++x;


					*/

					// 3. Avoiding a copy

							/*
							 ==== FROM :

								auto x = findMax(array);

							====> TO:
								auto & x = findMax(array);

								if array contains elements that are large and you just want the value.

							*/

	int arr[10] = { 5, 5, 4, 8, 10, 7, 9, 6, 45, 4 };

	std::string str1 = "12345";
	std::string str2 = "1234568";

	int& max = findMax(arr, 10);

	std::cout << "Original: [ ";
	for (int i = 0; i < 10; i++)
		std::cout << arr[i] << ", ";

	std::cout << "]";

	_New(1);
	std::cout << "Max: " << max;
	_New(1);

	max = 99;

	std::cout << "Modified: [ ";
	for (int i = 0; i < 10; i++)
		std::cout << arr[i] << ", ";

	std::cout << "]";

	_New(2);

	std::cout << "lvalue: " << findMax(str1, str2) << "\n";
	std::cout << "rvalue: " << findMax("12345689", "43332") << "\n";

	_Wait();

	return 0;
}

int lvalueAndrvalue()
{
	{
		std::vector<std::string> arr(3);

		const int x = 2;
		int y = 2;
		int z = x + y;
		std::string str = "Hello";

		std::vector<std::string>* ptr = &arr;

		/*
				arr, x, y, z, str, *ptr, ptr, arr[x], &x, (*ptr)[x]

				ABOVE ARE ALL 'lvalue'

				if you have a name for a variable, it is lvalue regardless of whether it is modifiable or not.

		 */

		 /*
				 2, x + y,  "Hello", str.substr(0, 1)

				 ABOVE ARE ALL 'rvalue'

				 2 AND "Hello" are rvalue because they are literals
		 */
	}

	// lvalue references

	std::string str = "hell";

	std::string& rstr = str;

	rstr += 'o';

	std::cout << "Str: " << str;

	_New(1);
	std::cout << "rstr: " << rstr;

	_New(1);

	std::cout << "str == rstr: " << std::boolalpha << (str == rstr);

	_New(1);

	std::cout << "&str == &rstr: " << std::boolalpha << (&str == &rstr);

	_New(1);

	//std::string& value = "Value"; // Illegal lvalue initialization
	//std::string& value =  str + "d"; // Illegal lvalue initialization
	//std::string& value = str.substr(0, 4); // Illegal lvalue initialization


	// rvalue references

	std::string something = "something";

	std::string&& good = "good";                       // Legal
	std::string&& good1 = something + " new";          // Legal
	std::string&& good2 = something.substr(0, 4);      // Legal

	std::cout << good;

	_New(1);

	_Wait();
	return 0;
}

/*
	VECTORS AND STRINGS
*/

int vecotrAndString()
{
	//std::vector<int> numbers(100); // Creates vector with 100 elements (Constructor that takes size)
	//std::vector<int> numbers{ 100, 200, 300 }; // Creates vector with size 3 and initializes with values in parameters
	std::vector<int> numbers = { 100, 200, 300, 400, 500, 600, 700 }; // Same as line before.

	std::vector<int> someNums = { 1, 2, 3, 4, 5, 6, 7, 8 };

	std::vector<int>* ptr = &someNums;

	std::cout << "someNums: " << &someNums[0] << '\n';
	std::cout << "Ptr: " << ptr;
	_New(2);

	std::cout << "Values someNums pointed by ptr: \n";

	for (auto& val : *ptr)
		std::cout << val << ", ";

	_New(2);


	for (int i = 0; i < numbers.size(); i++)
		numbers[i] = i + 1;

	for (auto& num : numbers)
		std::cout << num << ", ";

	_New(2);

	std::string name = "Mikul";
	std::string name2{ "Bhavik" };

	std::string name3 = { "Harshad" };
	std::string name4("Divyesh");

	std::cout << name << "\n";
	std::cout << name2 << "\n";
	std::cout << name3 << "\n";
	std::cout << name4 << "\n";
	std::cout << name4.size() << "\n";


	_Wait();
	return 0;
}





/*
	CLASSES HEADER FILE

	----NUMBER (class)

*/

void doSomething(const Number& obj)
{
	std::cout << "Doing nothing.\n";
}

int classesExercise()
{
	Number num{}; // 0 Parameter constructor
	Number num1(); // THIS IS SAME AS FUNCTION CALL WHICH RETURNS 'Number' datatype.
	Number num2(5);
	Number num3(10, 20);


	/*
	*
	* BELOW ARE LEGAL INCASE OF USE OF POINTER
				Number* ptr = nullptr;

				ptr = new Number();
				ptr = new Number{};
				ptr = new Number;

	*/

	//Number num4 = 320; Legal if constructor with one parameter is not explicit

	Number num5{ 40, 80 };

	num3 = 100;
	Number temp = num3;

	doSomething(temp);

	std::cout << "Num5: " << num5.getValue() << ", " << num5.getSum() << std::endl;

	std::cout << "Num3: " << num3.getValue() << ", " << num3.getSum() << std::endl;
	std::cout << "Temp: " << temp.getValue() << ", " << temp.getSum() << std::endl;




	_Wait();

	return 0;
}







/*
	RECURSION FUNCTIONS USAGE
*/

int f(int x); // Recursive function
int bad(int x); // Non terminating recursive function

void printNum(int x); // Use recursive function to print numbers( x >= 0 )

int RecursionExercise()
{
	int value = 3; // Values less than 0, will create infinite function calls.
	int value2 = 0; // Values less than or greater than 0, will make the function non-terminating 

	int result = f(value);

	int result2 = bad(value2);

	std::cout << "Result: " << result << std::endl;
	std::cout << "Result2: " << result2 << std::endl;

	std::cout << "\n\n";

	printNum(4320);

	std::cout << "\n\n";



	std::cout << "Press enter to continue.";
	std::cin.get();

	return 0;
}

