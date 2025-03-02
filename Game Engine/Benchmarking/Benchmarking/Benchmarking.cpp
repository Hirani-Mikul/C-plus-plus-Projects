#include <iostream>
#include <string>
#include <cmath>

#include "Benchmark.h"

#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) Benchmark::InstrumentationTimer Timer##__LINE__(name)
#define PROFILE_TIME_BENCHMARK() PROFILE_SCOPE(__FUNCSIG__)
#else 
#define PROFILE_SCOPE(name)
#endif

void Print1()
{
	PROFILE_TIME_BENCHMARK();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i << std::endl;
}
void Print2()
{
	PROFILE_TIME_BENCHMARK();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}
void Print3()
{
	PROFILE_TIME_BENCHMARK();
	std::cout << "M";
}

void RunBenchmark()
{
	PROFILE_TIME_BENCHMARK();
	Print1();
	Print2();
	Print3();
}

int main()
{
	Benchmark::Instrumentor::Get().BeginSession("Profile1");
	Print1();
	Print2();
	Print3();
	Benchmark::Instrumentor::Get().EndSession();
}

