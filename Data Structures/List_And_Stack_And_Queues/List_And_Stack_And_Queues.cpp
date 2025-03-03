#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MyList.h"
#include "MyList_2.h"
#include "MyVector.h"
#include "Classes.h"
#include "Stack_LinkedList.h"
#include "Stack.h"
#include "Queue.h"

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

#include <stdlib.h>


int main()
{
	Vector<int> nums{ 10 };

	nums.push_back(5);
	nums.push_back(6);
	nums.push_back(7);
	nums.push_back(3);
	nums.push_back(1);

	int index = 3;
	std::cout << "Element at index " << index << ": " << nums[index];

	_New(2);

	std::cout << "Original: \n";
	for (auto& i : nums)
	{
		std::cout << i << ", ";
	}
	_New(2);

	nums.insert(3, 100);

	std::cout << "Inserted 100 at index 3: \n";
	for (auto& i : nums)
	{
		std::cout << i << ", ";
	}
	_New(2);

	nums.erase(2);

	std::cout << "Erased element at index 2: \n";
	for (auto& i : nums)
	{
		std::cout << i << ", ";
	}
	_New(2);

	_Wait();
	return 0;
}


/*
	MERGE & SORT

	USING DIVIDE AND CONQUER
*/
void merge(int * arr, int start, int mid, int end)
{
	int* temp = new int[end - start + 1];

	int i = start, j = mid + 1, k = 0;

	while (i <= mid && j <= end)
	{
		if (arr[i] <= arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}

	// Add rest of the values from left sub-array into the result
	while (i <= mid)
	{
		temp[k++] = arr[i++];
	}

	// Add rest of the values from right sub-array into the result
	while (j <= end)
	{
		temp[k++] = arr[j++];
	}

	for (i = start; i <= end; i++)
		arr[i] = temp[i - start];

	delete[] temp;
}

void mergeSort(int* arr, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

int Recursive_Merge_And_Sort()
{
	int arr[10] = { -10, 4, -80, 1, 6, 2, -122, 55, 0, -163 };

	int size = 10;

	int start = 0;
	int end = size - 1;

	std::cout << "Before: \n[ ";
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i];
		if (i != size - 1) std::cout << ", ";
	}
	std::cout << " ]";

	mergeSort(arr, start, end);

	_New(2);
	std::cout << "After sorting: \n[ ";

	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i];
		if (i != size - 1) std::cout << ", ";
	}
	std::cout << " ]";

	_New(2);

	_Wait();
	return 0;
}



void printSet_V2(const std::vector<int>&cont)
{
	for (auto& x : cont)
		std::cout << x << ", ";

}

int EX_3_6_VECTOR()
{
	int N = 5000;
	int M = 6;
	std::vector<int> people;

	people.reserve(N);

	for (int i = 0; i < N; i++)
		people.push_back( i + 1 );

	printSet_V2(people);

	int i = 0;

	while (people.size() > 1)
	{

		i = (i + M) % people.size();

		auto itr = people.begin() + i;

		people.erase(itr);

	}

	_New(2);

	std::cout << "Winner: " << people.back() << '\n';


	_Wait();
	return 0;
}

void printSet(const MyList::List<int>& cont)
{
	for (int i = 0; i < cont.size(); i++)
		std::cout << *cont[i] << ", ";
}

int EX_3_6_LINKED_LIST()
//int main()
{
	int N = 5000;
	int M = 6;

	MyList::List<int> people;

	for (int i = 0; i < N; i++)
	{
		people.push_back(i + 1);
	}

	printSet(people);

	_New(2);

	int i = 0;

	while (people.size() > 1)
	{
		i = (i + M) % people.size();

		auto itr = people[i];

		people.erase(itr);
	}

	printSet(people);

	_New(2);

	_Wait();
	return 0;
}



std::ostream& operator << (std::ostream& out, const Person& p)
{
	out << "{ ";
	out << "_id: " << p.getId() << ", ";
	out << "Name: " << p.getName() << ", ";
	out << "Gender: " << p.getGender();
	out << " }";
	return out;
}

