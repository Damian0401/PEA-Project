#include "..\..\inc\utils\TSPsolver.hpp"

#include <iostream>

long long PEA::TSPsolver::solve(AdjacencyMatrix& matrix, AlgorithmBase& algorithm, TimeUnit unit, bool display)
{
	Timer timer;
	timer.start();
	
	auto path = algorithm.execute(matrix);

	timer.stop();
	auto time = timer.getTime(unit);

	if (display)
	{
		std::cout << "Finished." << std::endl;
		std::cout << "Time: " << time << timer.timeUnitToString(unit) << std::endl;
		path->display();
	}

	delete path;
	return time;
}

PEA::Result PEA::TSPsolver::solveWithResult(AdjacencyMatrix& matrix, AlgorithmBase& algorithm, TimeUnit unit)
{
	Timer timer;
	timer.start();

	auto path = algorithm.execute(matrix);

	timer.stop();
	auto time = timer.getTime(unit);

	Path copyOfPath(*path);
	delete path;
	
	return Result(copyOfPath, time);
}
