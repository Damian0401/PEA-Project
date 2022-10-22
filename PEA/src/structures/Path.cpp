#include "..\..\inc\structures\Path.hpp"

#include <iostream>

PEA::Path::Path()
{
}

PEA::Path::Path(const Path& origin)
	: _totalCost(origin._totalCost), _vertices(origin._vertices)
{
	std::cout << "Copy path" << std::endl;
}

PEA::Path::Path(SDIZO::Array<size_t> vertices, int totalCost)
	: _vertices(vertices), _totalCost(totalCost)
{
}

void PEA::Path::display()
{
	std::cout << "Total cost: " << _totalCost << std::endl;
	_vertices.print();
}

int PEA::Path::getTotalCost()
{
	return _totalCost;
}
