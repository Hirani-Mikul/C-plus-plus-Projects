#pragma once
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <thread>

namespace Benchmark 
{

	struct ProfileResult {

		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};
	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor();

	public:

		void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		void EndSession();

		void WriteProfile(const ProfileResult& result);

		void WriteHeader();

		void WriteFooter();

		 

		static Instrumentor& Get();


	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;

	};

	class Timer {

	public:
		Timer(const char* name);
		
		~Timer();

	public:
		virtual void Stop();


	protected:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
		const char* m_TimerName;
		bool m_Stopped;
	};

	class InstrumentationTimer : public Timer
	{
	public:
		InstrumentationTimer(const char* name);

		~InstrumentationTimer();

	public:
		void Stop() override;
	};

}


//	USE MACROS TO EASY THE WRITING AND REPETITION OF THE CODE


//#define PROFILING 1
//#if PROFILING
//#define PROFILE_SCOPE(name) Benchmark::InstrumentationTimer Timer##__LINE__(name)
//#define PROFILE_BENCHMARK() PROFILE_SCOPE(__FUNCSIG__)
//#else 
//#define PROFILE_SCOPE(name)
//#endif