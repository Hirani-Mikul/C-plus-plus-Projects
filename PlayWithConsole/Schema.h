#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Request
{
	Request(int id, std::string model, int count) : _id(id), Model(model), Count(count) {}
	int _id;
	std::string Model;
	int Count;
};

struct Vehicle
{
	Vehicle(int id, std::string model, int count, float amount) : ID(id), Model(model), Stock(count), Amount(amount) {}

	int ID;
	std::string Model;
	int Stock;
	float Amount;
};

struct User
{
	User(int id, std::string username, std::string password) : ID(id), Username(username), Password(password) {}

	int ID;
	std::string Username;
	std::string Password;

	std::vector<Request> Requests;
	std::vector<Request> PendingRequests;
	std::vector<Request> ReturnsRequests;


	void ChangePassword(const std::string password)
	{
		Password = password;
	}

	void MakeRequests()
	{

	}
};