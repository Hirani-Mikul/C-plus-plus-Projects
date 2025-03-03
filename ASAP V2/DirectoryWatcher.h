#pragma once

#pragma once
#include "Utils.h"
#include <unordered_map>
#include <thread>
#include <string>
#include <functional>

enum class FileStatus { created, modified, erased };

class DirectoryWatcher {

public:

public:
	DirectoryWatcher() {
		// Must create "IN" directory if it does not exist.
		path_to_watch = "./IN";
		delay = std::chrono::milliseconds(3000);

		// DD-MM-YYYY

		log_path = "./Logs/" + utils::getDate() + " log.txt";
	}

	DirectoryWatcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay) : path_to_watch{ path_to_watch }, delay{ delay }
	{
		log_path = "./Logs/" + utils::getDate() + " log.txt";
	}

	// Start should fetch all files

	// Monitor should detect new files.
	bool monitor(const std::function<void(std::string)> &action) {
		while (true)
		{
			// Wait for delay
			std::this_thread::sleep_for(delay);

			// Check if a file was created

			for (auto& file : std::filesystem::recursive_directory_iterator(path_to_watch))
			{
				auto current_file_last_write_time = std::filesystem::last_write_time(file);

				// File Creation

				if (!m_contains(file.path().string()))
				{
					paths_[file.path().string()] = current_file_last_write_time;

					action(file.path().string());

					// The file has been added to the process list
					// Remove the path from the paths_
					paths_.erase(file.path().string());

				}
				// File Modification
			}
		}

		return true;
	}

	void setDirectoryPath(const std::string& path)
	{
		path_to_watch = path;
	}
	void setDelayDuration(const std::chrono::milliseconds& dealy)
	{
		delay = std::chrono::duration(delay);
	}


private:

	std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
	std::string path_to_watch;
	std::chrono::duration<int, std::milli>  delay;

	bool m_contains(const std::string &key) {
		auto el = paths_.find(key);
		return el != paths_.end();
	}

	std::string log_path;
};
