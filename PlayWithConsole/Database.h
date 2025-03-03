#pragma once
#include "Schema.h"

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
public:
private:
	Database () {}

	std::vector<User> Users;
};