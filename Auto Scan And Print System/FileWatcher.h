#pragma once
#include <filesystem>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <string>
#include <functional>

enum class FileStatus { created, modified, erased };

class FileWatcher {


public:
	FileWatcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay) : path_to_watch{ path_to_watch }, delay{ delay } 
	{
		for (auto& file : std::filesystem::recursive_directory_iterator(path_to_watch))
		{
			paths_[file.path().string()] = std::filesystem::last_write_time(file);
		}
	}


	// Monitor for changes and if change occurs execute the user supplied function
	void start(const std::function<void (std::string, FileStatus)> &action) {
		while (running_)
		{
			// Wait for delay
			std::this_thread::sleep_for(delay);

			auto it = paths_.begin();

			while (it != paths_.end())
			{
				if (!std::filesystem::exists(it->first)) {
					action(it->first, FileStatus::erased);

					it = paths_.erase(it);
				}
				else it++;
			}

			// Check if a file was created or modified

			for (auto& file : std::filesystem::recursive_directory_iterator(path_to_watch))
			{
				auto current_file_last_write_time = std::filesystem::last_write_time(file);

				// File Creation
				if (!contains(file.path().string()))
				{
					paths_[file.path().string()] = current_file_last_write_time;
					action(file.path().string(), FileStatus::created);
				}
				// File Modification
				else {
					if (paths_[file.path().string()] != current_file_last_write_time) {
						paths_[file.path().string()] = current_file_last_write_time;
						action(file.path().string(), FileStatus::modified);
					}
				}
			}
		}
	}

private:
	std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
	std::string path_to_watch;
	std::chrono::duration<int, std::milli> delay;

	bool running_ = true;

	bool contains(const std::string& key)
	{
		auto el = paths_.find(key);
		return el != paths_.end();
	}
};
