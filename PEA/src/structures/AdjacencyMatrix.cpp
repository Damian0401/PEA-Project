#include "..\..\inc\structures\AdjacencyMatrix.hpp"
#include <exception>
#include <iostream>

PEA::AdjanencyMatrix::AdjanencyMatrix(size_t edgeNumber, int* data)
	: _edgeNumber(edgeNumber)
{
	this->allocateMemory();
	this->insertData(data);
}

PEA::AdjanencyMatrix::AdjanencyMatrix(const AdjanencyMatrix& origin)
	: _edgeNumber(origin._edgeNumber)
{
	this->allocateMemory();
	this->copyData(origin._root);
}

PEA::AdjanencyMatrix::~AdjanencyMatrix()
{
	this->deallocateMemory();
}

void PEA::AdjanencyMatrix::displayMatrix()
{
	for (size_t i = 0; i < _edgeNumber; i++)
	{
		std::cout << "| ";
		for (size_t j = 0; j < _edgeNumber; j++)
		{
			std::cout << _root[i][j] << " | ";
		}
		std::cout << std::endl;
	}
}

int** PEA::AdjanencyMatrix::getRoot()
{
	return _root;
}

void PEA::AdjanencyMatrix::allocateMemory()
{
	if (_edgeNumber == 0 || _root != nullptr)
		throw new std::exception("Unable to allocate memory");

	_root = new int* [_edgeNumber];
	for (int i = 0; i < _edgeNumber; i++) {
		_root[i] = new int[_edgeNumber];
	}
}

void PEA::AdjanencyMatrix::insertData(int* data)
{
	if (_edgeNumber == 0 || _root == nullptr) 
		throw new std::exception("Unable to insert data to empty matrix");

	size_t dataCounter = 0;
	for (size_t i = 0; i < _edgeNumber; i++)
	{
		for (size_t j = 0; j < _edgeNumber; j++)
		{
			_root[i][j] = data[dataCounter];
			dataCounter++;
		}
	}
}

void PEA::AdjanencyMatrix::deallocateMemory()
{
	if (_root == nullptr) 
		return;

	for (size_t i = 0; i < _edgeNumber; i++)
	{
		delete[] _root[i];
	}
	delete[] _root;
	_root = nullptr;
}

void PEA::AdjanencyMatrix::copyData(int** data)
{
	for (size_t i = 0; i < _edgeNumber; i++)
	{
		for (size_t j = 0; j < _edgeNumber; j++)
		{
			_root[i][j] = data[i][j];
		}
	}
}