template<typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x)
{

	while (start != end)
	{
		if (*start == x)
			return start;

		start++;
	}
	return end;
}

int EX_3_3()
{
	MyList::List<Person> people;

	Person p{ 4, "Devanshi Vaghani", 19, 'F' };
	Person p2{ 4, "Preet Patel", 18, 'M' };

	people.push_back(Person{ 1, "Mikul Hirani", 20, 'M' });
	people.push_back(Person{ 2, "Bhavik Hirani", 20, 'M' });
	people.push_back(Person{ 3, "Nirav Rabadia", 20, 'M' });
	people.push_back(p);
	people.push_back(p2);
	//people.push_back(Person{ 4, "Devanshi Vaghani", 19, 'F' });
	people.push_back(Person{ 5, "Divyesh Dabasia", 19, 'M' });
	people.push_back(Person{ 6, "Mann Patel", 18, 'M' });
	people.push_back(Person{ 7, "Harshad Vekaria", 19, 'M' });
	people.push_back(Person{ 8, "Yash Vekaria", 18, 'M' });

	auto start = people[4];
	auto last = people[7];

	auto found = find(start, last, p2);

	if (found != last)
		std::cout << "Found: " << *found << '\n';
	else std::cout << "Person not found.\n";

	_Wait();
	return 0;
}

int EX_3_2()
{
	MyList::List<Person> people;

	people.push_back(Person{ 1, "Mikul Hirani", 20, 'M' });
	people.push_back(Person{ 4, "Devanshi Vaghani", 19, 'F' });
	people.push_back(Person{ 5, "Divyesh Dabasia", 19, 'M' });


	std::cout << "Before swap.\n\n";

	std::cout << people.front();
	_New(1);
	std::cout << people.back();

	MyList::List<Person>::iterator itr = people[1];

	people.swap(itr);

	_New(2);
	std::cout << "After swap.\n\n";

	std::cout << people.front();
	_New(1);
	std::cout << people.back();


	_Wait();
	return 0;
}

void printLots(const List<Person>& cont, List<int>& pos)
{
	while (!pos.empty())
	{
		std::cout << cont[pos.front()] << '\n';
		pos.pop_front();
	}
}

int EX_3_1()
{
	List<Person> people;

	people.push_back(Person{ 1, "Mikul Hirani", 20, 'M' });
	people.push_back(Person{ 2, "Bhavik Hirani", 20, 'M' });
	people.push_back(Person{ 3, "Nirav Rabadia", 20, 'M' });
	people.push_back(Person{ 4, "Devanshi Vaghani", 19, 'F' });
	people.push_back(Person{ 5, "Divyesh Dabasia", 19, 'M' });
	people.push_back(Person{ 6, "Mann Patel", 18, 'M' });
	people.push_back(Person{ 7, "Harshad Vekaria", 19, 'M' });
	people.push_back(Person{ 8, "Yash Vekaria", 18, 'M' });


	List<int> position;

	position.push_back(5);
	position.push_back(3);
	position.push_back(1);
	position.push_back(0);
	position.push_back(2);
	position.push_back(6);

	printLots(people, position);

	_Wait();
	return 0;
}



/*
	USE STACK WITH IMPLIMENTATION OF LINKED LIST
*/

int Queue_EG()
{
	Queue<int> nums;

	std::cout << "Size: " << nums.size() << '\n';
	std::cout << "Is Empty: " << std::boolalpha << nums.empty() << '\n';

	nums.enqueue(2);
	nums.enqueue(3);
	nums.enqueue(4);
	nums.enqueue(6);
	nums.enqueue(10);
	nums.enqueue(43);
	nums.enqueue(23);
	nums.enqueue(7);
	nums.enqueue(22);
	nums.enqueue(73);

	int index = 0;

	std::cout << "Element dequeued: " << nums.dequeue() << '\n';

	nums.enqueue(77);
	std::cout << "Element at index " << index << ": " << nums[index] << '\n';



	//std::cout << "Element at front: " << nums.dequeue() << '\n';
	//std::cout << "Element at front: " << nums.dequeue() << '\n';

	_New(2);
	std::cout << "Size: " << nums.size() << '\n';
	std::cout << "Capacity: " << nums.capacity() << '\n';
	std::cout << "Is Empty: " << std::boolalpha << nums.empty() << '\n';

	_Wait();
	return 0;
}

