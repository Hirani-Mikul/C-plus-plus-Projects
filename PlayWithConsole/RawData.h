#pragma once
#include <vector>
#include <string>

class RawData
{
public:
	RawData(const RawData&) = delete;

	static RawData& Get() {
		static RawData Instance;
		return Instance;
	}

	template<class T>
	static T GetTextData() { return Get().I_GetTextData(); }

	template<class T>
	static T GetParsedData() { return Get().I_GetParsedData(); }

	static void SetTextData(const std::string& data) { Get().I_SetTextData(data); }

	static void SetParsedData(const std::string& data) { Get().I_SetParsedData(data); }

public:
	auto I_GetTextData() { return std::move(TextData); }
	auto I_GetParsedData() { return std::move(ParsedData); }
	void I_SetTextData( const std::string& data ) {
		TextData.push_back(data);
	}
	void I_SetParsedData( const std::string& data ) {
		ParsedData.push_back(data);
	}

private:
	RawData() {}
	std::vector<std::string> TextData;
	std::vector<std::string> ParsedData;
};