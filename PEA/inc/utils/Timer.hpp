#pragma once

#include "enums/TimeUnit.hpp"
#include <chrono>
#include <string>

namespace SDIZO
{
	class Timer
	{
	public:
		void start();
		void stop();
		long long getTime(TimeUnit unit);
		std::string timeUnitToString(TimeUnit unit);
	private:
		std::chrono::high_resolution_clock::time_point startPoint;
		std::chrono::high_resolution_clock::time_point endPoint;
	};
}