int Stack_Linked_List()
{
	L_Stack<int> nums;

	std::cout << "Is Empty: " << std::boolalpha << nums.empty() << '\n';
	std::cout << "Size: " << nums.size() << '\n';

	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);

	std::cout << "Element: " << nums.top() << '\n';
	nums.pop();
	std::cout << "Element: " << nums.top() << '\n';

	_New(2);
	std::cout << "Is Empty: " << std::boolalpha << nums.empty() << '\n';
	std::cout << "Size: " << nums.size() << '\n';

	_Wait();
	return 0;
}

int getPriorityOfOperator(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/')
		return 2;
	if (ch == '^')
		return 3;
	else return 0;
}



int InfixToPostfix_V2(std::string& infix_exp, std::string& postfix_exp)
{
	Stack<char> operators;

	//std::string infix_exp = "a+b*c/d-q";

	//std::string infix_exp = "4*2+5*(3-2/2)-1";
							//42 * 5322 / -*1 - +
							//42 * 5322 / -*1 - +

	//std::string infix_exp = "3*3+(2-(6/2)+5)-3+8/5";  //  = 33 * 262 / -5++3 - 85 / +
											//output	//	33 * 262 / -5++3 - 85 / +
	//std::string postfix_exp = "";

	std::string delimiter = "*/+-";

	for (auto i = infix_exp.begin(); i != infix_exp.end(); i++)
	{
		if (*i == '(') operators.push_back(*i);
		else if (*i == ')')
		{
			while (operators.back() != '(')
			{
				postfix_exp += operators.back();
				operators.pop_back();
			}

			operators.pop_back();
		}
		//else if (*i == '+' || *i == '-' || *i == '*' || *i == '/' )
		else if (std::find(delimiter.begin(), delimiter.end(), *i) != delimiter.end())
		{
			if (operators.empty()) operators.push_back(*i);
			else
			{
				if (getPriorityOfOperator(operators.back()) >= getPriorityOfOperator(*i))
				{
					postfix_exp += operators.back();
					operators.pop_back();
					operators.push_back(*i);
				}
				else operators.push_back(*i);

			}
		}
		else postfix_exp += *i;
	}

	if (!operators.empty())
	{
		while (!operators.empty())
		{
			postfix_exp += operators.back();
			operators.pop_back();
		}
	}


	std::cout << "Result: " << postfix_exp << '\n';

	//_Wait();
	return 0;
}


int Postfix_Expression_Evaluation()
//int main()
{
	//std::string expression = "546+*493/+*"; // = 350
	//std::string expression = "42*5322/-*+1-"; // = 17
	//std::string expression = "4329*5302010/-*+100-"; // = 1287

	std::string infix_exp = "3-2+(6*2)";

	std::string expression = "";

	InfixToPostfix_V2(infix_exp, expression);


	Stack<float> values;

	std::string delimiter = "*/+-";

	for (std::string::iterator i = expression.begin(); i != expression.end(); i++)
	{

		std::string::iterator itr = std::find(delimiter.begin(), delimiter.end(), *i);

		if (itr == delimiter.end())
		{
			float val = *i - '0';
			values.push_back(val);
		}

		else
		{
			if (!values.empty())
			{
				float val1 = values.back();
				values.pop_back();
				float val2 = values.back();
				values.pop_back();

				if (*i == '*') values.push_back(val2 * val1);
				else if (*i == '/') values.push_back(val2 / val1);
				else if (*i == '+') values.push_back(val2 + val1);
				else if (*i == '-') values.push_back(val2 - val1);
			}
		}


	}
	std::cout << "Size of stack: " << values.size() << '\n';
	std::cout << "Result: " << values.back() << '\n';

	_Wait();
	return 0;
}


