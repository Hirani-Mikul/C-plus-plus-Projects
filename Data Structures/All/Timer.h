#pragma once
#include <chrono>
#include <iostream>

class Timer {
public:
	Timer(const char* name) : m_TimerName{ name }, m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	};

	~Timer()
	{
		if (!m_Stopped) Stop();
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();

		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;

		double ms = duration * 0.001;

		std::cout << m_TimerName << " took: " << ms << "ms.\n";

		m_Stopped = true;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

	const char* m_TimerName;
	bool m_Stopped;
};