#pragma once
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>
#include <fstream>
#include <optional>


namespace Utils {

	template<typename Container>
	void WriteToCout(const Container& container, const char* delimiter = " ")
	{
		std::copy(
			container.begin(), container.end(),
			std::ostream_iterator< Container::value_type >(std::cout, delimiter)
		);
	}

	template<typename ContainerA, typename ContainerB, typename Pred>
	void CopyIf( const ContainerA& a, ContainerB& b, Pred pred )
	{
		std::copy_if( a.begin(), a.end(), std::back_inserter(b), pred );
	}

	template<typename Container, typename Pred>
	void RemoveIf(Container& a, Pred pred)
	{
		a.erase(
			std::remove_if( a.begin(), a.end(), pred ), a.end()
		);
	}

	template<typename ContainerA, typename ContainerB>
	void Move(ContainerA& a, ContainerB& b, int count = 1)
	{
		std::move( a.begin(), a.begin() + count, std::back_inserter(b) );
	}

	template<typename ContainerA, typename ContainerB, typename Pred>
	void MoveIf(ContainerA& a, ContainerB& b, Pred pred)
	{
		std::copy_if( 
			std::make_move_iterator(a.begin()),
			std::make_move_iterator(a.end()), 
			std::back_inserter(b),
			pred
			);
	}

	template<typename ContainerA, typename ContainerB, typename Pred>
	void Transform(const ContainerA& a, ContainerB& b, Pred pred )
	{
		std::transform( a.begin(), a.end(), std::back_inserter(b), pred );
	}

	template<typename Container, typename Pred>
	void Transform(Container& cont, Pred pred)
	{
		std::transform(cont.begin(), cont.end(), cont.begin(), pred);
	}

	template<typename ContainerA, typename ContainerB, typename ContainerC, typename Pred>
	void Transform( const ContainerA& a, const ContainerB& b, ContainerC& c, Pred pred )
	{
		std::transform( a.begin(), a.end(), b.begin(), std::back_inserter(c), pred );
	}

	template<class Container, class Predicate>
	void Partition_Copy( Container& src, Container& dest, Predicate p )
	{
		// Partition_copy returns a pair of two vectors, then make_move_iterator moves the elements to dest from src
		auto end = std::partition_copy
		( 
			std::make_move_iterator(src.begin()), std::make_move_iterator(src.end()), 
			src.begin(), 
			std::back_inserter(dest), 
			p 
		);

		// Cleans the unnecessary gaps in the src vector

		src.erase( end.first, src.end() );
	}

	template<class Container, class Predicate>
	void WriteToFile(const Container& cont, const char* fileName, Predicate pred = std::ios::trunc ) {
		
		std::fstream file;
		file.open(fileName, pred);

		for (auto& i : cont)
			file << i << '\n';

		file.close();

	} // What to write?, path

	template<class Container>
	void ReadFromFile( Container& cont, const char* fileName ) {
		
		std::ifstream file(fileName);

		unsigned int value;

		while (file >> value)
		{
			cont.push_back(value);
		}

		file.close();

	}

	// BINARY SEARCH USING LOWER_BOUND
	template<class Container>
	std::optional<std::size_t> Binary_Find( const Container& cont, const typename Container::value_type& v )
	{
		auto i = std::lower_bound(cont.begin(), cont.end(), v);
		return i != cont.end() && *i == v ? std::distance(cont.begin(), i) : std::optional<std::size_t>{};
	}
	template<class Container>
	int Binary_Find_String( const Container& cont, const std::string& text, int length )
	{
		int l = 0;
		int r = length - 1;

		while (l <= r)
		{
			int m = l + (r - 1) / 2; // Middle of the container

			//int res = -1000;
			int res = 100;

			if (text == (cont[m]))
			{
				res = 0;
			}

			// Check if text is present at mid
			if (res == 0)
			{
				return m;
			}

			// If text is greater, ignore left half
			if (text > (cont[m]))
			{

				l = m + 1;
			} 
			else {
				// If x is smaller, ignore right half
				//r = m - 1;
				l = m - 1;
			}

		}

		return -1;
	}
	template<class Container>
	int Binary_Find_String2(const Container& cont, const std::string& text, int length)
	{
		int low = 0;
		int high = length - 1;

		while (low <= high)
		{
			int mid = (low + high) / 2;

			if (text == cont[mid])
				return mid;
			else if (cont[mid] < text)
				low = mid + 1;
			else 
			high = mid - 1;
		}

		return -1;
	}

}


struct Values {

	static std::vector<int> GetNumbers() {

		std::vector<int> temp = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		return std::move(temp);

	};
	static std::vector<int> GetNumbers_iota( int numOfElements, int initialValue ) {
		std::vector<int>temp(numOfElements);

		std::iota( temp.begin(), temp.end(), initialValue );

		return std::move(temp);

	}
	static std::vector<int> GetNumbers(int min, int max, int numOfElements = 10) {

		std::vector<int> temp;
		temp.reserve(numOfElements);

		for (int i = 0; i <= numOfElements; i++)
		{
			temp.emplace_back(rand() % max * 2 + (min));
		}

		return std::move(temp);

	};
	static std::vector<int> GetRandomNumbers(int min, int max, int numOfElements = 1)
	{
		std::vector<int> temp;
		temp.reserve(numOfElements);

		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> d(min, max);

		for (int i = 0; i < numOfElements; i++)
		{

			temp.emplace_back(d(rng));
		}
		return std::move(temp);

	}
	static std::vector<std::string> GetText() {
		
		std::vector<std::string> temp = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };

		return std::move(temp);
	};

};