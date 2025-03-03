#pragma once
#include "Formatter.h"
#include "FileStream.h"


// STORES PATH OF THE TEXT FILES
namespace Path
{
	const char* USERS_DB = "usersDB.txt";
	const char* ADMINS_DB = "adminsDB.txt";
	const char* CARS_DB = "carsDB.txt";
	const char* REQUEST_DB = "Requests.txt";
	const char* LOCALSTORAGE = "LocalStorage.txt";
}

// ANOTHER SINGLETON
// SINGLETONS WORKS IN THE SAME WAY AS NAMESPACE
// THIS CLASSES CAN ALSO BE NAMESPACE

class Database
{
public:
	Database(const Database&) = delete;

	static Database& Get()
	{
		static Database Instance;

		return Instance;
	}

public:
	static void Initialize() { Get()._Initialize(); }

	// STATIC GETTERS
	static const std::vector<Request>* GetRequests(int id, char reqType) { return Get()._GetRequests(id, reqType); }

	static std::pair<int, bool> LoadLocalStorage() { return Get()._LoadLocalStorage(); }

	static NormalUser* GetUserById(int id) { return Get()._SearchUserByID(id); }

	static AdminUser* GetAdminUserById(int id) { return Get()._SearchAdminUserByID(id); }

	static Cart RequestToRent(int vehicle_id) { return Get()._RequestToRent(vehicle_id); }

	static void CompleteRequest(Cart cart) { Get()._CompleteRequest(cart); }

	static std::vector<Pending_Info> GetPendingInfo() { return Get()._GetPendingInfo(); }

	static bool ApproveRequest(int user_id, int vehicle_id, int numOfRequests) { return Get()._ApproveRequest(user_id, vehicle_id, numOfRequests); }


	// STATIC ACTION METHODS

	
	static NormalUser* ValidateUser(const std::string& username, const std::string& password) { return Get()._ValidateUser(username, password); }

	static AdminUser* ValidateAdminUser(const std::string& username, const std::string& password) { return Get()._ValidateAdminUser(username, password); }

	static bool AddUser(const std::string& username, const std::string& password, float deposit) { return Get()._AddUser(username, password, deposit); }

	static bool RequestToReturn(int u_id, int v_id, int numOfRequests) { return Get()._RequestToReturn(u_id, v_id, numOfRequests); }

	static void UpdateSystemOnReturnedVehicles() { Get()._UpdateSystemOnReturnedVehicles(); }


	// STATIC UPDATING METHODS

	static void UpdateNoramlUsers() { Get()._UpdateNormalUsers(); }
	static void UpdateAdminUsers() { Get()._UpdateAdminUsers(); }
	static void UpdateVehicles() { Get()._UpdateVehicles(); }
	static void UpdateUserDatas() { Get()._UpdateUserData(); }

	static void UpdateLocalStorage(int id, bool isAdmin) { Get()._UpdateLocalStorage(id, isAdmin); }

	// STATIC PRINTING METHODS
	static void LogUsers() { Get()._LogUsers(); }
	static void LogAdminUsers() { Get()._LogAdminUsers(); }
	static std::map<int, int> LogVehicles() { return Get()._LogVehicles(); }

private:

	void _Initialize()
	{
		// FETCHES ALL THE DATA FROM TEXT FILES
		_FetchDataFromFiles();
	}
	void _FetchDataFromFiles()
	{
		// Read data from text files (Returns JSON object).
		// Parse the JSON data into respective form
		// Store in the respective containers.

		Formatter::ParseUserObject(Users, FileStream::ReadFile(Path::USERS_DB));
		Formatter::ParseAdminData(AdminUsers, FileStream::ReadFile(Path::ADMINS_DB));
		Formatter::ParseCarData(Vehicles, FileStream::ReadFile(Path::CARS_DB));
		Formatter::ParseUserData(UserDatas, FileStream::ReadFile(Path::REQUEST_DB));

	}

	std::pair<int, bool> _LoadLocalStorage() {

		// Loads local storage 
		// And assigns the static "UserID and AdminID Counters" with respective counter values in text file
		// Finally returns CurrentUser_Id (Admin or Not admin)

		LocalStorage storage = Formatter::ParseLocalStorage(FileStream::ReadFile(Path::LOCALSTORAGE));

		Database::UserID_Counter = storage.User_Id_Counter;
		Database::AdminID_Counter = storage.Admin_Id_Counter;

		return { storage.CurrentUser_Id, storage.isAdmin };
	}