void WriteToFile(const char* filePath)
{
	std::ofstream fout(filePath);

	fout << "{\n";
	fout << "\t\"Name\" : \"Mikul Hirani\",\n";
	fout << "\t\"Email\" : \"hm@gmail.com\",\n";
	fout << "\t\"DOB\" : \"2000-01-01\",\n";
	fout << "\t\"Gender\" : \'M\',\n";
	fout << "}\n";

	fout.close();
}

struct SymbolError
{
	SymbolError(int page = 0, char symb = 'U') : lineNumber{ page }, symbol{ symb } {}
	int lineNumber;
	char symbol;
};

int Balance_Symbol_Eg2()
{
	Stack<char> characters;
	Stack<SymbolError> errors;

	int n = 323;


	std::ifstream fin("carsDB.txt");

	std::string line;

	std::string openingDelimiter = "{[(";
	std::string closingDelimeter = "}])";


	int lineNumber = 1;

	while (std::getline(fin, line))
	{

		for (auto i = line.begin(); i != line.end(); i++)
		{
			auto opening = std::find(openingDelimiter.begin(), openingDelimiter.end(), *i);

			if (opening != openingDelimiter.end()) characters.push_back(*opening);
			else
			{
				auto closing = std::find(closingDelimeter.begin(), closingDelimeter.end(), *i);

				if (closing != closingDelimeter.end())
				{
					if (characters.empty())
					{
						errors.push_back(SymbolError{ lineNumber, *closing });
						break;
					}

					char symbol = characters.back();

					if (symbol == '{' && *closing == '}') characters.pop_back();
					else if (symbol == '(' && *closing == ')') characters.pop_back();
					else if (symbol == '[' && *closing == ']') characters.pop_back();
					else
					{
						//characters.pop_back();
						errors.push_back(SymbolError{ lineNumber, symbol });
						break;
					}

				}
			}

		}

		lineNumber++;
	}

	fin.close();

	_New(2);

	if (errors.empty()) std::cout << "Balanced symbols.\n";
	else
	{
		std::cout << "Unbalanced symbols.\n\n";

		std::cout << "------------------> ERROR! <-------------------\n";
		while (!errors.empty())
		{
			std::cout << "\tLine number: " << errors.back().lineNumber << '\n';
			std::cout << "\tSymbol: " << errors.back().symbol << "\n\n";

			errors.pop_back();
		}

	}
	_Wait();
	return 0;
}

int Balancing_Symbol_EG1()
{
	Stack<char> characters;

	std::ifstream fin("Text2.txt");

	std::string line;

	std::string openingDelimiter = "{[(";
	std::string closingDelimeter = "}])";

	while (std::getline(fin, line))
	{
		const auto itr = std::find_first_of(line.begin(), line.end(), openingDelimiter.begin(), openingDelimiter.end());

		if (itr != line.end()) characters.push_back(*itr);
		else
		{
			const auto itr2 = std::find_first_of(line.begin(), line.end(), closingDelimeter.begin(), closingDelimeter.end());

			if (itr2 != line.end())
			{
				char symbol = characters.back();

				if (symbol == '{' && *itr2 == '}') characters.pop_back();
				else if (symbol == '(' && *itr2 == ')') characters.pop_back();
				else if (symbol == '[' && *itr2 == ']') characters.pop_back();

			}
		}
	}

	fin.close();

	_New(2);

	if (characters.empty()) std::cout << "Balanced symbols.\n";
	else std::cout << "Unbalanced symbols.\n";

	_Wait();
	return 0;
}


