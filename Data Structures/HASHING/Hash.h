#include <iostream>
#include <list>

namespace Hash
{
	class HASHTABLE
	{

	public:

	public:
		bool isEmpty() const
		{
			int sum {};

			for (int i{}; i < hashGroups; i++)
			{
				sum += table[i].size();
			}

			if (sum) return false;

			return true;
		}

		int hashFunction(int key)
		{
			return key % hashGroups;
		}

		void Insert(int key, std::string value)
		{
			int hashValue = hashFunction(key);
			auto& cell = table[hashValue];
			auto bItr = std::begin(cell);

			bool keyExists = false;

			for (; bItr != cell.end(); bItr++)
			{
				if (bItr->first == key)
				{
					keyExists = true;
					bItr->second = value;
					std::cout << "[Warning]: Key exists. Value replaced.\n";
					break;
				}
			}

			if (!keyExists)
			{
				std::cout << "[INFO]: Item inserted.\n";
				cell.emplace_back(key, value);
			}

			return;
		}

		void Remove(int key)
		{
			int hashValue = hashFunction(key);
			auto& cell = table[hashValue];
			auto bItr = std::begin(cell);

			bool keyExists = false;

			for (; bItr != cell.end(); bItr++)
			{
				if (bItr->first == key)
				{
					keyExists = true;
					bItr = cell.erase(bItr);
					std::cout << "[Info]: Item removed.\n";
					break;
				}
			}

			if (!keyExists)
			{
				std::cout << "[Warning]: Item not found. Item not removed.\n";
			}

			return;
		}

		std::string Search(int key)
		{
			int hashValue = hashFunction(key);
			auto& cell = table[hashValue];

			auto bItr = cell.begin();

			for (; bItr != cell.end(); bItr++)
			{
				if (bItr->first == key)
				{
					return bItr->second;
				}
			}

			return "0\n";
		}

		void PrintTable()
		{
			for (int i{}; i < hashGroups; i++)
			{
				if (table[i].size() == 0) continue;

				auto bItr = table[i].begin();

				for (; bItr != table[i].end(); bItr++)
				{
					std::cout << "[Key: " << bItr->first << "] Value: " << bItr->second << "\n";
				}
			}
		}

	private:
		static const int hashGroups = 10;
		std::list<std::pair<int, std::string>> table[hashGroups];

	};
}