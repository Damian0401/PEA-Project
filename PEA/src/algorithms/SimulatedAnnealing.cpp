#include "../../inc/algorithms/SimulatedAnnealing.hpp"

PEA::Path* PEA::SimulatedAnnealing::execute(AdjanencyMatrix& matrix)
{
    SDIZO::Array<size_t> vertices;
    for (size_t i = 0; i < matrix.getVerticesNumber(); i++)
    {
        vertices.addBack(i);
    }

    auto cost = this->calculateCost(matrix, vertices);

    return new Path(vertices, cost);
}

int PEA::SimulatedAnnealing::calculateCost(AdjanencyMatrix& matrix, SDIZO::Array<size_t>& vertices)
{
    int result = 0;
    int iterationNumber = matrix.getVerticesNumber() - 1;

    for (size_t i = 0; i < iterationNumber; i++)
    {
        result += matrix.getCost(i, i + 1);
    }
    result += matrix.getCost(iterationNumber, 0);

    return result;
}

