#pragma once
#include "Utils.h"
#include <Windows.h>

void SetPage(Page page);
void SwitchPage();

void HomePage() {
	
	system("cls");

	std::cout << "-----------------------------------> WELCOME TO CAR RENTAL SYSTEM <----------------------------\n\n";

	std::cout << "1. Login as Client User\n";
	std::cout << "2. Login as Administrator\n";
	std::cout << "3. Register\n";

	int choice = Utils::GetChoice(3);

	std::cout << "Your choice is: " << choice << std::endl;

}
void LoginPage() {}
void RegisterPage() {}
void UserPage() {}
void AdminPage() {}
void DetialsPage() {}
void LogoutPage() {}
