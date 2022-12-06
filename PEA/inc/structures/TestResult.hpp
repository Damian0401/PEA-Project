#pragma once

namespace PEA
{
	struct TestResult
	{
		long long averageTime;
		double averageError;

		TestResult(long long averageTime, double averageError) {
			this->averageTime = averageTime;
			this->averageError = averageError;
		}
	};
}