#pragma once


#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Schema.h"
#include "json.hpp"

using json::JSON;

class Formatter {

public:
	Formatter(const Formatter&) = delete;

	static Formatter& Get() {
		static Formatter Instance;
		return Instance;
	}
	
	static void ParseUserData(const std::string rawData, std::vector<NormalUser>& users) { Get()._ParseUserData(rawData, users); }
	static JSON StringifyUserData(const std::vector<NormalUser>& users) { return Get()._StringifyUserData(users); }


public:
private:

	JSON _StringifyUserData( const std::vector<NormalUser>& users ) { 
		
		JSON Data;
		for (auto& u : users)
		{
			JSON requests;
			
			if (u.Requests.size() > 0)
			{
				for (auto& r : u.Requests)
				{
					requests.append(JSON{ "Model", r.Model, "Count", r.Count });
				}
			}
			else
				requests = json::Array();

			JSON Info(
				{
					"Username", u.Username,
					"Password", u.Password,
					"Balance", u.Balance,
					"Requests", requests				
				}
			);

			Data.append(Info);
		}
		return Data;
	}
	void _ParseUserData( const std::string rawData, std::vector<NormalUser>& users ) {
		
		JSON Data = JSON::Load(rawData);

		users.reserve(Data.length());
		
		for (int i = 0; i < Data.length(); i++)
		{
			NormalUser user;

			JSON data = Data[i];

			user.Username = data["Username"].ToString();
			user.Password = data["Password"].ToString();
			user.Balance = data["Balance"].ToFloat();

			int numOfRequests = Data[i]["Requests"].length();

			if (numOfRequests > 0)
			{
				user.Requests.reserve(numOfRequests);

				for (int j = 0; j < numOfRequests; j++)
				{
					auto model = Data[i]["Requests"][j]["Model"].ToString();
					auto count = Data[i]["Requests"][j]["Count"].ToInt();
					user.Requests.emplace_back(model, count);
				}
			}

			users.push_back(user);

		}


	}
	

private:
	Formatter() {}

};