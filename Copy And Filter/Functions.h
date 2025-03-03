#pragma once

#include "Others.h"
#include "Benchmark.h"
#include <execution>
#include <fstream>

#define PROFILE 1
#if PROFILE
#define Log(arg) Utils::WriteToCout(arg); std::cout << std::endl << std::endl
#define Log1(arg) Utils::WriteToCout(arg)
#else
#define Log(arg)
#endif // PROFILE

#define Log2(arg1, arg2) Utils::WriteToCout(arg1, arg2); std::cout << std::endl << std::endl
#define Print(value) std::cout << value
#define Space(num) for (int i = 0; i < num; i++) { std::cout << std::endl; }

static constexpr size_t LENGTH = 100000u;

void Part24()
{
	// MERGE - MERGES TWO SORTED RANGES
	// INPLACE_MERGE - MERGES TWO ORDERED RANGES IN PLACE

	std::vector<uint32_t> a = { 0, 1, 4, 4, 3, 2, 5, 8, 13, 15 };
	std::vector<uint32_t> b = { 1, 6, 7, 6, 9, 11, 10, 14, 12, 16 };
	std::vector<uint32_t> c;

	Print("a: ");
	Log(a);
	Print("b: ");
	Log(b);

	//sort
	Print("Sorting Ascending...\n");
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	Print("Sorted...\n");

	Print("Merging Ascending...\n");
	std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(c));
	Print("Merged...\n");
	
	Print("Acse-c: ");
	Log(c);
	
	c.clear();

	Print("Sorting Descending...\n");
	std::sort(a.begin(), a.end(), std::greater<uint32_t>{});
	std::sort(b.begin(), b.end(), std::greater<uint32_t>{});
	Print("Sorted...\n");

	Print("Merging Descending...\n");
	std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(c), std::greater<uint32_t>{});
	Print("Merged...\n");

	Print("Desc-c: ");
	Log(c);



}

void Part23()
{
	// BINARY SEARCH OF STRING

	std::string b[10] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };

	int length = 10;

	Print("b: [");
	for (int i = 0; i < length; i++)
	{
		if (i != 0)
			Print(", ");
		std::cout << b[i];
	}
	Print("]\n");

	std::string text = "Five";
	//auto index = Utils::Binary_Find_String(b, text, length);
	auto index = Utils::Binary_Find_String2(b, text, length);

	Space(2);
	index == -1 ? Print("Element not found") : Print("Element \"" << text <<"\" found at index " << index);
}

void Part22()
{
	auto a = Values::GetNumbers_iota(100, 100);

	int num;
	Print("Enter a number: ");
	std::cin >> num;

	if (auto i = Utils::Binary_Find(a, num))
		Print("Index of \""<< num << "\" is " << *i << '\n');
	else Print("Value does not exist in the container.\n");
}

void Part21()
{
	// BINARY SEARCH
	// LOWER_BOUND, UPPER_BOUND, EQUAL_RANGE(LOWER & UPPER BOUNDS)

	constexpr size_t n = LENGTH;
	std::vector<unsigned int> a;
	a.reserve(n);

	// Read Sorted List
	Print("Reading sorted list...\n");

	{
		Benchmark::Timer Timer("Reading took: ");
		Utils::ReadFromFile(a, "SortedNumbers.txt");
	}
	
	const auto target = a[n / 2 + 69];
	const auto begin = a.cbegin();
	const auto end = a.cend();
	
	// Finding Target using std::find
	{
		Print("\nFinding using std::find...\n");
		Benchmark::Timer Timer("std::find took...");
		auto i = std::find(begin, end, target);
		Print("std::find - Found " << *i << " at index " << std::distance(begin, i));
	}


	// Finding Target using std::equal_range
	{
		Print("\n\nFinding using binary equal_range search...\n\n");
		Benchmark::Timer Timer("Equal_Range took...");
		auto r = std::equal_range(begin, end, target);
		Print("std::equal_range - Found " << *r.first << " at index " << std::distance(begin, r.first));
	}

	// Finding Target using std::lower_bound
	{
		Print("\n\nFinding using binary lower bound search...\n\n");
		Benchmark::Timer Timer("Lower_Bound took...");
		auto i = std::lower_bound(begin, end, target);
		Print("std::lower_bound - Found " << *i << " at index " << std::distance(begin, i));
	}


	Print("\nFinished");
}

