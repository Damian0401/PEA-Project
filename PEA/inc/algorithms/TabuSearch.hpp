#pragma once

#include <string>

#include "AlgorithmBase.hpp"

namespace PEA
{
	class TabuSearch : public AlgorithmBase
	{
	public:
		Path* execute(AdjanencyMatrix& matrix) override;

	private:
		int calculateCost(AdjanencyMatrix& matrix, std::string vertices);
		std::string getInitialSolution(size_t verticesNumber);
		void swapTwoRandomVertices(std::string& vertices);
		void swapTwoVertices(std::string& vertices, size_t firstIndex, size_t secondIndex);

	};
}