	void _UpdateLocalStorage( int id, bool isAdmin)
	{
		// Updates local storage with current user.
		// DONE DURING: LOGOUT, LOGIN and REGISTERING NEW USER

		LocalStorage storage;
		storage.CurrentUser_Id = id;
		storage.isAdmin = isAdmin;
		storage.User_Id_Counter = Database::UserID_Counter;
		storage.Admin_Id_Counter = Database::AdminID_Counter;

		FileStream::WriteToFile(Path::LOCALSTORAGE, Formatter::StringifyLocalStorage(storage));
	}

	std::vector<Request>* _GetRequests(int id, char reqType)
	{
		for (auto& data : UserDatas)
		{
			if (data.User_Id == id)
			{
				return data.GetAllRequests(reqType);
			}
		}
		return nullptr;
	}

	// START OF SEARCHING METHODS
	// Below methods are used to search for specific user, vehicle or userdata based on id or username

	NormalUser* _SearchUserByUsername(const std::string& username)
	{
		if (Users.size() <= 0) return nullptr;

		for (auto& user : Users)
			if (user.Username == username)
				return &user;

		return nullptr;
	}

	NormalUser* _SearchUserByID(int id)
	{
		for (auto& user : Users)
			if (user._id == id)
				return &user;

		return nullptr;
	}
	AdminUser* _SearchAdminUserByID(int id)
	{
		for (auto& user : AdminUsers)
			if (user._id == id)
				return &user;

		return nullptr;
	}

	Vehicle* _GetVehicleByID(int id)
	{
		for (auto& v : Vehicles)
		{
			if (v._id == id)
				return &v;
		}

		return nullptr;
	}

	AdminUser* _SearchAdminByUsername(const std::string& username)
	{
		for (auto& u : AdminUsers)
			if (u.Username == username)
				return &u;

		return nullptr;
	}

	// END OF SEARCHING METHODS


	// VALIDATING METHODS
	// To validate given credentials
	NormalUser* _ValidateUser( const std::string& username, const std::string& password )
	{
		NormalUser* found = _SearchUserByUsername(username);

		if (found)
		{
			if (found->Password == password)
				return found;
		}

		return nullptr;
	}

	AdminUser* _ValidateAdminUser(const std::string& username, const std::string& password)
	{
		AdminUser* found = _SearchAdminByUsername(username);

		if (found)
		{
			if (found->Password == password)
				return found;
		}

		return nullptr;
	}

	// END OF VALIDATING METHODS (ONLY TWO)

	Cart _RequestToRent(int vehicle_id)
	{
		Cart cart;

		cart.user = nullptr;
		cart.vehicle = _GetVehicleByID(vehicle_id);
		cart.numOfVehicles = 0;

		return cart;
	}

	void _CompleteRequest(Cart cart) 
	{
		cart.vehicle->Stock -= cart.numOfVehicles;

		std::vector<Request>* request = _GetRequests(cart.user->_id, 'P');

		if (request)
		{
			bool isRequestFound = false;

			for (auto& req : *request)
			{
				if (req.Vehicle_Id == cart.vehicle->_id)
				{
					isRequestFound = true;
					req.Count += cart.numOfVehicles;
				}
			}

			if (!isRequestFound)
			{
				Request newReq(cart.vehicle->_id, cart.vehicle->Model, cart.numOfVehicles);
				request->push_back(newReq);
			}
		}
		else
		{
			UserData data;

			data.User_Id = cart.user->_id;
			data.Pending.push_back(Request{ cart.vehicle->_id, cart.vehicle->Model, cart.numOfVehicles });

			UserDatas.push_back(data);
		}

		_UpdateNormalUsers();
		_UpdateVehicles();
		_UpdateUserData();

	}
	

	std::vector<Pending_Info> _GetPendingInfo()
	{
		std::vector<Pending_Info> Info;
		for (auto& data : UserDatas)
		{
			if (data.Pending.size() > 0)
			{
				Pending_Info info;
				NormalUser* user = _SearchUserByID(data.User_Id);

				info.Username = user->Username;
				info.User_Id = user->_id;
				info.NumOfRequests = data.Pending.size();

				Info.push_back(info);
			}
		}

		return Info;
	}

