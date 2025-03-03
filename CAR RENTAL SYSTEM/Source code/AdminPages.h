#pragma once
#include "Constants.h"
#include "Utils.h"

// ALL THE ADMINISTRATOR PAGES (FUNCTIONS)
// ACTIONS ARE TAKEN BASED ON THE CHOICE

void extern SetPage(Page);


void RegisterPage()
{
	system("cls");

	std::cout << "------------------> REGISTRATION PROCESS <-----------------" << std::endl << std::endl;

	std::cout << "Fill in the form.\n\n";

	std::string username, password, confirmPassword;

	std::cout << "Username: ";
	std::cin >> username;

	do
	{
		std::cout << "Password: ";
		std::cin >> password;
		std::cout << "Confirm Password: ";
		std::cin >> confirmPassword;

		if (password == confirmPassword)
			break;
		else std::cout << "Try again, password and confirm password does not match.\n";

	} while (true);

	float deposit = 0.0f;


	do
	{
		std::cout << "Deposit cash (at least Sh.10,500): ";
		std::cin >> deposit;

		if (deposit >= 10500) break;
		else std::cout << "\nYou have to deposit at least Sh.10,500 to continue.\n\n";

	} while (true);

	bool doesUserExist = Database::AddUser(username, password, deposit);

	if (!doesUserExist)
	{
		std::cout << "\nAccount with this username, already exist.\nPlease consider changing your username.";

		_NewLine(2);
		Utils::Wait();

		SetPage(Page::REGISTER_PAGE);
		return;
	}
	else
	{
		std::cout << "Congratulations, account created.";
		Database::UpdateLocalStorage(CurrentAdminUser->_id, true);

		_NewLine(2);
		Utils::Wait();

		SetPage(Page::ADMINISTRATOR_PAGE);
		return;
	}
}


void AdministratorPage()
{
	if (!CurrentAdminUser)
	{
		SetPage(Page::HOMEPAGE);
		return;
	}

	system("cls");

	std::cout << "------------------> ADMINISTRATION PAGE <-----------------" << std::endl << std::endl;

	std::cout << "1. Register new user.\n";
	std::cout << "2. Approve User's car rent request.\n";
	std::cout << "3. Update system on returned car.\n";
	std::cout << "4. Change password.\n";
	std::cout << "5. LOG OUT.\n";

	int choice = Utils::GetChoice(5);

	if (choice == 1) SetPage(Page::REGISTER_PAGE);
	else if (choice == 2) SetPage(Page::APPROVEREQUEST_PAGE);
	else if (choice == 3) {

		Database::UpdateSystemOnReturnedVehicles();

		std::cout << "\nSystem updated.\n\n";

		Utils::Wait();
		return;
	}
	else if (choice == 4) SetPage(Page::A_CHANGEPASSWORD_PAGE);
	else if (choice == 5) SetPage(Page::A_LOGOUT_PAGE);
}

void ApproveRequest()
{
	system("cls");

	if (!CurrentAdminUser)
	{
		SetPage(Page::HOMEPAGE);
		return;
	}

	std::cout << "-----------------------------> APPROVE REQUESTS PAGE <--------------------------" << std::endl << std::endl;

	std::vector<Pending_Info> pending_info = Database::GetPendingInfo();

	if (pending_info.size() <= 0)
	{
		std::cout << "\t\t\tNO REQUESTS.\n";
		Utils::Wait();

		SetPage(Page::ADMINISTRATOR_PAGE);
		return;
	}

	std::map<int, int> id_map = Utils::LogPendingInfo(pending_info);

	int numOfUsers = (--id_map.end())->first;
	numOfUsers++;

	std::cout << "\n";
	std::cout << numOfUsers << ". GO BACK.\n\n";

	int choice = Utils::GetChoice(numOfUsers);

	if (choice == numOfUsers)
	{
		SetPage(Page::ADMINISTRATOR_PAGE);
		return;
	}

	system("cls");

	std::string username;
	int user_id = id_map[choice];

	for (auto& info : pending_info)
		if (info.User_Id == user_id)
		{
			username = info.Username;
			break;
		}

	std::vector<Request> requests = *Database::GetRequests(user_id, 'P');

	// Clear the id_map, for reuse.
	id_map.clear();

	id_map = Utils::DisplayRequests(requests, username);

	int count = (--id_map.end())->first;

	std::cout << ++count << " GO BACK.\n\n";

	int vehicle_choice = Utils::GetChoice(count);
	int vehicle_id = id_map[vehicle_choice];

	if (vehicle_choice == count)
	{
		SetPage(Page::APPROVEREQUEST_PAGE);
		return;
	}

	int numOfAcceptedRequest;
	std::cout << "Enter the number of vehicles to grant: ";
	std::cin >> numOfAcceptedRequest;

	bool isSuccess = Database::ApproveRequest(user_id, vehicle_id, numOfAcceptedRequest);

	if (isSuccess)
	{
		Database::UpdateUserDatas();
		std::cout << "Request(s) successfully accepted.\n";
	}
	else
		std::cout << "Accepted reqeuests exceed the required requests.\n";

	Utils::Wait();
	SetPage(Page::APPROVEREQUEST_PAGE);
	return;

}