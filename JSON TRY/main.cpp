#include "json.hpp"
#include <fstream>
#include <vector>
#include "Database.h"

using json::JSON;


std::string ReadUserRequests(const std::vector<CarRequest>& requests) {
	std::string text;

	if (requests.size() == 0)
		return "0,\n";

	text += "[\n";
	for (auto& r : requests)
	{
		text += "\t\t\t{\n";
		text += "\t\t\t\tModel: " + r.Model + ",\n" + "\t\t\t\tCount: " + std::to_string(r.Count) + ",\n";
		text += "\t\t\t},\n";
	}
	text += "\t\t]\n";

	return text;
}

std::ostream& operator << (std::ostream& input, const NormalUser& u) {

	return input
		<< "\n{\n"
		<< "\tUsername: " << u.Username << ",\n"
		<< "\tPassword: " << u.Password << ",\n"
		<< "\tBalance: " << u.Balance << ",\n"
		<< "\tRequests: "
		<< ReadUserRequests(u.Requests)
		<< "},";
}


int main() {

	Database::Initialize();

}

int TRY() 
{
	NormalUser user1;
	NormalUser user2;

	user1.Username = "Mikul";
	user1.Password = "hirani123";
	user1.Balance = 1034.23f;
	user1.Requests.push_back(CarRequest{ "Ferrari", 20 });
	user1.Requests.push_back(CarRequest{ "Subaru", 340 });
	user1.Requests.push_back(CarRequest{ "Range Rover", 4530});

	user2.Username = "Bhavik";
	user2.Password = "bhavik123";
	user2.Balance = 103324.62f;
	user2.Requests.push_back(CarRequest{ "Probox", 24320 });
	user2.Requests.push_back(CarRequest{ "Toyota", 30 });
	user2.Requests.push_back(CarRequest{ "Buggati", 43 });

	std::cout << "---------------------> USERS <-------------------------\n\n";

	//std::cout << user1 << std::endl;
	//std::cout << user2 << std::endl;

	std::vector<NormalUser> Users;
	Users.push_back(user1);
	Users.push_back(user2);

	//JSON obj({
	//		"Model", "Ferrari",
	//		"Count", 10,
	//	});
	//JSON obj2({
	//	"Model", "Buggati",
	//	"Count", 10342,
	//	});

	//JSON users({
	//		
	//		"Username", "Mikul",
	//		"Password", "hirani123",
	//		"Balance", 3234.23f,
	//		"Requests", json::Array(obj, obj2),

	//	});

	JSON users;
	for (auto& u : Users)
	{
		JSON request;
		for (auto& r : u.Requests)
		{
			JSON req({ "Model", r.Model, "Count", r.Count});
			request.append(req);
			//request.append("Model", r.Model, "Count", r.Count);
		}
		JSON obj(
			{
				"Username", u.Username,
				"Password", u.Password,
				"Balance", u.Balance,
				"Requests", request
			}
		);

		users.append(obj);
	}

	return 0;
}