	bool _ApproveRequest(int user_id, int vehicle_id, int numOfRequests)
	{
		for (auto& data : UserDatas)
		{
			if (data.User_Id == user_id)
			{
				Request* req = data.GetRequest(vehicle_id, 'P');
				if (req->Count < numOfRequests) return false;

				req->Count -= numOfRequests;

				Request* rentedReq = data.GetRequest(vehicle_id, 'r');

				if (rentedReq)
					rentedReq->Count += numOfRequests;
				else
					data.Rented.push_back(Request{ vehicle_id, req->Model, numOfRequests });

				if (req->Count <= 0)
					data.Pending.erase(std::remove_if(data.Pending.begin(), data.Pending.end(), [&](Request& req) { return req.Count <= 0; }), data.Pending.end());

				return true;
			}

		}
		return false;
	}

	bool _RequestToReturn(int u_id, int v_id, int numOfRequests) {

		for (auto& data : UserDatas)
		{
			if (data.User_Id == u_id)
			{
				Request* req = data.GetRequest(v_id, 'r');

				if (numOfRequests > req->Count) return false;

				req->Count -= numOfRequests;

				Request* returnReq = data.GetRequest(v_id, 'R');

				if (returnReq) returnReq->Count += numOfRequests;
				else data.Returns.push_back(Request{ v_id, req->Model, numOfRequests });

				if (req->Count <= 0)
					data.Rented.erase(std::remove_if(data.Rented.begin(), data.Rented.end(), [&](Request& req) { return req.Count <= 0; }), data.Rented.end());

				return true;
			}
		}

		return false;
	}

	bool _AddUser( const std::string& username, const std::string& password, float deposit )
	{
		NormalUser* found = _SearchUserByUsername(username);

		if (found) return false;

		NormalUser user;

		user._id = Database::UserID_Counter;
		user.Username = username;
		user.Password = password;
		user.Balance = deposit;

		Users.push_back(user);

		FileStream::AppendToFile(Path::USERS_DB, Formatter::StringifyUserObject(user));

		Database::UserID_Counter++;

		return true;

	}

	// START: UPDAING METHODS
	// Simply stringifies the data, and handles it to the FileStream

	void _UpdateNormalUsers()
	{
		JSON data;

		for (auto& u : Users)
			data.append(Formatter::StringifyUserObject(u));

		FileStream::WriteToFile(Path::USERS_DB, data);
	}

	void _UpdateAdminUsers()
	{
		JSON data;

		for (auto& u : AdminUsers)
			data.append(Formatter::StringifyAdminUserObject(u));

		FileStream::WriteToFile(Path::ADMINS_DB, data);
	}

	void _UpdateVehicles()
	{
		JSON data;

		for (auto& v : Vehicles)
		{
			data.append(Formatter::StringifyVehicleObject(v));
		}

		FileStream::WriteToFile(Path::CARS_DB, data);
	}

	void _UpdateUserData()
	{

		JSON data;

		for (auto& userdata : UserDatas)
			data.append(Formatter::StringifyUserData(userdata));

		FileStream::WriteToFile(Path::REQUEST_DB, data);


	}

	void _UpdateSystemOnReturnedVehicles()
	{
		for (auto& data : UserDatas)
		{
			if (data.Returns.size() > 0)
			{
				for (auto& req : data.Returns)
				{
					Vehicle* v = _GetVehicleByID(req.Vehicle_Id);
					if (v) v->Stock += req.Count;
				}
				// EMPTY THEM
				data.Returns.clear();
			}
		}

		_UpdateUserData();
		_UpdateVehicles();
	}
	// END: UPDATING METHODS

	// SOME OF THE PRINTING METHODS (PRINTS THE DATA IN THE LOCAL CONTAINER)
	void _LogUsers() 
	{
		for (auto& user : Users)
			std::cout << user;
	}
	void _LogAdminUsers() 
	{
		for (auto& user : AdminUsers)
			std::cout << user;
	}
	std::map<int, int> _LogVehicles() 
	{
		return Utils::LogVehicles( Vehicles );
	}

private:
	Database() {}

	std::vector<NormalUser> Users;
	std::vector<AdminUser> AdminUsers;
	std::vector<Vehicle> Vehicles;

	std::vector<UserData> UserDatas;

	static int UserID_Counter;
	static int AdminID_Counter;
};

int Database::UserID_Counter = 0;
int Database::AdminID_Counter = 0;
