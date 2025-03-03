#pragma once
#include "RawData.h"
#include "Schema.h"

class Formatter 
{
public:
	Formatter(const Formatter&) = delete;

	static Formatter& Get()
	{
		static Formatter Instance;
		return Instance;
	}
public:

public:
	void I_ParseData() {}
	void I_StringifyData() {}

private:
	Formatter() {}
};