#include "..\..\inc\algorithms\BranchAndBound.hpp"

#include <climits>
#include <cmath>


PEA::Path* PEA::BranchAndBound::execute(AdjacencyMatrix& matrix)
{
	size_t verticesNumber = matrix.getVerticesNumber();
	size_t* currentPath = this->allocateMemory(verticesNumber);

	_visitedVertices[0] = true;
	currentPath[0] = 0;

	this->examineNextLevel(matrix, 0, 1, currentPath);

	Path* finalPath = this->getFinalPath();
	this->deallocateMemory(currentPath);

	return finalPath;
}

size_t* PEA::BranchAndBound::allocateMemory(size_t verticesNumber)
{
	_finalCost = INT_MAX;
	_verticesNumber = verticesNumber;
	_finalPath = new size_t[verticesNumber] {};
	_visitedVertices = new bool[verticesNumber] {};
	size_t* currentPath = new size_t[verticesNumber];

	return currentPath;
}

void PEA::BranchAndBound::deallocateMemory(size_t* currentPath)
{
	delete[] currentPath;
	delete[] _finalPath;
	delete[] _visitedVertices;

	_finalPath = nullptr;
	_visitedVertices = nullptr;
	_finalCost = INT_MAX;
	_verticesNumber = 0;
}

PEA::Path* PEA::BranchAndBound::getFinalPath()
{
	SDIZO::Array<size_t> vertices;
	for (size_t i = 0; i < _verticesNumber; i++)
	{
		vertices.addBack(_finalPath[i]);
	}

	Path* path = new Path(vertices, _finalCost);

	return path;
}

void PEA::BranchAndBound::examineNextLevel(AdjacencyMatrix& matrix, int currentCost, size_t currentLevel, size_t* currentPath)
{
	if (currentLevel == _verticesNumber)
	{
		currentCost += matrix.getCost(currentPath[currentLevel - 1], currentPath[0]);

		if (currentCost < _finalCost)
		{
			_finalCost = currentCost;
			for (size_t i = 0; i < _verticesNumber; i++)
			{
				_finalPath[i] = currentPath[i];
			}
		}

		return;
	}

	for (size_t i = 0; i < _verticesNumber; i++)
	{
		int cost = matrix.getCost(currentPath[currentLevel - 1], i);
		if (cost <= 0 || _visitedVertices[i] || currentCost + cost >= _finalCost)
			continue;

		currentPath[currentLevel] = i;
		_visitedVertices[i] = true;

		this->examineNextLevel(matrix, currentCost + cost, currentLevel + 1, currentPath);

		for (size_t j = 0; j < _verticesNumber; j++)
			_visitedVertices[i] = false;

		for (size_t j = 0; j <= currentLevel - 1; j++)
			_visitedVertices[currentPath[j]] = true;
	}
}