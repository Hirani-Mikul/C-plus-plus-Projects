#pragma once

#include <vector>
#include "Utils.h"
#include "json.hpp"

using json::JSON;

// THIS SINGLETON CLASS IS USED FOR FORMATTING THE JSON DATA.
// USED TO STRINGIFY AND PARSE JSON DATA.
// FOR THE PURPOSE TO STORE THE DATA IN TEXT FILE AND IN DATABASE WHEN RETRIEVED

class Formatter {

public:
	Formatter(const Formatter&) = delete;

	static Formatter& Get() {
		static Formatter Instance;
		return Instance;
	}

public:

	// using template to avoid writing long types.
	// can work without it, but have to specify the type

	template<class DestinationContainer>
	static void ParseCarData(DestinationContainer& cont, JSON data) { Get()._ParseCarData(cont, data); }

	template<class DestinationContainer>
	static void ParseUserObject(DestinationContainer& cont, JSON data) { Get()._ParseUserObject(cont, data); }

	template<class DestinationContainer>
	static void ParseAdminData(DestinationContainer& cont, JSON data) { Get()._ParseAdminData(cont, data); }

	template<class DestinationContainer>
	static void ParseUserData(DestinationContainer& cont, JSON data) { Get()._ParseUserData(cont, data); }

	static LocalStorage ParseLocalStorage(JSON rawdata) { return Get()._ParseLocalStorage(rawdata); }

	static JSON StringifyUserObject(const NormalUser& user) { return Get()._StringifyUserObject(user); }
	static JSON StringifyAdminUserObject(const AdminUser& user) { return Get()._StringifyAdminUserObject(user); }
	static JSON StringifyVehicleObject(const Vehicle& vehicle) { return Get()._StringifyVehicleObject(vehicle); }
	static JSON StringifyUserData(const UserData& req) { return Get()._StringifyUserData(req); }
	static JSON StringifyLocalStorage(const LocalStorage& storage) { return Get()._StringifyLocalStorage(storage); }



private:

	template<class DestinationContainer>
	void _ParseCarData(DestinationContainer& cont, JSON cardata) {

		cont.reserve(cardata.length());

		for (int i = 0; i < cardata.length(); i++)
		{
			JSON data = cardata[i];

			int id = data["_id"].ToInt();
			auto model = data["Model"].ToString();
			float amount = data["Price"].ToFloat();
			int stock = data["Stock"].ToInt();

			cont.emplace_back(id, model, amount, stock);
		}

	}

	template<class DestinationContainer>
	void _ParseUserObject(DestinationContainer& cont, JSON userdata)
	{
		if (userdata.IsNull()) return;

		cont.reserve(userdata.length());

		for (int i = 0; i < userdata.length(); i++)
		{
			NormalUser user;

			JSON data = userdata[i];

			user._id = data["_id"].ToInt();
			user.Username = data["Username"].ToString();
			user.Password = data["Password"].ToString();
			user.Balance = data["Balance"].ToFloat();

			cont.emplace_back(user);

		}

	}

	template<class DestinationContainer>
	void _ParseAdminData(DestinationContainer& cont, JSON admindata)
	{
		cont.reserve(admindata.length());

		for (int i = 0; i < admindata.length(); i++)
		{
			AdminUser user;

			JSON data = admindata[i];

			user._id = data["_id"].ToInt();
			user.Username = data["Username"].ToString();
			user.Password = data["Password"].ToString();

			cont.emplace_back(user);
		}
	}

