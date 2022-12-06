#pragma once

#include "../algorithms/AlgorithmBase.hpp"
#include "../structures/AdjacencyMatrix.hpp"
#include "../structures/Result.hpp"
#include "Timer.hpp"


namespace PEA
{
	using namespace SDIZO;

	class TSPsolver
	{
	public:
		long long solve(AdjacencyMatrix& matrix, AlgorithmBase& algorithm,
			TimeUnit unit = TimeUnit::MICROSECONDS, bool display = false);
		Result solveWithResult(AdjacencyMatrix& matrix, AlgorithmBase& algorithm,
			TimeUnit unit = TimeUnit::MICROSECONDS);
	private:

	};
}
