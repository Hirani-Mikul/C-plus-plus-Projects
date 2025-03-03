#pragma once
#include "FileStream.h"
#include "Schema.h"
#include <vector>
#include "Formatter.h"

namespace Path {

	const char USERS_DB[12] = "usersDB.txt";
	const char ADMIN_DB[13] = "adminsDB.txt";
	const char CARS_DB[11] = "carsDB.txt";
	const char Test_File[9] = "Test.txt";
	const char Test_File2[12] = "testing.txt";

}

class Database {

public:
	Database(const Database&) = delete;
public:

	static Database& Get() {
		static Database Instance;
		return Instance;
	}

	static void Initialize() { Get()._Initialize(); }
	static bool AddUser(const std::string& username, const std::string& password) { return Get()._AddUser(username, password); };
	static void UpdateUsers() { Get()._UpdateUsers(); }
	static void UpdateVehicles() { Get()._UpdateVehicles(); }

	static NormalUser* ValidateUser(const std::string& username, const std::string& password) { return Get()._ValidateUser(username, password); }
	static AdminUser* ValidateAdmin(const std::string& username, const std::string& password) { return Get()._ValidateAdmin(username, password); }


	static void LogUsers() { Get()._LogUsers(); }
	static void LogAdminUsers() { Get()._LogAdminUsers(); }
	static void LogVehicles() { Get()._LogVehicles(); }
	static void DisplayVehicles() { Get()._DisplayVehicles(); }

private:
	void _Initialize() {
		_LoadData();
	}
	void _LoadData() {
	
		Formatter::ParseUserData(FileStream::ReadFile(Path::Test_File), Users);
		FileStream::WriteToFile(Path::Test_File2, std::move(Formatter::StringifyUserData(Users)));
	}

	NormalUser* _ValidateUser( const std::string& username, const std::string& password ) {
	
		NormalUser* foundUser = &SearchUserByUsername(username);

		if (foundUser)
			if (foundUser->Password == password)
				return foundUser;

		return nullptr;
	}

	AdminUser* _ValidateAdmin(const std::string& username, const std::string& password) {

		AdminUser* foundUser = &SearchAdminByUsername(username);

		if (foundUser)
			if (foundUser->Password == password)
				return foundUser;

		return nullptr;
	}

	NormalUser& SearchUserByUsername( const std::string& username ) {
		
		NormalUser* foundUser = nullptr;

		for (auto& u : Users)
		{
			if (u.Username == username)
			{
				foundUser = &u;
				break;
			}
		}

		return *foundUser;
		
	}
	AdminUser& SearchAdminByUsername(const std::string& username) {

		AdminUser* foundUser = nullptr;

		for (auto& u : AdminUsers)
		{
			if (u.Username == username)
			{
				foundUser = &u;
				break;
			}
		}

		return *foundUser;

	}
	bool _AddUser(const std::string& username, const std::string& password) {

		NormalUser* userExist = &SearchUserByUsername(username);

		if (userExist)
		{
			return true;
		}

		NormalUser user;

		user.Username = username;
		user.Password = password;

		Users.push_back(user);


		return false;
	}
	void _UpdateUsers() {
	
		
	}
	void _UpdateVehicles() {


	}

	void _UpdateAdminUsers() {}

	void _LogUsers() {

	}
	void _LogAdminUsers() {

	}
	void _LogVehicles()
	{
	}
	void _DisplayVehicles()
	{
		int spacing = 15;
		int counter = 1;
		std::cout << "   " << std::setw(spacing) << "Model" << std::setw(spacing) << "|" << std::setw(spacing) << "Stock" << std::setw(spacing) << "|" << std::setw(spacing) << "Price" << std::setw(spacing) << "|\n";
		std::cout << "_______________________________________________________________________________________________\n";
		for (auto& v : Vehicles)
		{
			if (v.In_Stock == 0)
				continue;

			std::cout << counter << ". " << std::setw(spacing) << v.Model << std::setw(spacing) << "|" << std::setw(spacing) << v.In_Stock << std::setw(spacing) << "|" << std::setw(spacing) << v.Price << std::setw(spacing) << "|\n";
			std::cout << "---------------------------------------------------------------------------------------------\n";
			counter++;
		}
	}

private:
	Database() {}
	std::vector<NormalUser> Users;
	std::vector<AdminUser> AdminUsers;
	std::vector<Vehicle> Vehicles;
	
	static int ID_Counter;
};

int Database::ID_Counter = 0;

