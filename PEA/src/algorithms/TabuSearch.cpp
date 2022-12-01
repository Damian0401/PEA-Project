#include "..\..\inc\algorithms\TabuSearch.hpp"

#include <random>

#include "../../inc/utils/RandomGenerator.hpp"

PEA::Path* PEA::TabuSearch::execute(AdjanencyMatrix& matrix)
{
    size_t verticesNumber = matrix.getVerticesNumber();

    std::string currentPath = this->getInitialSolution(verticesNumber);
    int currentCost = this->calculateCost(matrix, currentPath);

    // TODO

	return new Path(SDIZO::Array<size_t>(), -1);
}

int PEA::TabuSearch::calculateCost(AdjanencyMatrix& matrix, std::string vertices)
{
    int result = 0;
    int iterationNumber = matrix.getVerticesNumber() - 1;

    for (size_t i = 0; i < iterationNumber; i++)
    {
        result += matrix.getCost(vertices.at(i), vertices.at(i + 1));
    }
    result += matrix.getCost(vertices.at(iterationNumber), vertices.at(0));

    return result;
}

std::string PEA::TabuSearch::getInitialSolution(size_t verticesNumber)
{
    std::string solution = "";

    for (size_t i = 0; i < verticesNumber; i++)
    {
        solution += i;
    }

    for (size_t i = 0; i < verticesNumber; i++)
    {
        this->swapTwoRandomVertices(solution);
    }


    return solution;
}

void PEA::TabuSearch::swapTwoRandomVertices(std::string& vertices)
{
    size_t firstIndex = RandomGenerator::generate(0, vertices.size() - 1);
    size_t secondIndex = RandomGenerator::generate(0, vertices.size() - 1);

    this->swapTwoVertices(vertices, firstIndex, secondIndex);
}

void PEA::TabuSearch::swapTwoVertices(std::string& vertices, size_t firstIndex, size_t secondIndex)
{
    char temp = vertices[firstIndex];
    vertices[firstIndex] = vertices[secondIndex];
    vertices[secondIndex] = temp;
}


