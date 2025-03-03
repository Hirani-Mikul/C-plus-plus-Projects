#pragma once
#include <string>
#include <vector>

class JSONArray; 
class JSONField; 
class JSONObject;

class JSONArray {

	std::vector<JSONObject> objects;

};

class JSONField {

	std::string name;
	std::string value;

};

class JSONObject {
	
	std::vector<JSONField> fields;
	std::vector<JSONArray> arrays;

	void append( JSONField field ) {
		fields.push_back(field);
	}
	void append(JSONArray arr) {
		arrays.push_back(arr);
	}

};

class JSON {

public:
	JSON(const JSON&) = delete;

	enum class TYPE {
		String,
		Array,
		Object,
		Integral,
		Floating,
		Boolean,
		Null,
	};

public:
	
	static JSON& Get() {
		static JSON Instance;

		return Instance;
	}

	static void parse() { Get()._Parse(); }

	template<class Container>
	static std::string stringify( const Container& data ) { return Get()._Stringify(data); }

private:

	void SetType(TYPE type) {

		if (type == Type)
			return;

		Type = type;
	}

	void _Parse() {}

	std::pair<std::string, std::string> to_string( const std::string& text ) {
	
		const auto index = text.find(separator);
		std::string name = text.substr(0, index);
		std::string value = text.substr(index + 1);

		return { name, value };
		
	}

	template<class Container>
	std::string _Stringify(const Container& data) {
		
		std::string result;
		result += "[\n";
		/*for (auto& d : data)
		{

		}*/
		
	}

public:

private:
	JSON() {}

	const char separator = ':';

	TYPE Type = TYPE::Null;

};