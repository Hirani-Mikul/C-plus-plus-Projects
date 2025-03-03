#pragma once
#include <iostream>

enum class Page : unsigned int {
	HOME = 0,
	LOGIN,
	USER,
	ADMIN,
	REGISTER,
	DETIALS,
	LOGOUT
};

Page CurrentPage = Page::HOME;

namespace Utils
{
	int GetChoice(int max) {

		int choice;

		do
		{
			std::cout << "Enter role to proceed: ";
			std::cin >> choice;

			if (std::cin.fail())
			{
				std::cout << "Enter integer value\n";
				std::cin.clear();
#undef max
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				continue;
			}

			if (choice >= 1 && choice <= max)
				break;
			else
			{
				std::cout << "Try again, invalid choice.\n";
			}

		} while (true);

		return choice;
	}
}