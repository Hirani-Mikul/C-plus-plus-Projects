#include <iostream>
#include "Stack.h"
#include <string>

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

int getPriorityOfOperator(char ch);

void InfixToPostfix(std::string& infix_exp, std::string& postfix_exp);
void PostfixToInfix(std::string & postfix_exp);
void EvaluatePostfix();

int main()
{
	//std::string infix_exp = "4*2+5*(3-2/2)-1";

	//std::string postfix_exp = "42*5322/-*1-+";
	std::string postfix_exp = "322^*";


	PostfixToInfix(postfix_exp);

	std::cout << "Postfix: " << postfix_exp << '\n';
	//InfixToPostfix(infix_exp, postfix_exp);
	//EvaluatePostfix();

	//std::cout << "Postfix Expression: " << postfix_exp << "\n";

	_New(2);
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

void InfixToPostfix(std::string& infix_exp, std::string& postfix_exp)
{
	Stack<char> symbols;

	//std::string delimeter = "*/+-";
	std::string delimeter = "*/^+-";

	for (auto i = infix_exp.begin(); i != infix_exp.end(); i++)
	{
		if (*i == '(') symbols.push_back(*i);
		else if (*i == ')')
		{
			while (symbols.top() != '(')
			{
				postfix_exp += symbols.top();
				symbols.pop();
			}

			symbols.pop();
		}
		else if (std::find(delimeter.begin(), delimeter.end(), *i) != delimeter.end())
		{
			if (symbols.empty()) symbols.push_back(*i);
			else
			{
				if (getPriorityOfOperator(symbols.top()) >= getPriorityOfOperator(*i))
				{
					postfix_exp += symbols.pop();
					//symbols.pop();
					symbols.push_back(*i);
				}
				else symbols.push_back(*i);
			}
		}

		else postfix_exp += *i;
	}

	if (!symbols.empty())
	{
		while (!symbols.empty())
		{
			postfix_exp += symbols.pop();
		}
	}
}
void EvaluatePostfix()
{
	//std::string infix_exp = "3-2+(6*2)";
	//std::string infix_exp = "4*2+5*(3-2/2)-1";
	//std::string infix_exp = "4*2+5*((3-2)/2)-1";
	//std::string infix_exp = "3*2^2";
	std::string infix_exp = "4*2+5*(3-2^4/2)-1";


	std::string expression = "";

	InfixToPostfix(infix_exp, expression);


	Stack<float> values;

	//std::string delimiter = "*/+-";
	std::string delimiter = "*/^+-";

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
				float val1 = values.pop();
				float val2 = values.pop();

				if (*i == '*') values.push_back(val2 * val1);
				else if (*i == '/') values.push_back(val2 / val1);
				else if (*i == '^')
				{
					float ans = val1;
					for (int i = 1; i < val2; i++)
					{
						ans = ans * ans;
					}
					//values.push_back(val1 * val1);
					values.push_back(ans);

				}
				else if (*i == '+') values.push_back(val2 + val1);
				else if (*i == '-') values.push_back(val2 - val1);
			}
		}


	}
	std::cout << "Infix expression: " << infix_exp << '\n';
	std::cout << "Postfix expression: " << expression << '\n';
	std::cout << "Result: " << values.top() << '\n';
}

void PostfixToInfix(std::string& postfix_exp)
{
	Stack<std::string> characters;

	std::string infix_exp = "";

	std::string delimeter = "*/^+-";

	for (auto i = postfix_exp.begin(); i != postfix_exp.end(); i++)
	{
		if (std::find(delimeter.begin(), delimeter.end(), *i) == delimeter.end())
		{
			std::string op(1, *i);
			characters.push_back(op);
		}
		else
		{
			if (characters.size() < 2)
			{
				std::cout << "Invalid expression.\n";
				break;
			}
			else
			{
				std::string val1 = characters.pop();
				std::string val2 = characters.pop();

				std::string op = "(" + val2 + *i + val1 + ")";
				characters.push_back(op);
			}
		}
	}

	if (characters.size() == 1)
	{
		std::cout << "Infix: " << characters.top() << '\n';
	}
}
