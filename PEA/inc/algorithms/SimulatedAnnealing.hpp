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
		double getRandom();
		double calculateProbability(const int delta, const double temperature);
		bool makeDecision(const int delta, const double temperature);
		double probabilityOnSamples(const int delta, const double temperature, const int samples);
		void changeOrder(SDIZO::Array<size_t>& vertices);
		SDIZO::Array<size_t> getInitialSolution(size_t verticesNumber);

	};

}