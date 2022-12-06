#pragma once

#include "AlgorithmBase.hpp"

#include <climits>

namespace PEA
{
	class BranchAndBound : public AlgorithmBase
	{
	public:
		Path* execute(AdjacencyMatrix& matrix) override;

	private:
		int _finalCost = INT_MAX;
		size_t _verticesNumber = 0;
		size_t* _finalPath = nullptr;
		bool* _visitedVertices = nullptr;

		size_t* allocateMemory(size_t verticesNumber);
		void deallocateMemory(size_t* currentPath);
		Path* getFinalPath();
		void examineNextLevel(AdjacencyMatrix& matrix, int currentCost, size_t currentLevel, size_t* currentPath);
	};
}
