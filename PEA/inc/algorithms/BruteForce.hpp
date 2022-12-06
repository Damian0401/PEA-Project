#pragma once

#include "AlgorithmBase.hpp"
#include "../structures/Array.hpp"

namespace PEA
{
	class BruteForce : public AlgorithmBase
	{
	public:
		Path* execute(AdjacencyMatrix& matrix) override;

	private:
		bool nextPermutation(SDIZO::Array<size_t>& array);
		int getCost(SDIZO::Array<size_t>& numbers, PEA::AdjacencyMatrix& matrix);
	};
}