	template<class DestinationContainer>
	void _ParseUserData(DestinationContainer& cont, JSON userdata)
	{
		if (userdata.IsNull()) return;
		cont.reserve(userdata.length());
		
		for (int i = 0; i < userdata.length(); i++)
		{
			UserData UserInfo;

			JSON data = userdata[i];

			UserInfo.User_Id = data["User_Id"].ToInt();

			int numOfRented = data["Rented"].length();
			int numOfPending = data["Pending"].length();
			int numOfReturns = data["Returns"].length();

			if (numOfRented > 0)
			{
				UserInfo.Rented.reserve(numOfRented);

				for (int j = 0; j < numOfRented; j++)
				{
					auto reqData = data["Rented"][j];

					UserInfo.Rented.emplace_back(reqData["Vehicle_Id"].ToInt(), reqData["Model"].ToString(), reqData["Count"].ToInt());
				}
			}
			if (numOfPending > 0)
			{
				UserInfo.Pending.reserve(numOfPending);

				for (int j = 0; j < numOfPending; j++)
				{
					auto reqData = data["Pending"][j];

					UserInfo.Pending.emplace_back(reqData["Vehicle_Id"].ToInt(), reqData["Model"].ToString(), reqData["Count"].ToInt());
				}
			}
			if (numOfReturns > 0)
			{
				UserInfo.Returns.reserve(numOfReturns);

				for (int j = 0; j < numOfReturns; j++)
				{
					auto reqData = data["Returns"][j];

					UserInfo.Returns.emplace_back(reqData["Vehicle_Id"].ToInt(), reqData["Model"].ToString(), reqData["Count"].ToInt());
				}
			}

			cont.emplace_back(UserInfo);
		}


		//JSON req = data[i];
		//cont.emplace_back(req["Vehicle_Id"].ToInt(), req["Model"].ToString(), req["Count"].ToInt());
	}

	LocalStorage _ParseLocalStorage(JSON rawData)
	{
		LocalStorage storage;

		storage.isAdmin = rawData["isAdmin"].ToBool();
		storage.CurrentUser_Id = rawData["CurrentUser_Id"].ToInt();
		storage.User_Id_Counter = rawData["User_Id_Counter"].ToInt();
		storage.Admin_Id_Counter = rawData["Admin_Id_Counter"].ToInt();

		return storage;

	}

	JSON _StringifyUserObject(const NormalUser& user)
	{
		JSON Info{
			"_id", user._id,
			"Username", user.Username,
			"Password", user.Password,
			"Balance", user.Balance,
		};

		return Info;
	}

	JSON _StringifyUserData(const UserData& data)
	{
		JSON Req{
			"User_Id", data.User_Id,
			"Rented", json::Array(),
			"Pending", json::Array(),
			"Returns", json::Array()
		};

		if (data.Rented.size() > 0)
			for (auto& req : data.Rented)
				if (req.Count > 0)
					Req["Rented"].append(JSON{
						"Vehicle_Id", req.Vehicle_Id,
						"Model", req.Model,
						"Count", req.Count
						});

		if (data.Pending.size() > 0)
			for (auto& req : data.Pending)
				if (req.Count > 0)
					Req["Pending"].append(JSON{
						"Vehicle_Id", req.Vehicle_Id,
						"Model", req.Model,
						"Count", req.Count
						});

		if (data.Returns.size() > 0)
			for (auto& req : data.Returns)
				if (req.Count > 0)
					Req["Returns"].append(JSON{
						"Vehicle_Id", req.Vehicle_Id,
						"Model", req.Model,
						"Count", req.Count
						});

		return Req;
		
	}

	JSON _StringifyAdminUserObject(const AdminUser& user)
	{
		JSON Info{
			"_id", user._id,
			"Username", user.Username,
			"Password", user.Password,
		};

		return Info;
	}

	JSON _StringifyVehicleObject(const Vehicle& vehicle)
	{
		JSON Info{ "_id", vehicle._id, "Model", vehicle.Model, "Price", vehicle.Price, "Stock", vehicle.Stock };

		return Info;
	}

	JSON _StringifyLocalStorage(const LocalStorage& storage)
	{
		JSON data{
			"isAdmin", storage.isAdmin,
			"CurrentUser_Id", storage.CurrentUser_Id,
			"User_Id_Counter", storage.User_Id_Counter,
			"Admin_Id_Counter", storage.Admin_Id_Counter
		};

		return data;
	}


private:
	Formatter() {}

};