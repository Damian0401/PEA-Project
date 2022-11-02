#pragma once

#include "AlgorithmBase.hpp"

#include <climits>

namespace PEA
{
	class BranchAndBound : public AlgorithmBase
	{
	public:
		Path* execute(AdjanencyMatrix& matrix) override;

	private:
		int _finalCost = INT_MAX;
		int _currentBound = 0;
		size_t _verticesNumber = 0;
		size_t* _finalPath = nullptr;
		bool* _visitedVertices = nullptr;

		size_t* allocateMemory(size_t verticesNumber);
		void deallocateMemory(size_t* currentPath);
		Path* getFinalPath();
		int findFirstMin(AdjanencyMatrix& matrix, size_t startVertex);
		int findSecondMin(AdjanencyMatrix& matrix, size_t startVertex);
		void examineNextLevel(AdjanencyMatrix& matrix, int currentCost, size_t currentLevel, size_t* currentPath);
	};
}