void Part20()
{

	constexpr size_t n = LENGTH;

	std::vector<unsigned int> a;
	a.reserve(n);

	Print("Generating " << n << " random numbers...");
	Space(1);
	{
		Benchmark::Timer Timer("Generating took: ");
		std::mt19937 range(std::random_device{}());
		std::generate_n( std::back_inserter(a), n, range );
	}

	Utils::WriteToFile(a, "UnsortedNumbers.txt", std::ios::app);

	Space(2);
	Print("Sorting random numbers...");
	Space(2);
	{
		Benchmark::Timer Timer("Sorting took: ");
		std::sort(std::execution::par_unseq, a.begin(), a.end());
	}
	Utils::WriteToFile(a, "SortedNumbers.txt", std::ios::app);


	Space(2);
	Print("Finished");
}

void Part19()
{
	// SORT, IS_SORTED, IS_SORTED_UNTIL,
	// STABLE_SORT(KEEPS THE ORDER RELATIVE IF TWO ELEMENTS ARE EQUAL)
	// PARTIAL_SORT (FASTER THAN SORT IF YOU WANT THE RANGE OF VALUE IN ORDER)
	// PARTIAL_SORT_COPY,
	// NTH_ELEMENT (PARTITIONS THE CONTAINER SUCH THAT ELEMENTS SMALLER ARE BEFORE THE GIVEN "NTH" ELEMENT AND ELEMENTS BIGGER ARE AFTER THE GIVEN "NTH" ELEMENT) (BUT ELEMENTS BEFORE AND AFTER ARE NOT RELATIVELY ORDERED)
	std::vector<int>   a         = { 2, 8, 1, 3, 5, 4, 9, 6, 7, 1 };
	std::vector<Stuff> stuffs  = { {4, "Flour"}, {2, "TV's"}, {100, "PS5 Console"}, {20, "Phones"}, {8, ""} };
	std::vector<Stuff> stuffs2 = { {4, "Flour"}, {2, "TV's"}, {100, "PS5 Console"}, {20, "Phones"}, {8, ""} };
	std::vector<Stuff> stuffs3 = { {4, "Flour"}, {20, "Intel"}, {2, "TV's"}, {100, "PS5 Console"}, {20, "Phones"}, {2, "Soap"},  {8, ""} };
	std::vector<Stuff> stuffs4 = { {4, "Flour"}, {20, "Intel"}, {2, "TV's"}, {100, "PS5 Console"}, {20, "Phones"}, {2, "Soap"},  {8, ""} };

	Print("a: "      );
	Log(   a         );
	Print("stuffs: " );
	Log(stuffs );
	Print("stuffs2: ");
	Log(stuffs2);
	Print("stuffs3: ");
	Log(stuffs3);
	Print("stuffs4: ");
	Log(stuffs4);

	std::sort(a.begin(), a.end());
	Print("Asce-a: ");
	Log(a);

	std::sort(a.begin(), a.end(), std::greater<int>{});
	Print("Desc-a: ");
	Log(a);

	//std::sort(stuffs.begin(), stuffs.end(), [](const auto& s1, const auto& s2) { return s1.num < s2.num; });
	std::sort(stuffs.begin(), stuffs.end(), std::greater<Stuff>{});
	std::sort(stuffs3.begin(), stuffs3.end(), std::greater<Stuff>{});
	std::stable_sort(stuffs2.begin(), stuffs2.end(), std::greater<Stuff>{});
	std::partial_sort(stuffs4.begin(), stuffs4.begin() + 4, stuffs4.end(), std::greater<Stuff>{});

	Print("Desc-stuffs: ");
	Log(stuffs);
	Print("Desc-stuffs2: ");
	Log(stuffs2);
	Print("Desc-stuffs3: ");
	Log(stuffs3);
	Print("Partial-Desc-stuffs4: ");
	Log(stuffs4);
}

