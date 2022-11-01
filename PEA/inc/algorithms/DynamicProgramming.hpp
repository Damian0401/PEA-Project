#pragma once

#include "AlgorithmBase.hpp"

namespace PEA
{
	class DynamicProgramming : public AlgorithmBase
	{
	public:
		Path* execute(AdjanencyMatrix& matrix) override;

	private:
		Path*** _subsolutions;
		int _finalVerticesMask;

		void allocateMemory(size_t verticesNumber);
		void deallocateMemory(size_t verticesNumber);
		Path* examineNextLevel(AdjanencyMatrix& matrix, int currentVertex, int visitedVerticesMask);
	};
}