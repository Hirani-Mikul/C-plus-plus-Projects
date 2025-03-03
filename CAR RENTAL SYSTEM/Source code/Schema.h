#pragma once
#include <string>
#include <iostream>
#include <vector>

/*
			THIS HEADER FILE INCLUDES STRUCTURE FOR ALL THE 
					DATA THAT IS REQUIRED IN THIS APP.
*/

struct Vehicle
{
	Vehicle() = default;
	Vehicle( int id, const std::string model, float amount, int stock ) : _id(id), Model(model), Price(amount), Stock(stock) {}

	int _id;
	std::string Model;

	int Stock;
	float Price;
};

struct Request
{
	Request(int v_id, std::string model, int count) : Vehicle_Id(v_id), Model(model), Count(count) {}
	int Vehicle_Id;

	std::string Model;
	int Count = 0;
};

struct User
{
	int _id;
	std::string Username;
	std::string Password;

	bool ChangePassword(const std::string& password)
	{
		if (password != Password) return false;

		std::string newPassword, confirmPassword;

		do
		{
			std::cout << "Enter new password: ";
			std::cin >> newPassword;

			std::cout << "Confirm password: ";
			std::cin >> confirmPassword;

			if (newPassword == confirmPassword) break;
			else std::cout << "Password and Confirm Password does not match, try again.\n\n";


		} while (true);

		Password = newPassword;

		return true;
	}
	
};

struct NormalUser : public User
{
	float Balance = 0.0f;

	void DepositCash(float amount) {

		if (amount <= 0) return;
		Balance += amount;
	}

	bool WithdrawCash( float amount )
	{
		if (Balance < amount)
		{
			std::cout << "Insufficient balance...\n";
			return false;
		}

		Balance -= amount;
		return true;
	}
};

struct AdminUser : public User {};

struct UserData
{
	int User_Id;
	std::vector<Request> Rented;
	std::vector<Request> Pending;
	std::vector<Request> Returns;

	Request* GetRequest( int vehicle_id, char flag )
	{
		// Returns pointer to individual request based on vehicle id.
		// Returns NULL POINTER if no request is found.
		// FLAG is used to determine which request to loop through
		switch (flag)
		{
		case 'r':
			for (auto& req : Rented)
				if (req.Vehicle_Id == vehicle_id)
					return &req;

			return nullptr;
			break;
		case 'P':
			for (auto& req : Pending)
				if (req.Vehicle_Id == vehicle_id)
					return &req;

			return nullptr;
			break;
		case 'R':
			for (auto& req : Returns)
				if (req.Vehicle_Id == vehicle_id)
					return &req;

			return nullptr;
			break;
		default:
			return nullptr;
			break;
		}

	}

	std::vector<Request>* GetAllRequests( char flag )
	{
		// Simply returns the pointer to the list of requests depending on the flag
		if (flag == 'r') return &Rented;
		else if (flag == 'P') return &Pending;
		else if (flag == 'R') return &Returns;

		return nullptr;
	}

};


struct LocalStorage
{
	// Used for storing and retrieving current user.
	// Therefore, no need to input credentials every time the app is started.
	// UNLESS: you log out
	bool isAdmin;
	int CurrentUser_Id;
	int User_Id_Counter;
	int Admin_Id_Counter;
};

struct Cart
{
	// USED: to reference a particular vehicle and user during making a request to rent a car.
	Vehicle* vehicle;
	NormalUser* user;

	int numOfVehicles;
};

struct Pending_Info
{
	// Used for temporarily store data about the user pending requests.
	std::string Username;
	int User_Id;
	int NumOfRequests;
};