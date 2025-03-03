#pragma once
#include <string>
#include <vector>

struct Request
{
	Request( const std::string& model, int count ) : Model(model), Count(count) {}

	std::string Model;
	int Count;
};

struct UserData
{
	int User_ID;
	std::vector<Request> Requests;
	std::vector<Request> PendingRequests;
	std::vector<Request> ReturnsRequests;

};

struct User
{
	int _id;
	std::string Username;
	std::string Password;

	float Balance = 0.0f;

};