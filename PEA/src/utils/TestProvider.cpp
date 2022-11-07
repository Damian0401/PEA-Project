#include "..\..\inc\utils\TestProvider.hpp"
#include "..\..\inc\utils\MatrixGenerator.hpp"
#include "..\..\inc\utils\TSPsolver.hpp"

#include <stdexcept>


long long PEA::TestProvider::performTests(AlgorithmBase& algorithm, TimeUnit timeUnit, size_t repeatsNumber, size_t verticesNumber)
{
	MatrixGenerator generator;
	TSPsolver solver;
	long long time = 0;

	for (size_t i = 0; i < repeatsNumber; i++)
	{
		AdjanencyMatrix matrix = generator.generate(verticesNumber);
		time += solver.solve(matrix, algorithm, timeUnit);
	}

	return time / repeatsNumber;
}