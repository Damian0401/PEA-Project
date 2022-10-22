#include "../../inc/utils/Timer.hpp"

#include <stdexcept>

void SDIZO::Timer::start()
{
	this->startPoint = std::chrono::high_resolution_clock::now();
}

void SDIZO::Timer::stop()
{
	this->endPoint = std::chrono::high_resolution_clock::now();
}

long long SDIZO::Timer::getTime(TimeUnit unit)
{
	switch (unit)
	{
	case SDIZO::TimeUnit::NANOSECONDS:
		return std::chrono::
			duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count();
		break;
	case SDIZO::TimeUnit::MICROSECONDS:
		return std::chrono::
			duration_cast<std::chrono::microseconds>(endPoint - startPoint).count();
		break;
	case SDIZO::TimeUnit::MILLISECONDS:
		return std::chrono::
			duration_cast<std::chrono::milliseconds>(endPoint - startPoint).count();
		break;
	default:
		throw new std::invalid_argument("Bad time unit");
		break;
	}
}

std::string SDIZO::Timer::timeUnitToString(TimeUnit unit)
{
	switch (unit)
	{
	case SDIZO::TimeUnit::NANOSECONDS:
		return "ns";
		break;
	case SDIZO::TimeUnit::MICROSECONDS:
		return "us";
		break;
	case SDIZO::TimeUnit::MILLISECONDS:
		return "ms";
		break;
	default:
		throw new std::invalid_argument("Invalid time unit");
		break;
	}
}
