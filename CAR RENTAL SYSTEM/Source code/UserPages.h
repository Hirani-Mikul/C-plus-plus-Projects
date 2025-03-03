#pragma once

#include "Constants.h"
#include "Database.h"
#include <map>

// ALL THE NORMALUSER PAGES (FUNCTIONS)
// ACTIONS ARE TAKEN BASED ON THE CHOICE

void extern SetPage(Page);

void NormalUserPage() {

	system("cls");

	std::cout << "------------------> USER HOMEPAGE <-----------------" << std::endl << std::endl;

	std::cout << "1. View Peronal Details.\n";
	std::cout << "2. Goto ATM.\n";
	std::cout << "3. Request to rent a car.\n";
	std::cout << "4. Return rented car.\n";
	std::cout << "5. Change password.\n";
	std::cout << "6. LOG OUT.\n";

	int choice = Utils::GetChoice(6);

	if (choice == 1)      SetPage(Page::PERSONALDETAILS_PAGE);
	else if (choice == 2) SetPage(Page::ATM_PAGE);
	else if (choice == 3) SetPage(Page::U_SEND_REQUESTS_PAGE);
	else if (choice == 4) SetPage(Page::U_SEND_RETURNSREQUEST_PAGE);
	else if (choice == 5) SetPage(Page::U_CHANGEPASSWORD_PAGE);
	else if (choice == 6) SetPage(Page::U_LOGOUT_PAGE);

}
void ATMPage() {
	system("cls");
	std::cout << "------------------> WELCOME TO ATM <-----------------" << std::endl << std::endl;

	std::cout << "Balance: " << CurrentUser->Balance << "\n\n";

	std::cout << "1. Deposit cash.\n";
	std::cout << "2. Withdraw cash.\n";
	std::cout << "3. GO BACK.\n";

	int choice = Utils::GetChoice(3);
	bool isTransactionMade = false;

	if (choice == 1 || choice == 2)
	{
		float amount;
		std::cout << "Enter amount: ";
		std::cin >> amount;

		if (choice == 1)
		{
			CurrentUser->DepositCash(amount);
			isTransactionMade = true;
		}
		else if (choice == 2)
		{
			isTransactionMade = CurrentUser->WithdrawCash(amount);
		}

		if (isTransactionMade)
		{
			Database::UpdateNoramlUsers();
			std::cout << "Account updated.\n";
		}
		Sleep(500);
	}
	else if (choice == 3)
		SetPage(Page::NORMALUSER_PAGE);

}
void PersonalDetailsPage() {

	system("cls");

	std::cout << "------------------> USER DETAILS PAGE <-----------------" << std::endl << std::endl;

	std::cout << "Username: " << CurrentUser->Username << "\n";
	std::cout << "Balance: " << CurrentUser->Balance << "\n\n";
	std::cout << "1. Requests: " << "\n";
	std::cout << "2. Pending Requests." << "\n";
	std::cout << "3. Pending Returns." << "\n";
	std::cout << "4. GO BACK." << "\n";

	int choice = Utils::GetChoice(4);

	if (choice != 4)
	{
		auto (*DB_GetRequests)(int, char) = Database::GetRequests;

		int id = CurrentUser->_id;

		if (choice == 1) Utils::LogRequests(id, 'r', DB_GetRequests);
		if (choice == 2) Utils::LogRequests(id, 'P', DB_GetRequests);
		if (choice == 3) Utils::LogRequests(id, 'R', DB_GetRequests);

		std::cout << "\nPress enter to continue.\n";
		std::cin.ignore();
		std::cin.get();
	}
	else if (choice == 4) SetPage(Page::NORMALUSER_PAGE);

}

void UserRequestPage()
{
	system("cls");
	std::cout << "-----------------------------> CAR SHOWROOM <--------------------------" << std::endl << std::endl;

	std::map<int, int> id_map = Database::LogVehicles();

	int numOfVehicles = (--id_map.end())->first;
	numOfVehicles++;

	std::cout << "\n";
	std::cout << numOfVehicles << ". GO BACK.\n\n";

	std::cout << "\nSelect your choice of car.\n\n";


	int choice = Utils::GetChoice(numOfVehicles);

	if (choice == numOfVehicles)
	{
		SetPage(Page::NORMALUSER_PAGE);
		return;
	}

	Cart cart = Database::RequestToRent(id_map[choice]);

	cart.user = CurrentUser;

	int numOfRequests;
	std::cout << "Enter Number of \"" << cart.vehicle->Model << "\" to rent : ";
	std::cin >> numOfRequests;

	if (numOfRequests > cart.vehicle->Stock)
	{
		std::cout << "Not enough stock.\n";

		Utils::Wait();
		SetPage(Page::U_SEND_REQUESTS_PAGE);
		return;
	}
	else
	{
		float TotalAmount = cart.vehicle->Price * numOfRequests;

		cart.numOfVehicles = numOfRequests;


		if (CurrentUser->WithdrawCash(TotalAmount))
		{
			// TODO
			Database::CompleteRequest(cart);

			std::cout << "Congratulations, request has been sent.\n";
			Utils::Wait();
			SetPage(Page::NORMALUSER_PAGE);
			return;
		}
		else {
			Utils::Wait();

			SetPage(Page::U_SEND_REQUESTS_PAGE);
			return;
		}

	}




	//if (CurrentUser->WithdrawCash(TotalAmount))



}

void ReturnRequestPage()
{
	system("cls");

	std::cout << "-----------------------------> WELCOME TO GARAGE <--------------------------" << std::endl << std::endl;

	const std::vector<Request>* requests = Database::GetRequests(CurrentUser->_id, 'r');

	if (!requests || requests->size() <= 0)
	{
		std::cout << "\t\t\tNO REQUESTS..\n";
		Utils::Wait();

		SetPage(Page::NORMALUSER_PAGE);
		return;
	}

	std::map<int, int> id_map = Utils::DisplayRequests(*requests);

	int totalRentedVehicles = (--id_map.end())->first;
	totalRentedVehicles++;

	_NewLine(1);
	std::cout << totalRentedVehicles << ". GO BACK.\n";

	int choice = Utils::GetChoice(totalRentedVehicles);

	if (choice == totalRentedVehicles)
	{
		SetPage(Page::NORMALUSER_PAGE);
		return;
	}

	int numOfRequests;
	std::cout << "Enter number of vehicles to return: ";
	std::cin >> numOfRequests;

	int vehicle_id = id_map[choice];

	bool isSuccess = Database::RequestToReturn( CurrentUser->_id, vehicle_id, numOfRequests);

	if (isSuccess)
	{
		Database::UpdateUserDatas();
		std::cout << "Request sent successfully.";
		_NewLine(2);

	}
	else {
		_NewLine(1);
		std::cout << "Sorry, your number of request exceeds total number of vehicles you rented.";
		_NewLine(2);
	}

	Utils::Wait();

	SetPage(Page::U_SEND_RETURNSREQUEST_PAGE);
	return;
}