void Part18()
{
	// MY WAY OF SORTING
	//auto a = Values::GetRandomNumbers(10, 1000, 10);
	std::vector<int> a = {2, 8, 1, 3, 5, 4, 9, 6, 7, 1};

	Print("a: ");
	Log(a);

	MySort( a, 1 );
	Print("Asce-A: ");
	Log(a);
	Space(1);

	MySort(a, -1);
	Print("Desc-A: ");
	Log(a);
	Space(1);
	//Print("a: ");
	//Log(a);

}

void Part17()
{
	// PARTITION, STABLE_PARTITION, IS_PARTITIONED, PARTITION_COPY, PARTITION_POINT

	std::vector<Stuff> stuffs = { {4, "Flour"}, {2, "TV's"}, {100, "PS5 Console"}, {20, "Phones"}, {8, ""} };
	std::vector<Stuff> stuffs2;

	auto a = Values::GetText();
	auto b = Values::GetNumbers();
	auto c = Values::GetNumbers();

	Print("a: ");
	Log(a);
	Print("b: ");
	Log(b);
	Print("c: ");
	Log(c);
	Print("stuffs: [ ");
	Log1(stuffs);
	Print(" ]");
	Space(2);

	// After Partitioning

	std::partition(a.begin(), a.end(), [](const std::string& s) {
		return std::any_of(s.begin(), s.end(), [](const char c) { return c == 'e'; });
		});

	std::partition(b.begin(), b.end(), [](const int n) { return n % 2 == 0; });
	std::stable_partition(c.begin(), c.end(), [](const int n) { return n % 2 == 0; });

	Utils::Partition_Copy(stuffs, stuffs2, []( const auto& ss ) { return ss.num > 10; });

	Print("Partitioned-a: ");
	Log(a);
	Print("Partitioned-b: ");
	Log(b);
	Print("Stable-Partitioned-c: ");
	Log(c);

	Print("stuffs: [ ");
	Log1(stuffs);
	Print(" ]");
	Space(2);

	Print("stuffs2: [ ");
	Log1(stuffs2);
	Print(" ]");
	Space(2);
}

void Part16()
{
	// REVERSE, REVERSE_COPY, ROTATE, ROTATE_COPY, SHUFFLE, NEXT_PERMUTATION, PREV_PERMUTATION, IS_PERMUTATION 
	//(SHIFT_RIGHT, SHIFT_LEFT (C++ 20))
	
	auto a = Values::GetText();
	auto b = Values::GetNumbers_iota( 10, 20 );
	std::vector<int> c;

	auto d = Values::GetNumbers();
	auto e = Values::GetNumbers();

	auto p = Values::GetNumbers();

	std::string s = "abcd";
	std::string s2 = "dcba";
	std::string s3 = "caab";

	std::vector<std::string> permuted_s;


	Print("a: ");
	Log(a);
	Print("b: ");
	Log(b);
	Print("d: ");
	Log(d);
	Print("e: ");
	Log(e);
	Print("p: ");
	Log(p);

	Print("s: ");
	Print(s);
	Space(2);
	Print("s2: ");
	Print(s2);
	Space(2);
	Print("s3: ");
	Print(s3);
	Space(2);

	std::reverse(a.begin(), a.end());
	std::reverse_copy(b.begin(), b.end(), std::back_inserter(c));

	std::rotate(d.begin(), d.begin() + 4, d.end());

	std::mt19937 rng(std::random_device{}());

	std::shuffle( e.begin(), e.end(), rng );

	std::next_permutation(p.begin(), p.end());


	while (std::next_permutation(s.begin(), s.end()))
	{
		permuted_s.push_back(s);
	}


	std::next_permutation( s.begin(), s.end() );

	Print("Reverse-a: ");
	Log(a);
	Print("Reverse-b: ");
	Log(c);
	Print("Rotated-d: ");
	Log(d);
	Print("Shuffled-e: ");
	Log(e);
	Print("All Permutated-s: [");

	for (int i = 0; i < permuted_s.size(); i++)
	{
		std::cout << permuted_s[i];
		if (i != permuted_s.size() - 1)
			std::cout << ", ";
	}
	Print(" ]");
	Space(2);

	

	Print("Permuted-p: ");
	Log(p);

	// Check if s is permutation of s2 and if s2 is the permutation of s3

	std::cout << "s is Permutation of s2: " << std::boolalpha << std::is_permutation(s.begin(), s.end(), s2.begin(), s2.end());
	Space(1);
	std::cout << "s2 is Permutation of s3: " << std::boolalpha << std::is_permutation(s2.begin(), s2.end(), s3.begin(), s3.end());
	Space(1);

}

