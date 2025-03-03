#pragma once
#include <string>
#include <iomanip>
#include <iostream>

struct Vehicle
{
	std::string Model;
	float Price;

	int In_Stock;
};

struct User {


	std::string Username;
	std::string Password;

	void ChangePassword(const std::string& password)
	{
		Password = password;
	}
};
struct CarRequest
{
	CarRequest( const std::string model, int count ) : Model(model), Count(count) {}

	std::string Model;
	int Count;
};
struct NormalUser : public User
{
	float Balance;

	std::vector<CarRequest> Requests;

	void DisplayRequests() {

	}
};

struct AdminUser : public User
{

};