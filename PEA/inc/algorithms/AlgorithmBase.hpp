#pragma once

#include "../structures/Path.hpp"
#include "../structures/AdjacencyMatrix.hpp"

namespace PEA
{
	class AlgorithmBase
	{
	public:
		virtual ~AlgorithmBase() = default;
		virtual Path* execute(AdjanencyMatrix& matrix) = 0;

	private:

	};
}