void Part15()
{
	// FILL, IOTA(INCLUDE NUMERIC HEADER), GENERATE, GENERATE_N, SAMPLE

	/*
		FILL - FILLS THE CONTAINER WITH THE VALUE GIVEN
		IOTA - FILLS THE CONTAINER WITH INCREASING VALUE (++VALUE)
		GENERATE_N - FILLS THE CONTAINER WITH VALUES WITHIN THE RANGE GIVEN
		SAMPLE - RETURNS (X) NUMBER OF ELEMENTS RANDOMLY FROM THE CONTAINER (POPULATION)
	*/

	auto a = Values::GetNumbers_iota(10, 100);
	Print("A: ");
	Log(a);

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> r(100, 1000);

	std::vector<int> b;
	std::generate_n(std::back_inserter(b), 5, [&]() { return r(rng); });
	Print("B: ");
	Log(b);

	std::vector<int> c;
	std::generate_n(std::back_inserter(c), 10, [val = 10]() mutable {
		
		auto old = val;
		val += 10;
		return old;

	});
	Print("C: ");
	Log(c);

	auto d = Values::GetRandomNumbers(-1000, 1000, 10);
	Print("D: ");
	Log(d);

	auto e = Values::GetText();
	std::vector<std::string> e_sample;
	std::sample( e.begin(), e.end(), std::back_inserter(e_sample), 5, rng );
	Print("E: ");
	Log(e);
	Print("E_Sample: ");
	Log(e_sample);
}

void Part14()
{
	// FINDING ELEMENTS IN THE CONTAINER
	// FIND, FIND_IF, SEARCH, SEARCH_N, FIND_FIRST_OF, MISMATCH, ADJACENT_FIND, FIND_END

	auto a = Values::GetNumbers();
	auto b = Values::GetText();
	std::vector<std::string> c = { "One", "Two", "Three", "Four", "One", "Five", "Six", "Seven", "One", "Eight", "Nine", "Ten" };

	std::string d = "Hirani,Mikul.Premji*138730(Hello";
	std::string delimiter = "(?!,.*";
	std::string delimiter2 = ",.*(";

	Print("A: ");
	Log(a);
	Print("B: ");
	Log(b);
	Print("C: ");
	Log(c);
	Print("D: ");
	Print(d);
	Space(2);

	// Find returns the iterator
	const auto i = std::find(a.begin(), a.end(), 4);
	const auto i2 = std::find( b.begin(), b.end(), "Six" );
	Print("Index of 4 is: ");
	Print( i - a.begin() );
	Space(2);
	Print( "Index of \"Six\" is: " );
	Print(i2 - b.begin());
	Space(2);

	// Find the iterator for last match using reverse iterator
	//const auto i = std::find( a.rbegin(), a.rend() );
	const auto i3 = std::find( c.rbegin(), c.rend(), "One");
	Print("Index of \"Four\" is: ");
	Print(c.rend() - i3 - 1);
	Space(2);

	// Find_First_Of returns the iterator of the first delimiter in the string

	const auto i4 = std::find_first_of(d.begin(), d.end(), delimiter.begin(), delimiter.end());
	Print("Position of the first delimiter is: ");
	Print(i4 - d.begin());
	Space(2);


	const auto split = Split(d, delimiter2);
	Log2(split, " | ");

	// Search
	const std::string haystack = "jfksdjaljjeiwo2kjdsa23jals";
	const std::string needle = "als";

	const auto i5 = std::search( haystack.begin(), haystack.end(), needle.begin(),needle.end());
	Print("Position of the needle is at: ");
	Print(i5 - haystack.begin());
	Space(2);

	// Adjacent_Find
	const std::vector<int> x = { 1, 1, 3, 6, 9, 11, 13, 13, 15, 17, 19 };
	const auto i6 = std::adjacent_find( x.begin(), x.end() );
	Print("Two similar adjacent elements is at position: ");
	Print(i6 - x.begin());
	Space(2);

	// Adjacent_Find using unary predicate
	const auto i7 = std::adjacent_find(x.begin(), x.end(), [](const int x1, const int x2) { return x1 + x1 == x2; });
	Print("Position where the number + itself gives the next element value: ");
	Print(i7 - x.begin());
	Space(2);
}

