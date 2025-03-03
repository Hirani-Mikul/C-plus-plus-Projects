#pragma once
#include <Windows.h>
#include <unordered_map>
#include <tchar.h>

/*
	LIST

	Stores name and last write time of a file in unique map container in the UTF-8 version.

	These files are the files that were recently detected by directory watcher.
*/
class List
{
public:
	List() {

	}

	~List() {
		clear();
	}

private:
	// ArrayHasher is used internally to hash each wide character in the path and generate a unique hash value.
	struct ArrayHasher
	{
		std::size_t operator()(const TCHAR* path) const {

			std::size_t h = 0;

			int i = 0;

			while (path[i] != '\0')
			{
				h ^= std::hash<TCHAR>{}(path[i]) + 0x9e3779b9 + (h << 6) + (h >> 2);
				i++;
			}
			return h;
		}
	};

	// KeyComparator is internally used to compare each path from another path in the list. 
	struct KeyComparator
	{
		bool operator()(const TCHAR* key1, const TCHAR* key2) const
		{
			// _tcscmp, if returns 0, then the values matches.
			return (_tcscmp(key1, key2) == 0) ? true : false;
		}
	};

public:
	// Insert new paths. If the path exists return false.
	BOOL insert(const TCHAR* fileName, FILETIME ftWrite)
	{
		if (!contains(fileName))
		{
			m_paths[fileName] = ftWrite;

			auto el = m_paths.begin()->first;
			return TRUE;
		}

		return FALSE;
	}

	// Remove certain path from the list.
	BOOL remove(CONST TCHAR* fileName)
	{
		if (!contains(fileName)) return FALSE;

		// Clear the buffer in the memory.

		auto el = m_paths.find(fileName);
		delete[] el->first;

		// Remote the file name from the list.
		m_paths.erase(fileName);

		return TRUE;
	}

	// Fetches the first inserted file in the list.
	CONST TCHAR* getFirstElement() CONST { return m_paths.begin()->first; }

	// Clear the whole list and the buffer held in memory.
	void clear()
	{
		// First check if the list is empty or not.
		if (m_paths.size() <= 0) return;

		// Free the buffer.
		for (auto& el : m_paths)
			delete[] el.first;

		// Clear the container.
		m_paths.clear();

	}

	// Find a key in the list.
	bool contains(const TCHAR* key)
	{
		// If the key exists, it's iterator cannot be equal to the end of the list.
		return (m_paths.find(key) != m_paths.end());
	}

	// Get file name in ANSI standard.
	const char* getFileNameInANSI()
	{

		return new char[2];
	}

private:
	// Instead use unique_ptr
	std::unordered_map<CONST TCHAR*, FILETIME, ArrayHasher, KeyComparator> m_paths;
	
};