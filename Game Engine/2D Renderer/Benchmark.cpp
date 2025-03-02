#include "Benchmark.h"

namespace Benchmark {

	// Instrumentor
	Instrumentor::Instrumentor() : m_CurrentSession(nullptr), m_ProfileCount(0){}

	Instrumentor& Instrumentor::Get() {

		static Instrumentor* instance = new Instrumentor();

		return *instance;
	}

	void Instrumentor::BeginSession(const std::string& name, const std::string& filepath) {
		
		m_OutputStream.open(filepath);
		WriteHeader();
		m_CurrentSession = new InstrumentationSession{ name };

	}
	void Instrumentor::EndSession()
	{
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;
	}

	void Instrumentor::WriteProfile( const ProfileResult& result )
	{
		if (m_ProfileCount++ > 0)
			m_OutputStream << ", ";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.ThreadID << ",";
		m_OutputStream << "\"ts\":" << result.Start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	void Instrumentor::WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
		m_OutputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	// TIMER DEFINITION
	Timer::Timer( const char* name ) : m_TimerName(name), m_Stopped(false) {
	
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}
	Timer::~Timer() 
	{
		if (!m_Stopped)
			Stop();
	}

	void Timer::Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();

		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << "\n" << m_TimerName << " took: " << ms << "ms\n";

		m_Stopped = true;
		
	}


	// INSTRUMENTOR TIMER

	InstrumentationTimer::InstrumentationTimer( const char* name ) : Timer(name) {}
	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!m_Stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();

		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

		Instrumentor::Get().WriteProfile({ m_TimerName, start, end, threadID });

		m_Stopped = true;
	}
}