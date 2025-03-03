#include <iostream>
#include "Schema.h"
#include <iomanip>

std::ostream& operator <<(std::ostream& input, const User &user)
{
	input << user._id << "  " << user.f_name << " " << user.l_name << "  " << user.gender << "  " << user.DOB;

	return input;
}

//std::ostream& operator <<(std::ostream& input, const std::vector<User>& users)
//{
//
//#define _w() std::setw(10) // Sets width to 20
//
//	input << "_id" << _w() << "|" << _w() << "Name" << _w() << "|" << _w() << "Gender" << _w() << "|" << _w() << "DOB" << _w() << "|";
//
//	input << "\n\n";
//	for (auto& u : users)
//		input << u._id << _w() << "|" << _w() << u.f_name << " " << u.l_name << _w() << "|" << _w() << u.gender << _w() << "|" << _w() << u.DOB << _w() << "|\n";
//
//	return input;
//}
std::ostream& operator <<(std::ostream& input, const std::vector<User>& users)
{

#define _w() std::setw(15) // Sets width to 20
#define _w2() std::setw(10) // Sets width to 20
#define _w3() std::setw(5) // Sets width to 20

	input << "_id" << _w2() << "Name" << _w3() << "Gender" << _w() << "DOB";

	input << "\n\n";
	for (auto& u : users)
		input << u._id << _w2() << u.f_name << " " << u.l_name << _w3() << u.gender << _w() << u.DOB << '\n';

	return input;
}

int main()
{
	User user;
	user._id = 1;
	user.f_name = "James";
	user.l_name = "Kimani";
	user.gender = 'M';
	user.DOB = "1994-07-18";

	std::vector<User> Users;
	Users.push_back(user);

	std::cout << Users << std::endl;

	return 0;
}

