#pragma once

#include "enums\Algorithm.hpp"
#include "enums\TimeUnit.hpp"
#include "..\..\inc\algorithms\BranchAndBound.hpp"
#include "..\..\inc\algorithms\BruteForce.hpp"
#include "..\..\inc\algorithms\DynamicProgramming.hpp"

namespace PEA
{
	using namespace SDIZO;

	class TestProvider
	{
	public:
		long long performTests(AlgorithmBase& algorithm, TimeUnit timeUnit, size_t repeatsNumber, size_t verticesNumber);

	private:

	};

}