int Stack_EG()
{
	Stack<int> nums;

	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(5);
	nums.push_back(6);

	std::cout << "Size: " << nums.size() << '\n';

	std::cout << "Pop: " << nums.back() << '\n';
	std::cout << "Pop: " << nums.back() << '\n';
	std::cout << "Pop: " << nums.back() << '\n';
	std::cout << "Pop: " << nums.back() << '\n';

	std::cout << "Size: " << nums.size() << '\n';


	_Wait();
	return 0;
}


int CAT2()
{

	std::string class_5A[][2] = {
		{ "Mikul Hirani", "M"},
		{ "Devanshi Vaghani", "F" },
		{ "Bhavik Hirani", "M"},
		{ "Sharon", "F"},
	};

	std::string class_5B[][2] = {
	{ "Mina Kerai", "F"},
	{ "Shivani Halai", "F" },
	{ "Yash Vekaria", "M"},
	{ "Pinky Paliwal", "F"},
	{ "Harshad Vekaria", "M"},
	{ "Ishika Senghani", "F"},
	};

	int total = 10;

	std::string* class_5C2 = new std::string[total];

	/*
		FILTER OUT ALL GIRLS FROM TWO CLASSES
	*/

	int index = 0;
	std::string class_5C[6][2];

	for (int i = 0; i < 4; i++)
		if (class_5A[i][1] == "F")
		{
			class_5C[index][0] = class_5A[i][0];
			class_5C[index][1] = class_5A[i][1];
			index++;
		}

	for (int i = 0; i < 6; i++)
		if (class_5B[i][1] == "F")
		{
			class_5C[index][0] = class_5B[i][0];
			class_5C[index][1] = class_5B[i][1];
			index++;
		}

	for (int i = 0; i < 6; i++)
	{
		std::cout << "Name: " << class_5C[i][0] << ", Gender: " << class_5C[i][1] << "\n";
	}

	_Wait();

	delete[] class_5C2;
	return 0;
}


void printList(const List<Person>& list)
{
	for (List<Person>::const_iterator i = list.begin(); i != list.end(); i++)
	{
		std::cout << *i << ",\n";
	}
}

void printList(const MyList::List<Person>& list)
{
	for (MyList::List<Person>::const_iterator i = list.begin(); i != list.end(); i++)
	{
		std::cout << *i << ",\n";
	}
}


int MYList_EG2()
{
	MyList::List<Person> lists;

	lists.push_back(Person{ 1, "Mikul Hirani", 20, 'M' });
	lists.push_back(Person{ 2, "Bhavik Hirani", 21, 'M' });
	lists.push_back(Person{ 3, "Nirav Rabadia", 26, 'M' });

	MyList::List<Person>::const_iterator f{ lists.begin() };

	std::cout << "Front: " << lists.front() << '\n';
	std::cout << "Last: " << lists.back() << '\n';

	std::cout << "Size: " << lists.size() << '\n';

	printList(lists);

	_Wait();
	return 0;
}

int MyList_Example()
{
	List<Person> lists;

	lists.push_back(Person{ 1, "Mikul Hirani", 20, 'M' });
	lists.push_back(Person{ 2, "Bhavik Hirani", 20, 'M' });
	lists.push_back(Person{ 3, "Nirav Vaghani", 19, 'F' });

	std::cout << "Size: " << lists.size() << '\n';

	Person person = lists.back();
	const Person person2 = lists.back();

	person.setName("Harshad Vekaria");

	lists.pop_front();
	std::cout << "Element at 0: " << lists.front().getName() << '\n';
	std::cout << "Element at last: " << person << '\n';

	std::cout << "Size: " << lists.size() << '\n';

	_New(2);

	printList(lists);

	_Wait();
	return 0;
}



template<typename Container>

auto begin(Container& c) -> decltype (c.begin())
{

	return c.begin();
}

void Print(const Vector<int>& cont)
{
	std::cout << "[ ";
	for (auto& e : cont)
	{
		std::cout << e << ", ";
	}
	std::cout << "]\n";

}

