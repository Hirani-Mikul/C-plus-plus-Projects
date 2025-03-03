#include <iostream>
#include "Schema.h"
#include "Pages.h"

void SetPage(Page page) {

	if (CurrentPage == page) return;

	CurrentPage = page;
}

void SwitchPage()
{
	switch (CurrentPage)
	{
	case Page::HOME:
		HomePage();
		break;
	case Page::LOGIN:
		LoginPage();
		break;
	case Page::USER:
		UserPage();
		break;
	case Page::ADMIN:
		AdminPage();
		break;
	case Page::REGISTER:
		RegisterPage();
		break;
	case Page::DETIALS:
		DetialsPage();
		break;
	case Page::LOGOUT:
		LogoutPage();
		break;
	default:
		std::cout << "Page Unavailable\n";
		break;
	}
}

std::ostream& operator <<( std::ostream& input, const Vehicle& v ) 
{
	return input
		<< "{\n"
		<< "\t_Id: " << v.ID << ",\n"
		<< "\tModel: " << v.Model << ",\n"
		<< "\tStock: " << v.Stock << ",\n"
		<< "\tAmount: " << v.Amount << "\n"
		<< "},\n";
}

std::string ReadRequests( const std::vector<Request>& req )
{

	std::string text;

	if (req.size() == 0)
		return "0,\n";

	text += "[\n";
	for (auto& r : req)
	{
		text += "\t\t\t{\n";
		text += "\t\t\t\tModel: " + r.Model + ",\n" + "\t\t\t\tCount: " + std::to_string(r.Count) + ",\n";
		text += "\t\t\t},\n";
	}
	text += "\t\t]\n";

	return text;
}

std::ostream& operator << ( std::ostream& input, const User& u )
{
	return input
		<< "{\n"
		<< "\t_Id: " << u.ID << ",\n"
		<< "\tUsername: " << u.Username << ",\n"
		<< "\tPassword: " << u.Password << ",\n"
		<< "\tRequests: " << ReadRequests(u.Requests)
		<< "\tPending: " << ReadRequests(u.PendingRequests)
		<< "\tReturns: " << ReadRequests(u.ReturnsRequests)
		<< "},\n";
}

template<class Container>
void LogObjects( const Container& cont )
{
	for (auto& e : cont)
		std::cout << e;
}

int main()
{
	std::vector<Vehicle> Vehicles;
	Vehicles.reserve(4);
	Vehicles.emplace_back( 1, "Ferrari", 1002, 10023.80f );
	Vehicles.emplace_back( 2, "Buggati", 112, 2343.0f );
	Vehicles.emplace_back( 3, "Range Rover", 23, 223.30f );
	Vehicles.emplace_back( 4, "Probox", 93042, 23.05f );

	std::vector<User> Users;
	Users.reserve(4);
	Users.emplace_back(1, "Mikul", "hirani123");
	Users.emplace_back(2, "Bhavik", "bhavik123");
	Users.emplace_back(3, "Nirav", "rabadia123");
	Users.emplace_back(4, "Harshad", "vekaria123");

	Users[0].Requests.push_back(Request{ 1, "Ferrari", 20 });
	Users[0].Requests.push_back(Request{ 2, "Buggati", 620 });
	Users[0].Requests.push_back(Request{ 4, "Probox", 22320});

	LogObjects(Users);
}