void Part13()
{
	// COUNT, COUNT_IF, ALL_OF, ANY_OF, NONE_OF
	std::vector<int> a = { 1, 2, 3, 4, 5, 6, 2, 22, 7, 8, 4, 9, 10 };

	std::cout << "A: ";
	Log(a);

	// Counts the number of times the value appears in the container
	std::cout << "Count: " << std::count(a.begin(), a.end(), 2) << std::endl << std::endl;

	// Counts the number of elements that matches the condition
	std::cout << "Count_If: " << std::count_if(a.begin(), a.end(), [](auto n) { return n < 5; }) << std::endl << std::endl;

	// Returns true if all of the element matches the criteria
	std::cout << "All_Of: " << std::boolalpha << std::all_of(a.begin(), a.end(), [](auto n) { return n < 10; }) << std::endl << std::endl;

	// Returns true if any of the element matches the criteria
	std::cout << "Any_Of: " << std::boolalpha << std::any_of(a.begin(), a.end(), [](auto n) { return n < 4; }) << std::endl << std::endl;

	// Returns true if none of the element matches the criteria
	std::cout << "None_Of: " << std::boolalpha << std::none_of(a.begin(), a.end(), [](auto n) { return n > 100; }) << std::endl << std::endl;

}

void Part12()
{
	// FOR EACH MODIFIER, MODIFIES EACH ELEMENT OF CONTAINER
	std::vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::cout << "A: ";
	Log(a);

	std::for_each(a.begin(), a.begin() + 4, [](int& num) { return num *= 2; });

	// After Modifying
	std::cout << "A: ";
	Log(a);
}

void Part11()
{
	// TRANFORM ELEMENTS OF TWO CONTAINERS AND RETURN RESULT IN OTHER CONTAINER
	std::vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> b = { 20, 100, 342, 54, 23, 1, 34, 53, 1, 99 };
	std::vector<int> c;
	std::vector<int> d;

	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);

		Utils::Transform(a, b, c, [](const int a, const int b) { return a + b; });
	Utils::Transform(a, b, d, [](const int a, const int b) { return std::max(a, b); });

	// AFTER TRANFORMING
	std::cout << "After Transforming: \n\n";
	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);
	std::cout << "C: ";
	Log(c);
	std::cout << "D: ";
	Log(d);
}

void Part10()
{
	// TRANSFORM AND REPLACE EACH ELEMENT
	std::string a = "My name is Mikul Hirani.";

	std::cout << "A: " << a;
	std::cout << std::endl << std::endl;

	Utils::Transform(a, std::toupper);
	std::cout << "A: " << a;
	std::cout << std::endl << std::endl;

}

void Part9()
{
	// TRANSFORM ELEMENTS AND RETURN IN NEW CONTAINER

	std::string a = "My name is Mikul Hirani.";
	std::string b;

	std::cout << "A: " << a;
	std::cout << std::endl << std::endl;

	Utils::Transform(a, b, std::toupper);
	std::cout << "A: " << a;
	std::cout << std::endl << std::endl;
	std::cout << "B: " << b;
	std::cout << std::endl << std::endl;

}

