#include <iostream>
#include "inc/structures/AdjacencyMatrix.hpp"


int main()
{
	auto data = new int[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto matrix = new PEA::AdjanencyMatrix(3, data);

	matrix->displayMatrix();

	delete matrix;
	return 0;
}