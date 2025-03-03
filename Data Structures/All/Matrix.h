#pragma once


#include <vector>

template<typename Object>

class matrix
{
public:
	matrix(int rows, int cols) : mat(rows)
	{
		for (auto& row : mat)
			row.resize(cols);
	}

	matrix(std::vector<std::vector<Object>> v) : mat{ v }  {}
	matrix(std::vector<std::vector<Object>>&& v) : mat{ std::move(v) } {}

public:


	const std::vector<Object>& operator [] (int row) const
	{
		return mat[row];
	}

	std::vector<Object>& operator[] (int row)
	{
		return mat[row];
	}

	int numOfRows() const { return mat.size(); }
	int numOfCols() const 
	{
		return numOfRows() ? mat[0].size() : 0;
	}
private:

	std::vector<std::vector<Object>> mat;
};