void Part8()
{
	// REMOVING ELEMENTS THAT ARE SAME IN CONSECUTIVE ORDER
	/*
		IF THE DUPLICATE IS NOT IN CONSECUTIVE ORDER, IT WILL NOT REMOVE

		EXAMPLE:

		std::vector<std::string> b = { "0", "1", "1", "2" , "3", "0" , "4" , "5" , "6" , "7", "7" , "8" , "9", "0" , "10" };

		"0" WILL NOT BE REMOVED

		SOLUTION:

		FIRST SORT THEM IN ORDER THEN REMOVE
	*/

	std::vector<std::string> b = { "0", "1", "1", "2" , "3" , "4" , "5" , "6" , "7", "7" , "8" , "9" , "10" };

	std::vector<int> c = { 0, 1, 2, 3, 4, 4, 5, 5, 6, 7, 8, 9, 9, 10 };

	Log(b);
	std::cout << "C: ";
	Log(c);
	
	// Replace

	c.erase(std::unique(c.begin(), c.end()), c.end());
	b.erase(std::unique(b.begin(), b.end()), b.end());

	std::cout << "After Removing Same Element" << std::endl;
	std::cout << "B: ";
	Log(b);
	std::cout << "C: ";
	Log(c);
}

void Part7()
{
	// REPLACING ELEMENTS FROM CONTAINER WITH THE VALUE PASSED IF CONDITION IS MET
	std::vector<std::string> a = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
	std::vector<std::string> b = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };
	std::vector<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


	std::cout << "A: ";
	Log(c);
	std::cout << "B: ";
	Log(b);
	std::cout << "C: ";
	Log(c);

	// Replace

	std::replace_if(c.begin(), c.end(), [](const int& num) { return num % 2 == 0; }, 0);

	std::cout << "After Replacing" << std::endl;
	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);
	std::cout << "C: ";
	Log(c);
}

void Part6()
{
	// REMOVING ELEMENTS FROM CONTAINER IF CONDITION IS MET
	std::vector<std::string> a = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
	std::vector<std::string> b = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };
	std::vector<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);
	std::cout << "C: ";
	Log(c);

		//Utils::RemoveIf(a, [](const std::string& str) { return std::count(str.begin(), str.end(), 'n') == 0; });
		Utils::RemoveIf(a, [](const std::string& str) { return std::none_of(str.begin(), str.end(), [](char l) { return l == 'n'; }); });

	Utils::RemoveIf(c, [](const int num) { return num % 2 != 0; });


	std::cout << "After Removing" << std::endl;
	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);
	std::cout << "C: ";
	Log(c);
}

void Part5()
{
	// SWAPING TWO RANGES OF ELEMENTS
	std::vector<std::string> a = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
	std::vector<std::string> b = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };

	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);

	// Swap
	std::swap_ranges(a.begin(), a.end(), b.begin());

	std::cout << "After Swapping" << std::endl;
	std::cout << "A: ";
	Log(a);
	std::cout << "B: ";
	Log(b);
}

void Part4()
{
	// MOVING ELEMENTS FROM ONE CONTAINER TO ANOTHER BASED ON CONDITION
	std::vector<std::string> a = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
	std::vector<std::string> b = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };

	std::vector<std::string> c;

	Utils::MoveIf(a, c, [](const std::string& str) { return str.size() > 4; });

	Log2(a, " | ");
	Log(c);

}

void Part3()
{
	// MOVING ELEMENTS FROM ONE CONTAINER TO ANOTHER
	std::vector<std::string> a = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
	std::vector<std::string> b = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };

	std::vector<std::string> c;
	std::move(a.begin(), a.begin() + 5, std::back_inserter(c));
	//std::move(a.begin(), a.begin() + 6, b.begin());

	Log2(a, " | ");
	Log(c);
}

void Part2()
{
	// COPYING ELEMENTS IF THE IS MET THE CONDITION

	std::string a = "WhaT iS YouR name PleAsE?";
	std::string b = "I don'T KNow mY nAmE.";

	std::string c; // Upper case

	Utils::CopyIf(a, c, std::isupper);

	c.append("----");

	Utils::CopyIf(b, c, std::isupper);

	Log(c);


}

void Part1()
{
	// Copying elements between certain range
	std::vector<std::string> a = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
	std::vector<std::string> b = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };


	std::vector<std::string> c;
	std::vector<std::string> d = { "0", "1", "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "10" };
	std::copy_n(a.begin(), a.size(), std::back_inserter(c));

	//Utils::WriteToCout(c);
	//std::cout << std::endl;
	Log(c);
}