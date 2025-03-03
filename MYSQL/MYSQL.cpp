// MySqlTest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <mysql.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>

int qstate;

MYSQL* connectDB(const char* db_name)
{
	MYSQL* conn;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "pass", db_name, 3306, NULL, 0);

	if (conn)
	{
		std::puts("Successful connection to database");
		return conn;
	}
	else
	{
		std::puts("Connection to database has failed.\n");
		return conn;
	}

	system("cls");
}

int RunQuery(MYSQL* conn)
{
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL_FIELD* fld;

	if (!conn) return 0;

	const char* q = "SELECT f_name, l_name, gender FROM student";

	qstate = mysql_query(conn, q);

	if (qstate)
	{
		std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		return 0;
	}
	res = mysql_store_result(conn);
	int numOfFields = mysql_num_fields(res);


	for (int i = 0; i < numOfFields; i++)
	{
		fld = mysql_fetch_field(res);
		std::cout << std::setw(20) << fld->name;

	}
	std::cout << "\n\n";

	while (row = mysql_fetch_row(res))
	{
		for (int i = 0; i < numOfFields; i++)
			std::cout << std::setw(20) << row[i];

		std::cout << std::endl;
	}

	return 1;
}

int InsertRecord(MYSQL* conn)
{
	int id;
	std::string f_name, l_name, date;
	char gender;

	std::stringstream ss;

	std::cout << "Enter id: ";
	std::cin >> id;
	std::cout << "First name: ";
	std::cin >> f_name;
	std::cout << "Last name: ";
	std::cin >> l_name;
	std::cout << "Gender (F\\M): ";
	std::cin >> gender;
	std::cout << "DOB (YYYY-MM--DD): ";
	std::cin >> date;

	//ss << "INSERT INTO student VALUES ('"+id+"', '', '', '', '')";

	std::string query = "INSERT INTO student VALUES(";
	query += std::to_string(id) + ", \'" + f_name + "\', \'" + l_name  + "\', " + "\'" + gender + "\', DATE \'" + date + "\'";
	query += " )";

	const char* q = query.c_str();

	//std::cout << q;

	//return 0;

	qstate = mysql_query(conn, q);

	if (!qstate)
		std::cout << "Record inserted.\n";
	else
	{
		std::cout << "Operation failed: " << mysql_error(conn) << "\n";
		return 0;
	}

	return 1;
}

int main()
{
	std::string db_name = "test";

	//std::cout << "Enter database name to use: ";
	//std::cin >> db_name;

	MYSQL* conn = connectDB(db_name.c_str());

	if (!conn) return 0;

	//int result = RunQuery(conn);
	int flag = InsertRecord(conn);

	std::cin.ignore();
	std::cin.get();
	system("cls");

	int result = RunQuery(conn);


	std::cin.get();

	return 0;
}


/*if (conn) {

		std::string query = "SELECT * FROM student";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}*/