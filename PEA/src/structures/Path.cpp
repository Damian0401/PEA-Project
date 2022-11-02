#include "..\..\inc\structures\Path.hpp"

#include <iostream>

PEA::Path::Path()
{
}

PEA::Path::Path(const Path& origin)
	: _totalCost(origin._totalCost), _vertices(origin._vertices)
{
}

PEA::Path::Path(SDIZO::Array<size_t> vertices, int totalCost)
	: _vertices(vertices), _totalCost(totalCost)
{
}

PEA::Path::Path(size_t vertex, int cost)
{
	_vertices.addFront(vertex);
	_totalCost = cost;
}

void PEA::Path::display()
{
	std::cout << "Total cost: " << _totalCost << std::endl;
	_vertices.print();
}

void PEA::Path::addVertex(size_t vertex, int cost)
{
	_vertices.addBack(vertex);
	_totalCost += cost;
}

int PEA::Path::getTotalCost()
{
	return _totalCost;
}