int MyVector_Example()
{
	Vector<int> nums(10);

	for (int i = 0; i < nums.size(); i++)
		nums[i] = i + 1;

	std::cout << "Size of nums: " << nums.size() << '\n';

	for (Vector<int>::iterator i = nums.begin(); i != nums.end(); i++)
		std::cout << *i << ", ";


	_New(2);

	Vector<Person> people;

	people[0] = (Person{ 1, "Mikul Hiran", 20, 'M' });

	std::cout << "Size of people: " << people.size() << '\n';



	_Wait();
	return 0;
}







#include <stack>

class InfixToPostfix
{

public:

	InfixToPostfix(const std::string& expression) : expression_(expression) { }

	int getPrecedenceOfOperators(char);

	std::string convertInfixToPostfix();

private:
	std::string expression_;

};

int InfixToPostfix::getPrecedenceOfOperators(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/')
		return 2;
	if (ch == '^')
		return 3;
	else
		return 0;
}

std::string InfixToPostfix::convertInfixToPostfix()
{
	std::stack <char> stack1;
	std::string infixToPostfixExp = "";
	int i = 0;
	while (expression_[i] != '\0')
	{
		//if scanned character is open bracket push it on stack
		if (expression_[i] == '(' || expression_[i] == '[' || expression_[i] == '{')
			stack1.push(expression_[i]);

		//if scanned character is opened bracket pop all literals from stack till matching open bracket gets poped
		else if (expression_[i] == ')' || expression_[i] == ']' || expression_[i] == '}')
		{
			if (expression_[i] == ')')
			{
				while (stack1.top() != '(')
				{
					infixToPostfixExp = infixToPostfixExp + stack1.top();
					stack1.pop();
				}
			}
			if (expression_[i] == ']')
			{
				while (stack1.top() != '[')
				{
					infixToPostfixExp = infixToPostfixExp + stack1.top();
					stack1.pop();
				}
			}
			if (expression_[i] == '}')
			{
				while (stack1.top() != '{')
				{
					infixToPostfixExp = infixToPostfixExp + stack1.top();
					stack1.pop();
				}
			}
			stack1.pop();
		}
		//if scanned character is operator
		else if (expression_[i] == '+' || expression_[i] == '-' || expression_[i] == '*' || expression_[i] == '/' || expression_[i] == '^')
		{
			//very first operator of expression is to be pushed on stack
			if (stack1.empty()) {
				stack1.push(expression_[i]);

			}
			else {
				/*
				 * check the precedence order of instack(means the one on top of stack) and incoming operator,
				 * if instack operator has higher priority than incoming operator pop it out of stack&put it in
				 * final postifix expression, on other side if precedence order of instack operator is less than i
				 * coming operator, push incoming operator on stack.
				 */
				if (getPrecedenceOfOperators(stack1.top()) >= getPrecedenceOfOperators(expression_[i]))
				{
					infixToPostfixExp = infixToPostfixExp + stack1.top();
					stack1.pop();
					stack1.push(expression_[i]);
				}
				else
				{
					stack1.push(expression_[i]);
				}
			}
		}
		else
		{
			//if literal is operand, put it on to final postfix expression
			infixToPostfixExp = infixToPostfixExp + expression_[i];
		}
		i++;
	}

	//poping out all remainig operator literals & adding to final postfix expression
	if (!stack1.empty())
	{
		while (!stack1.empty())
		{
			infixToPostfixExp = infixToPostfixExp + stack1.top();
			stack1.pop();
		}
	}

	return infixToPostfixExp;

}

int Others()
{
	std::string infix_exp = "4*2+5*(3-2/2)-1";
	std::string infix_exp2 = "a+b*c/d-q";
	std::string infix_exp3 = "a-(b*c-d)/e";

	InfixToPostfix p(infix_exp);

	std::cout << "\nPostfix expression      : " << p.convertInfixToPostfix();

	_Wait();
	return 0;
}
