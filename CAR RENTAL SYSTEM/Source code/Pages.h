#pragma once
#include "Utils.h"
#include "Constants.h"
#include "UserPages.h"
#include "AdminPages.h"

// ALL THE FUNCTIONS THAT ARE REQUIRED BY BOTH ADMIN AND NORMAL USER

void extern SetPage(Page);


void Homepage(bool &stop_app)
{
	// Login in the user directly based on the data in the local storage.
	// IF there is user data saved in the local storage then, the user is directed to the respective page.
	std::pair<int, bool> LocalStorage = Database::LoadLocalStorage();

	if (LocalStorage.second)
	{
		CurrentAdminUser = Database::GetAdminUserById(LocalStorage.first);

		if (CurrentAdminUser)
		{
			SetPage(Page::ADMINISTRATOR_PAGE);
			return;
		}
	}
	else {
		CurrentUser = Database::GetUserById(LocalStorage.first);
		if (CurrentUser)
		{
			SetPage(Page::NORMALUSER_PAGE);
			return;
		}
	}

	system("cls");

	std::cout << "------------------> WELCOME TO THE CAR RENTAL SYSTEM <-----------------" << std::endl << std::endl;

	std::cout << "Select your role to proceed:\n";
	std::cout << "1. Normal User\n";
	std::cout << "2. Administrator\n";
	std::cout << "3. EXIT\n";

	int choice = Utils::GetChoice(3);

	if (choice == 1) SetPage(Page::U_LOGIN_PAGE);
	if (choice == 2) SetPage(Page::A_LOGIN_PAGE);
	if (choice == 3) stop_app = true;

}

void LoginPage(char flag)
{
	system("cls");

	std::cout << "------------------> LOGIN INTERFACE <-----------------" << std::endl << std::endl;

	std::string username, password;

	do
	{
		std::cout << "Enter your username: ";
		std::cin >> username;
		std::cout << "Enter your password: ";
		std::cin >> password;

		if (flag == 'U')
		{
			CurrentUser = Database::ValidateUser(username, password);

			if (CurrentUser)
			{
				std::cout << "Successfully logged in\n";
				SetPage(Page::NORMALUSER_PAGE);
				Database::UpdateLocalStorage(CurrentUser->_id, false);
				break;
			}
			else std::cout << "Try again, invalid username or password\n";
		}
		else if (flag == 'A')
		{
			CurrentAdminUser = Database::ValidateAdminUser(username, password);

			if (CurrentAdminUser)
			{
				std::cout << "Successfully logged in\n";
				SetPage(Page::ADMINISTRATOR_PAGE);
				Database::UpdateLocalStorage(CurrentAdminUser->_id, true);
				break;
			}
			else std::cout << "Try again, invalid username or password\n";
		}

	} while (true);

	Sleep(600);
}

void LogOutPage(char flag)
{
	system("cls");

	std::cout << "------------------> LOGOUT PAGE <-----------------" << std::endl << std::endl;

	std::cout << "1. Yes, proceed.\n";
	std::cout << "2. No, GO BACK.\n";

	int choice = Utils::GetChoice(2);

	if (choice == 1)
	{
		if (flag == 'U')
			CurrentUser = nullptr;

		else if (flag == 'A')
			CurrentAdminUser = nullptr;

		SetPage(Page::HOMEPAGE);
		Database::UpdateLocalStorage(0, false);
	}
	else if (choice == 2)
	{
		if (flag == 'U')
			SetPage(Page::NORMALUSER_PAGE);
		else if (flag == 'A')
			SetPage(Page::ADMINISTRATOR_PAGE);
	}

	Sleep(500);
}


bool PromptForCurrentPassword(char flag)
{
	std::string currentPassword;

	std::cout << "Type \"exit\" to go back.\n\n";
	do
	{

		std::cout << "Enter current password: ";
		std::cin >> currentPassword;

		if (currentPassword == "exit") break;

		else if (flag == 'U')
		{
			if (CurrentUser->ChangePassword(currentPassword)) return true;
		}

		else if (flag == 'A')
		{
			if (CurrentAdminUser->ChangePassword(currentPassword)) return true;
		}

		std::cout << "Incorrect password, try again...\n";


	} while (true);

	return false;
}


void ChangePassword( char flag )
{
	system("cls");

	std::cout << "------------------> CHANGE PASSWORD <-----------------" << std::endl << std::endl;

	if (PromptForCurrentPassword(flag))
	{
		std::cout << "Password changed successfully.\n";

		if (flag == 'U')      Database::UpdateNoramlUsers();
		else if (flag == 'A') Database::UpdateAdminUsers();

		_NewLine(2);
		Utils::Wait();
	}
	
	if (flag == 'U')      SetPage(Page::NORMALUSER_PAGE);
	else if (flag == 'A') SetPage(Page::ADMINISTRATOR_PAGE);
}