#pragma once

#include "./AlgorithmBase.hpp"
#include "../structures/Array.hpp"

namespace PEA
{
	class SimulatedAnnealing : public AlgorithmBase
	{
	public:
		Path* execute(AdjanencyMatrix& matrix) override;

	private:
		int calculateCost(AdjanencyMatrix& matrix, SDIZO::Array<size_t>& vertices);

	};

}