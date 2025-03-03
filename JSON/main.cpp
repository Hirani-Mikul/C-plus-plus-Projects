#include "JSON.h"
#include "Objects.h"
#include <iostream>


int main() {

	User user1;
	User user2;

	user1.Username = "Mikul";
	user1.Password = "hirani123";
	user1.Balance = 32423.23f;
	user1.Requests.push_back(Request{ "Ferrari", 20 });
	user1.Requests.push_back(Request{ "Bugatti", 432 });

	user2.Username = "Bhavik";
	user2.Password = "bhavik123";
	user2.Balance = 43234.12f;
	user2.Requests.push_back(Request{ "Toyota", 2000 });
	user2.Requests.push_back(Request{ "Subaru", 7331 });

	std::vector<User> Users;

	Users.push_back(user1);
	Users.push_back(user2);

	//auto data = JSON::stringify(Users);
	for (auto& u : Users)
	{
		std::cout << u.Serialize();
	}



}