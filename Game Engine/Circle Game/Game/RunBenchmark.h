#pragma once

#include "Benchmark.h"

#define PROFILING 0
#if PROFILING
#define PROFILE_NAME(name) Benchmark::InstrumentationTimer Timer##__LINE__(name)
#define PROFILE_TIME_BENCHMARK() PROFILE_NAME(__FUNCSIG__)
#else
#define PROFILE_NAME(name)
#define PROFILE_TIME_BENCHMARK() PROFILE_NAME(__FUNCSIG__)
#endif
