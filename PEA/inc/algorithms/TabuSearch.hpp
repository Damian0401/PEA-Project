#pragma once

#include <string>

#include "AlgorithmBase.hpp"
#include "../structures/Array.hpp"

namespace PEA
{
	class TabuSearch : public AlgorithmBase
	{
	public:
		Path* execute(AdjanencyMatrix& matrix) override;

	private:
		size_t _iterationNumber = 5000;
		size_t _maxTabuListSize = 500;
		size_t _sameSolutionLimit = 100;
		size_t _neighbourhoodSize = 100;

		int calculateCost(AdjanencyMatrix& matrix, const std::string& vertices);
		std::string getInitialSolution(size_t verticesNumber);
		void swapTwoRandomVertices(std::string& vertices);
		void swapTwoVertices(std::string& vertices, 
			size_t firstIndex, size_t secondIndex);
		Path* createResult(const std::string& vertices, int totalCost);
		SDIZO::Array<std::string> generateNeighbours(std::string vertices);
		void updateTabuList(const std::string& currentPath, 
			SDIZO::Array<std::string>& tabuList);

	};
}