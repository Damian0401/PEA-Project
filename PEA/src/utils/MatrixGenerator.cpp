#include "..\..\inc\utils\MatrixGenerator.hpp"

#include <random>


PEA::AdjacencyMatrix PEA::MatrixGenerator::generate(size_t verticesNumber)
{
	size_t dataSize = verticesNumber * verticesNumber;
	int* data = new int[dataSize];

	int minValue = 1;
	int maxValue = 99;

	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<int> values(minValue, maxValue);

	size_t shift = 0;
	for (size_t i = 0; i < dataSize; i++)
	{
		if (i == shift)
		{
			data[i] = -1;
			shift += (1 + verticesNumber);
			continue;
		}

		data[i] = values(gen);
	}

	AdjacencyMatrix matrix(verticesNumber, data);
	delete[] data;

	return matrix;
}


//  -1   X   X   X
//   X  -1   X   X
//   X   X  -1   X
//   X   X   X  -1