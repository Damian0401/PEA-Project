#include "..\..\inc\structures\AdjacencyMatrix.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>

PEA::AdjacencyMatrix::AdjacencyMatrix(size_t verticesNumber, int* data)
	: _verticesNumber(verticesNumber)
{
	this->allocateMemory();
	this->insertData(data);
}

PEA::AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& origin)
	: _verticesNumber(origin._verticesNumber)
{
	this->allocateMemory();
	this->copyData(origin._root);
}

PEA::AdjacencyMatrix::~AdjacencyMatrix()
{
	this->deallocateMemory();
}

void PEA::AdjacencyMatrix::display()
{
	for (size_t i = 0; i < _verticesNumber; i++)
	{
		std::cout << "| ";
		for (size_t j = 0; j < _verticesNumber; j++)
		{
			std::cout << std::setw(2) << _root[i][j] << std::fixed << " | ";
		}
		std::cout << std::endl;
	}
}

int** PEA::AdjacencyMatrix::getRoot()
{
	return _root;
}

size_t PEA::AdjacencyMatrix::getVerticesNumber()
{
	return _verticesNumber;
}

void PEA::AdjacencyMatrix::allocateMemory()
{
	if (_verticesNumber == 0 || _root != nullptr)
		throw new std::runtime_error("Unable to allocate memory");

	_root = new int* [_verticesNumber];
	for (int i = 0; i < _verticesNumber; i++) {
		_root[i] = new int[_verticesNumber];
	}
}

void PEA::AdjacencyMatrix::insertData(int* data)
{
	if (_verticesNumber == 0 || _root == nullptr)
		throw new std::runtime_error("Unable to insert data to empty matrix");

	size_t dataCounter = 0;
	for (size_t i = 0; i < _verticesNumber; i++)
	{
		for (size_t j = 0; j < _verticesNumber; j++)
		{
			_root[i][j] = data[dataCounter];
			dataCounter++;
		}
	}
}

void PEA::AdjacencyMatrix::deallocateMemory()
{
	if (_root == nullptr) 
		return;

	for (size_t i = 0; i < _verticesNumber; i++)
	{
		delete[] _root[i];
	}
	delete[] _root;
	_root = nullptr;
}

int PEA::AdjacencyMatrix::getCost(size_t from, size_t to)
{
	if (from >= _verticesNumber || to >= _verticesNumber)
		throw new std::out_of_range("Invalid vertex index");

	return _root[from][to];
}

void PEA::AdjacencyMatrix::setCost(size_t from, size_t to, int cost)
{
	if (from >= _verticesNumber || to >= _verticesNumber)
		throw new std::out_of_range("Invalid vertex index");

	_root[from][to] = cost;
}

void PEA::AdjacencyMatrix::copyData(int** data)
{
	for (size_t i = 0; i < _verticesNumber; i++)
	{
		for (size_t j = 0; j < _verticesNumber; j++)
		{
			_root[i][j] = data[i][j];
		}
	}
}
