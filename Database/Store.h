#pragma once
#include <vector>
#include "UserSchema.h"

class Store
{
public:
	Store(const Store&) = delete;

	static Store& Get()
	{
		static Store Instance;
		return Instance;
	}

public:

	void Initialize()
	{
		// LOAD THE DATA FROM TEXT FILE

		User user;
		user._id = 1;
		user.Username = "John";
		user.Password = "john123";
		user.Balance = 234.34f;

		Users.push_back(user);

		UserData data;
		data.User_ID = 1;
		data.Requests.push_back(Request{ "Subaru", 13 });
		data.Requests.push_back(Request{ "Buggati", 1343 });
		data.PendingRequests.push_back(Request{ "Ferrari", 545 });
		data.ReturnsRequests.push_back(Request{ "Probox", 132});

		UserRequests.push_back(data);

	}

	void dispatch() {}

private:
	Store () {}
	std::vector<User> Users;
	std::vector<UserData> UserRequests;

};
