#include "..\..\inc\algorithms\BranchAndBound.hpp"

#include <climits>
#include <cmath>
#include <iostream>


PEA::Path* PEA::BranchAndBound::execute(AdjanencyMatrix& matrix)
{
	size_t verticesNumber = matrix.getVerticesNumber();
	size_t* currentPath = this->allocateMemory(verticesNumber);

	for (size_t i = 0; i < verticesNumber; i++)
	{
		_currentBound += this->findFirstMin(matrix, i) + findSecondMin(matrix, i);
	}
	_currentBound = ceil(_currentBound / 2);

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
	_currentBound = 0;
	_verticesNumber = verticesNumber;
	_finalPath = new size_t[verticesNumber] {0};
	_visitedVertices = new bool[verticesNumber] {false};
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
	_currentBound = 0;
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

void PEA::BranchAndBound::examineNextLevel(AdjanencyMatrix& matrix, int currentCost, size_t currentLevel, size_t* currentPath)
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

		int temp = _currentBound;
		if (currentLevel == 1)
			_currentBound -= (findFirstMin(matrix, currentPath[currentLevel - 1]) + findFirstMin(matrix, i)) / 2;
		else 
			_currentBound -= (findSecondMin(matrix, currentPath[currentLevel - 1]) + findFirstMin(matrix, i)) / 2;

		if (currentCost  + cost + _currentBound < _finalCost)
		{
			currentPath[currentLevel] = i;
			_visitedVertices[i] = true;

			this->examineNextLevel(matrix, currentCost + cost, currentLevel + 1, currentPath);
		}

		_currentBound = temp;

		for (size_t j = 0; j < _verticesNumber; j++)
			_visitedVertices[i] = false;

		for (size_t j = 0; j <= currentLevel - 1; j++)
			_visitedVertices[currentPath[j]] = true;
	}
}

int PEA::BranchAndBound::findFirstMin(AdjanencyMatrix& matrix, size_t startVertex)
{
	int firstMin = INT_MAX;

	for (size_t i = 0; i < matrix.getVerticesNumber(); i++)
	{
		if (startVertex == i)
			continue;

		if (matrix.getCost(startVertex, i) < firstMin)
			firstMin = matrix.getCost(startVertex, i);
	}

	return firstMin;
}

int PEA::BranchAndBound::findSecondMin(AdjanencyMatrix& matrix, size_t startVertex)
{
	int firstMin = INT_MAX;
	int secondMin = INT_MAX;

	for (size_t i = 0; i < matrix.getVerticesNumber(); i++)
	{
		if (startVertex == i)
			continue;

		int cost = matrix.getCost(startVertex, i);
		if (cost <= firstMin)
		{
			secondMin = firstMin;
			firstMin = cost;
		}
		else if (cost < secondMin && cost != firstMin)
			secondMin = cost;
	}

	return secondMin;
}
