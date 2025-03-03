#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"

struct SymbolError
{
    int lineNumber = 0;
    char symbol = 'U';
};

int main()
{
    Stack<char> symbols;

    std::string openingDelimiter = "([{";
    std::string closingDelimiter = ")]}";

    //std::ifstream input("carsDB.txt");
    //std::ifstream input("Test.txt");
    //std::ifstream input("AdminPages.h");
    std::ifstream input("Code.txt");
    

    std::string line;

    int lineNumber = 1;

    SymbolError error;

    while (std::getline(input, line))
    {
        for (std::string::iterator i = line.begin(); i != line.end(); i++)
        {
            if (*i == '(' || *i == '{' || *i == '[') symbols.push_back(*i);
            else if (*i == ')' || *i == '}' || *i == ']')
            {
                if (symbols.empty())
                {
                    error.lineNumber = lineNumber;
                    error.symbol = *i;
                    break;
                }

                char top = symbols.top();

                if (top == '(' && *i == ')') symbols.pop();
                else if (top == '[' && *i == ']') symbols.pop();
                else if (top == '{' && *i == '}') symbols.pop();
                else
                {
                    error.lineNumber = lineNumber;
                    error.symbol = *i;
                    break;
                }
            }
        }

        if (error.lineNumber != 0) break;

        lineNumber++;
    }

    input.close();

    if (symbols.empty()) std::cout << "Balanced symbols.\n";
    else
    {
        std::cout << "Unbalanced symbols.\n";

        std::cout << "---------------> ERROR <-----------------\n\n";

        std::cout << "\tLine: " << error.lineNumber << '\n';
        std::cout << "\tSymbol: " << error.symbol << '\n';
    }

    std::cout << "\nPress enter to continue.";
    std::cin.get();
    return 0;
}









int main_2()
{
    Stack<char> symbols;

    std::string openingDelimiter = "([{";
    std::string closingDelimiter = ")]}";

    //std::ifstream input("carsDB.txt");
    std::ifstream input("Test.txt");

    std::string line;

    int lineNumber = 1;

    SymbolError error;

    while (std::getline(input, line))
    {
        for (std::string::iterator i = line.begin(); i != line.end(); i++)
        {
            /*
                USE IF STATEMENTS INSTEAD OF STD::FIND
            */
            std::string::iterator o_itr = std::find(openingDelimiter.begin(), openingDelimiter.end(), *i);

            if (o_itr != openingDelimiter.end()) symbols.push_back(*i);
            else
            {
                std::string::iterator c_itr = std::find(closingDelimiter.begin(), closingDelimiter.end(), *i);

                if (c_itr != closingDelimiter.end())
                {
                    if (symbols.empty())
                    {
                        error.lineNumber = lineNumber;
                        error.symbol = *i;
                        break;
                    }

                    char top = symbols.top();

                    if (top == '(' && *i == ')') symbols.pop();
                    else if (top == '[' && *i == ']') symbols.pop();
                    else if (top == '{' && *i == '}') symbols.pop();
                    else
                    {
                        error.lineNumber = lineNumber;
                        error.symbol = *i;
                        break;
                    }
                }
            }
        }

        if (error.lineNumber != 0) break;

        lineNumber++;
    }

    input.close();

    if (symbols.empty()) std::cout << "Balanced symbols.\n";
    else
    {
        std::cout << "Unbalanced symbols.\n";

        std::cout << "---------------> ERROR <-----------------\n\n";

        std::cout << "\tLine: " << error.lineNumber << '\n';
        std::cout << "\tSymbol: " << error.symbol << '\n';
    }

    std::cout << "\nPress enter to continue.";
    std::cin.get();
    return 0;
}