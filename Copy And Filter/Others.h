#pragma once
#include "Utils.h"

auto Split(const std::string& text, const std::string& delimiters) {
	// Using find_first_of

	std::vector<std::string> split;

	const auto FindNext = [&](const auto i) {

		return std::find_first_of(i, text.end(), delimiters.begin(), delimiters.end());
	};

	for (std::string::const_iterator i, i_prev = text.begin(); ; i_prev = i + 1)
	{
		i = FindNext(i_prev);
		split.emplace_back(i_prev, i);

		if (i == text.end())
			break;
	}

	return split;
}

int Compare(int a, int b, int flag) //  100, 200, 50
{
	if (flag == 1)
	{
		if (a > b) return 1;
		else return -1;
	}
	else if (flag == -1)
	{
		if (a < b) return 1;
		else return -1;
	}
	else return -1;
}


void MySort( std::vector<int>& a, int flag = 1 ) {

	const int length = a.size();

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if (Compare(a[j], a[j + 1], flag) > 0)
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}


void Swap(int& a, int& b) {

	int temp = a;
	a = b;
	b = temp;

}


struct Stuff {

	int num;
	std::string string;

	bool operator<( const Stuff& s ) const {

		if (num == s.num)
			return string < s.string;

		return num < s.num;

	}
	bool operator>(const Stuff& s) const {

		if (num == s.num)
			return string > s.string;

		return num > s.num;

	}

};

std::ostream& operator<<(std::ostream& o, const Stuff& t) {
	
	return o << "{ " << t.num << " : " << t.string << " }";

}