#include "../../inc/algorithms/SimulatedAnnealing.hpp"

#include <random>
#include <cmath>
#include <iostream>

PEA::Path* PEA::SimulatedAnnealing::execute(AdjanencyMatrix& matrix)
{
    size_t verticesNumber = matrix.getVerticesNumber();
    SDIZO::Array<size_t> vertices = this->getInitialSolution(verticesNumber);

    int cost = this->calculateCost(matrix, vertices);
    double temperature = _startTemperature;

    SDIZO::Array<size_t> bestSolution = vertices;
    int bestCost = cost;
    
    while (temperature > 1)
    {
        SDIZO::Array<size_t> newVertices(vertices);
        this->changeOrder(newVertices);
        int newCost = this->calculateCost(matrix, newVertices);
        int delta = cost - newCost;

        if (delta < 0 && !this->makeDecision(delta, temperature))
            continue;

        cost = newCost;
        vertices = newVertices;
        temperature *= _coolingRatio;

        if (cost < bestCost)
        {
            bestSolution = vertices;
            bestCost = cost;
        }
    }

    return new Path(bestSolution, bestCost);
}

int PEA::SimulatedAnnealing::calculateCost(AdjanencyMatrix& matrix, SDIZO::Array<size_t>& vertices)
{
    int result = 0;
    int iterationNumber = matrix.getVerticesNumber() - 1;

    for (size_t i = 0; i < iterationNumber; i++)
    {
        result += matrix.getCost(vertices.get(i), vertices.get(i + 1));
    }
    result += matrix.getCost(vertices.get(iterationNumber), vertices.get(0));

    return result;
}

double PEA::SimulatedAnnealing::getRandom()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    return dis(gen);
}

double PEA::SimulatedAnnealing::calculateProbability(const int delta, const double temperature)
{
    return exp(delta / temperature);
}

bool PEA::SimulatedAnnealing::makeDecision(const int delta, const double temperature)
{
    return this->getRandom() < this->calculateProbability(delta, temperature);
}

double PEA::SimulatedAnnealing::probabilityOnSamples(const int delta, const double temperature, const int samples)
{
    int count = 0;
    for (size_t i = 0; i < samples; i++)
        if (this->makeDecision(delta, temperature))
            count++;
    return (double)count / samples;
}

void PEA::SimulatedAnnealing::changeOrder(SDIZO::Array<size_t>& vertices)
{
    size_t verticesNumber = vertices.getSize();
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<size_t> values(0, verticesNumber - 1);
    size_t firstIndex = values(gen);
    size_t secondIndex = values(gen);
    vertices.swap(firstIndex, secondIndex);
}

SDIZO::Array<size_t> PEA::SimulatedAnnealing::getInitialSolution(size_t verticesNumber)
{
    SDIZO::Array<size_t> vertices;
    for (size_t i = 0; i < verticesNumber; i++)
        vertices.addBack(i);
    for (size_t i = 0; i < verticesNumber; i++)
        this->changeOrder(vertices);

    return vertices;
}

