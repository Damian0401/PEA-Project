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
		AdjacencyMatrix matrix = generator.generate(verticesNumber);
		time += solver.solve(matrix, algorithm, timeUnit);
	}

	return time / repeatsNumber;
}

PEA::TestResult PEA::TestProvider::performExtendedTests(AlgorithmBase& algorithm, 
	AdjacencyMatrix& matrix, int optimalSolution, TimeUnit timeUnit, size_t repeatsNumber)
{
	TSPsolver solver;
	int totalCost = 0;
	long long totalTime = 0;

	for (size_t i = 0; i < repeatsNumber; i++)
	{
		auto result = solver.solveWithResult(matrix, algorithm, timeUnit);
		totalCost += result.path.getTotalCost();
		totalTime += result.time;
	}

	long long averageTime = totalTime / repeatsNumber;
	double averageCost = (double)totalCost / repeatsNumber;
	double averageError = (averageCost / optimalSolution - 1) * 100;


	return TestResult(averageTime, averageError);
}
