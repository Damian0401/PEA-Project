#include "..\..\inc\algorithms\TabuSearch.hpp"

#include <random>
#include <iostream>

#include "../../inc/utils/RandomGenerator.hpp"

PEA::Path* PEA::TabuSearch::execute(AdjacencyMatrix& matrix)
{
    size_t verticesNumber = matrix.getVerticesNumber();

    std::string currentPath = this->getInitialSolution(verticesNumber);
    int currentCost = this->calculateCost(matrix, currentPath);

    std::string bestPath = currentPath;
    int bestCost = currentCost;

    SDIZO::Array<std::string> tabuList;
    int sameSolutionCounter = 0;

    for (size_t i = 0; i < _iterationNumber; i++)
    {
        SDIZO::Array<std::string> neighbours = this->generateNeighbours(currentPath);
        currentPath = neighbours.get(0);
        currentCost = this->calculateCost(matrix, currentPath);

        for (size_t i = 1; i < neighbours.getSize(); i++)
        {
            std::string candidatePath = neighbours.get(i);

            if (tabuList.contains(candidatePath))
                continue;

            int candidateCost = this->calculateCost(matrix, candidatePath);
            if (candidateCost < currentCost)
            {
                currentCost = candidateCost;
                currentPath = candidatePath;
            }
        }

        if (currentCost < bestCost)
        {
            bestPath = currentPath;
            bestCost = currentCost;
            sameSolutionCounter = 0;
        }

        this->updateTabuList(currentPath, tabuList);
        if (sameSolutionCounter == _sameSolutionLimit)
            break;

        sameSolutionCounter++;
    }

    return this->createResult(bestPath, bestCost);
}

int PEA::TabuSearch::calculateCost(AdjacencyMatrix& matrix, const std::string& vertices)
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

PEA::Path* PEA::TabuSearch::createResult(const std::string& vertices, int totalCost)
{
    SDIZO::Array<size_t> verticesArray;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        verticesArray.addBack(vertices[i]);
    }

    return new Path(verticesArray, totalCost);
}

SDIZO::Array<std::string> PEA::TabuSearch::generateNeighbours(std::string vertices)
{
    SDIZO::Array<std::string> neighbours;

    for (size_t i = 0; i < _neighbourhoodSize; i++)
    {
        size_t firstNode = 0;
        size_t secondNode = 0;

        while (firstNode == secondNode)
        {
            firstNode = RandomGenerator::generate(1, vertices.size() - 1);
            secondNode = RandomGenerator::generate(1, vertices.size() - 1);
        }

        if (firstNode > secondNode)
        {
            int swap = firstNode;
            firstNode = secondNode;
            secondNode = swap;
        }

        std::string neighbour = vertices;
        int index = firstNode;
        for (int i = secondNode; i >= firstNode; i--)
        {
            neighbour[i] = vertices[index];
            index++;
        }
        neighbours.addFront(neighbour);
    }

    return neighbours;
}

void PEA::TabuSearch::updateTabuList(const std::string& currentPath, SDIZO::Array<std::string>& tabuList)
{
    tabuList.addFront(currentPath);

    if (tabuList.getSize() > _maxTabuListSize)
        tabuList.removeBack();
}



