#pragma once

#include "../algorithms/AlgorithmBase.hpp"
#include "../structures/AdjacencyMatrix.hpp"
#include "Timer.hpp"

namespace PEA
{
	using namespace SDIZO;

	class TSPsolver
	{
	public:
		long long solve(AdjanencyMatrix& matrix, AlgorithmBase& algorithm, 
			bool display = false, TimeUnit unit = TimeUnit::MICROSECONDS);
	private:

	};
}
