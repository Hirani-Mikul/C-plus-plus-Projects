#pragma once
#include "Schema.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <map>

// MACRO: used to insert the new line
#define _NewLine(count) for (int i = 0; i < count; i++) { std::cout << "\n"; }

// Overloading the ostream 
std::ostream& operator << (std::ostream& input, const NormalUser& user)
{
	return input
		<< "\n{\n"
		<< "\t_id: " << user._id << ",\n"
		<< "\tUsername: " << user.Username << ",\n"
		<< "\tPassword: " << user.Password << ",\n"
		<< "\tBalance: " << user.Balance << ",\n"
		<< "},";
}
std::ostream& operator << (std::ostream& input, const AdminUser& user)
{
	return input
		<< "\n{\n"
		<< "\t_id: " << user._id << ",\n"
		<< "\tUsername: " << user.Username << ",\n"
		<< "\tPassword: " << user.Password << ",\n"
		<< "},";

}
std::ostream& operator << (std::ostream& input, const std::vector<Vehicle>& vehicles)
{
	int spacing = 15;
	int counter = 1;
	input << "   " << std::setw(spacing) << "Model" << std::setw(spacing) << "|" << std::setw(spacing) << "Stock" << std::setw(spacing) << "|" << std::setw(spacing) << "Price" << std::setw(spacing) << "|\n";
	input << "_______________________________________________________________________________________________\n";
	for (auto& v : vehicles)
	{
		if (v.Stock == 0)
			continue;

		input << counter << ". " << std::setw(spacing) << v.Model << std::setw(spacing) << "|" << std::setw(spacing) << v.Stock << std::setw(spacing) << "|" << std::setw(spacing) << v.Price << std::setw(spacing) << "|\n";
		input << "---------------------------------------------------------------------------------------------\n";
		counter++;
	}

	return input;
}
std::ostream& operator << (std::ostream& input, const std::vector<Request>& requests)
{
	int spacing = 15;
	int counter = 1;

	if (requests.size() <= 0)
	{
		spacing *= 3;
		input << "\n";
		input << std::setw(spacing) << "NO REQUESTS...\n";
		return input;
	}

	input << "   " << std::setw(spacing) << "Model" << std::setw(spacing) << "|" << std::setw(spacing) << "Count" << std::setw(spacing) << "|\n";

	input << "_________________________________________________________________\n";

	for (auto& v : requests)
	{
		input << counter << ". " << std::setw(spacing) << v.Model << std::setw(spacing) << "|" << std::setw(spacing) << v.Count << std::setw(spacing) << "|\n";
		input << "-------------------------------------------------------------\n";
		counter++;
	}

	return input;
}
std::ostream& operator << (std::ostream& input, const UserData& userdata)
{
	return input
		<< "\n{\n"
		<< "\tUser_Id: " << userdata.User_Id << ",\n"
		<< "\tRented: " << userdata.Rented << ",\n"
		<< "\tPending: " << userdata.Pending << ",\n"
		<< "\tReturns: " << userdata.Returns << ",\n"
		<< "},";
}

// UTILS DEFINES SOME METHODS WHICH ARE USED OFTEN

namespace Utils
{

	void Wait()
	{
		std::cin.ignore();
		std::cout << "Press enter to continue...";
		std::cin.get();
	}

	void LogRequests(int id, char reqType, const std::vector<Request>* (*DB_GetRequests)(int, char))
	{
		const std::vector<Request>* requests = DB_GetRequests(id, reqType);

		if (!requests)
		{
			std::cout << "\n\t\t\tNO REQUESTS...\n";
			return;
		}

		std::cout << "\n\n" << *requests;
	}

	std::map<int, int> LogVehicles(const std::vector<Vehicle>& vehicles)
	{
		std::map<int, int> id_map;
		int spacing = 15;
		int counter = 1;
		std::cout << "   " << std::setw(spacing) << "Model" << std::setw(spacing) << "|" << std::setw(spacing) << "Stock" << std::setw(spacing) << "|" << std::setw(spacing) << "Price" << std::setw(spacing) << "|\n";
		std::cout << "_______________________________________________________________________________________________\n";
		for (auto& v : vehicles)
		{
			if (v.Stock == 0)
				continue;

			id_map[counter] = v._id;

			std::cout << counter << ". " << std::setw(spacing) << v.Model << std::setw(spacing) << "|" << std::setw(spacing) << v.Stock << std::setw(spacing) << "|" << std::setw(spacing) << v.Price << std::setw(spacing) << "|\n";
			std::cout << "---------------------------------------------------------------------------------------------\n";
			counter++;
		}

		return id_map;
	}

	std::map<int, int> LogPendingInfo(const std::vector<Pending_Info>& pendings)
	{

		std::map<int, int> id_map;

		int spacing = 15;
		int counter = 1;

		std::cout << "   " << std::setw(spacing) << "_id" << std::setw(spacing) << "|" << std::setw(spacing) << "Username" << std::setw(spacing) << "|" << std::setw(spacing) << "No. of Requests" << std::setw(spacing) << "|\n";
		std::cout << "_______________________________________________________________________________________________\n";
		for (auto& info : pendings)
		{
			id_map[counter] = info.User_Id;

			std::cout << counter << ". " << std::setw(spacing) << info.User_Id << std::setw(spacing) << "|" << std::setw(spacing) << info.Username << std::setw(spacing) << "|" << std::setw(spacing) << info.NumOfRequests << std::setw(spacing) << "|\n";
			std::cout << "---------------------------------------------------------------------------------------------\n";
			counter++;
		}

		return id_map;
	}

	std::map<int, int> DisplayRequests(const std::vector<Request>& requests, const std::string& username = "")
	{
		std::map<int, int> id_map;

		int spacing = 15;
		int counter = 1;

		if (!username.empty())
		{
			int spacing2 = spacing * 2;

			std::cout << std::setw(spacing2)  << "Username: " << username;
			_NewLine(2);

		}

		std::cout << "   " << std::setw(spacing) << "Model" << std::setw(spacing) << "|" << std::setw(spacing) << "Count" << std::setw(spacing) << "|\n";

		std::cout << "_________________________________________________________________\n";

		for (auto& v : requests)
		{
			id_map[counter] = v.Vehicle_Id;

			std::cout << counter << ". " << std::setw(spacing) << v.Model << std::setw(spacing) << "|" << std::setw(spacing) << v.Count << std::setw(spacing) << "|\n";
			std::cout << "-------------------------------------------------------------\n";
			counter++;
		}

		return id_map;
		
	}

	int GetChoice(int max)
	{
		// This function takes in "max".
		// Used very often to prompt for user's choice.
		// Helps in avoiding character or string input.
		// Fixes the "std::cin" when failed.

		// MAKES IT POSSIBLE TO ONLY ACCEPT INTEGER VALUES.
		// This values are within the range (1 - max).

		int choice;

		do
		{
			std::cout << "\nEnter your choice to proceed: ";

			std::cin >> choice;

			if (std::cin.fail())
			{
				std::cout << "Enter integer value\n";
				std::cin.clear();

#undef max
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				continue;
			}

			if (choice >= 1 && choice <= max) break;
			else std::cout << "Try again, invalid choice.\n";

		} while (true);

		return choice;
	}

}