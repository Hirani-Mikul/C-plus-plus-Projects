#pragma once
#include <string>
#include <vector>

struct Request
{
	std::string Model;
	int Count = 0;
};

struct User {

	std::string Username;
	std::string Password;

	float Balance = 0.0f;

	std::vector<Request> Requests;

	std::string Serialize() {

		return "\n\tUsername: " + Username + ",\n\tPassword: " + Password + ",\n\tBalance: " + std::to_string(Balance) + ",\n";
	}

};