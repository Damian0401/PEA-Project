#include "..\..\inc\algorithms\Genetic.hpp"
#include "..\..\inc\utils\RandomGenerator.hpp"

#include <stdexcept>

PEA::Path* PEA::Genetic::execute(AdjacencyMatrix& matrix)
{
    Array<Array<size_t>> currentPopulation;
    Array<int> currentCosts;
    size_t verticesNumber = matrix.getVerticesNumber();
    _stopSize = verticesNumber * 10;

    while (currentPopulation.getSize() < _populationSize)
    {
        auto solution = this->getInitialSolution(verticesNumber);
        currentPopulation.addBack(solution);
        currentCosts.addBack(this->calculateCost(matrix, solution));
    }

    this->sortPopulation(currentPopulation, currentCosts, 0, currentCosts.getSize() - 1);
    Array<size_t> bestSolution = currentPopulation.get(0);

    size_t currentStopSize = 0;
    for (size_t i = 0; i < _populationNumber; i++)
    {
        Array<Array<size_t>> newPopulation;
        Array<int> newCosts;
        
        for (size_t i = 0; i < _alphaSize; i++)
        {
            newPopulation.addBack(currentPopulation.get(i));
            newCosts.addBack(this->calculateCost(matrix, currentPopulation.get(i)));
        }

        while (newPopulation.getSize() < _populationSize)
        {

            size_t firstIndex;
            size_t secondIndex;
            this->generateIndexes(firstIndex, secondIndex, _eliteSize);

            auto firstParent = currentPopulation.get(firstIndex);
            auto secondParent = currentPopulation.get(secondIndex);

            auto firstChild = this->crossover(firstParent, secondParent);
            auto secondChild = this->crossover(secondParent, firstParent);

            this->mutation(firstChild);
            this->mutation(secondChild);

            newPopulation.addBack(firstChild);
            newCosts.addBack(this->calculateCost(matrix, firstChild));
            newPopulation.addBack(secondChild);
            newCosts.addBack(this->calculateCost(matrix, secondChild));
        }

        this->sortPopulation(newPopulation, newCosts, 0, currentCosts.getSize() - 1);
        this->updateBestSolution(matrix, bestSolution, newPopulation.get(0), currentStopSize);

        currentPopulation = newPopulation;
        std::cout << i << ": " << this->calculateCost(matrix, bestSolution) << std::endl;

        if (currentStopSize > _stopSize)
            break;
    }
    
    int bestCost = this->calculateCost(matrix, bestSolution);
	return new Path(bestSolution, bestCost);
}

int PEA::Genetic::calculateCost(AdjacencyMatrix& matrix, SDIZO::Array<size_t>& vertices)
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

void PEA::Genetic::updateBestSolution(AdjacencyMatrix& matrix, 
    Array<size_t>& current, Array<size_t>& candidate, size_t& stopSize)
{
    int currentBestCost = this->calculateCost(matrix, current);
    int candidateCost = this->calculateCost(matrix, candidate);
    stopSize++;

    if (candidateCost < currentBestCost)
    {
        current = candidate;
        stopSize = 0;
    }
}

void PEA::Genetic::generateIndexes(size_t& firstIndex, 
    size_t& secondIndex, size_t verticesNumber)
{
    do
    {
        firstIndex = RandomGenerator::generate(0, verticesNumber - 2);
        secondIndex = RandomGenerator::generate(0, verticesNumber - 1);
    } while (firstIndex >= secondIndex);
}

void PEA::Genetic::mutation(Array<size_t>& vertices)
{
    float value = RandomGenerator::generate(0, 100) / 100.0;

    if (value > _mutationRate)
        return;

    switch (_mutationType)
    {
    case PEA::MutationType::INVERT:
        this->invertMutation(vertices);
        break;
    case PEA::MutationType::SCRAMBLE:
        this->scrambleMutation(vertices);
        break;
    case PEA::MutationType::SWAP:
        this->swapMutation(vertices);
        break;
    case PEA::MutationType::INSERT:
        this->insertMutation(vertices);
        break;
    default:
        throw new std::invalid_argument("Mutation type not supported");
        break;
    }
}

void PEA::Genetic::swapMutation(Array<size_t>& vertices)
{
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    vertices.swap(firstIndex, secondIndex);
}

void PEA::Genetic::insertMutation(Array<size_t>& vertices)
{
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    auto temp = vertices.get(secondIndex);
    vertices.removeAt(secondIndex);
    vertices.addAt(firstIndex, temp);
}

void PEA::Genetic::invertMutation(Array<size_t>& vertices)
{
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    while (firstIndex < secondIndex)
    {
        vertices.swap(firstIndex, secondIndex);
        firstIndex++;
        secondIndex--;
    }
}

void PEA::Genetic::scrambleMutation(Array<size_t>& vertices)
{
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    size_t swapNumber = secondIndex - firstIndex;

    for (size_t i = 0; i < swapNumber; i++)
    {
        auto firstSwapIndex = RandomGenerator::generate(firstIndex, secondIndex);
        auto secondSwapIndex = RandomGenerator::generate(firstIndex, secondIndex);
        vertices.swap(firstSwapIndex, secondSwapIndex);
    }
}

SDIZO::Array<size_t> PEA::Genetic::crossover(Array<size_t>& firstParent, Array<size_t>& secondParent)
{
    float value = RandomGenerator::generate(0, 100) / 100.0;

    if (value > _crossoverRate)
        return firstParent;

    switch (_crossoverType)
    {
    case PEA::CrossoverType::OX:
        return this->OXCrossover(firstParent, secondParent);
        break;
    case PEA::CrossoverType::PMX:
    case PEA::CrossoverType::EX:
    default:
        throw new std::invalid_argument("Crossover type not supported");
    }
}

SDIZO::Array<size_t> PEA::Genetic::getInitialSolution(size_t verticesNumber)
{
    Array<size_t> vertices;
    for (size_t i = 0; i < verticesNumber; i++)
    {
        vertices.addBack(i);
    }

    size_t firstIndex;
    size_t secondIndex;
    for (size_t i = 0; i < verticesNumber; i++)
    {
        this->generateIndexes(firstIndex, secondIndex, verticesNumber);
        vertices.swap(firstIndex, secondIndex);
    }

    return vertices;
}

SDIZO::Array<size_t> PEA::Genetic::OXCrossover(Array<size_t>& firstParent, 
    Array<size_t>& secondParent)
{
    Array<size_t> result;
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, firstParent.getSize());

    for (size_t i = firstIndex; i < secondIndex; i++)
    {
        result.addBack(firstParent.get(i));
    }

    for (int i = secondIndex - 1; i >= 0; i--)
    {
        auto vertex = secondParent.get(i);
        if (result.contains(vertex))
            continue;

        result.addFront(vertex);
    }

    for (size_t i = secondIndex; i < secondParent.getSize(); i++)
    {
        auto vertex = secondParent.get(i);
        if (result.contains(vertex))
            continue;

        result.addBack(vertex);
    }

    return result;
}

void PEA::Genetic::updatePopulation(AdjacencyMatrix& matrix, 
    Array<Array<size_t>>& population, Array<Array<size_t>>& candidates)
{
    Array<size_t> bestCandidate = candidates.get(0);
    int bestCost = this->calculateCost(matrix, bestCandidate);
    Array<size_t> secondBestCandidate = candidates.get(1);;

    for (auto& candidate : candidates)
    {
        int cost = this->calculateCost(matrix, candidate);
        if (cost < bestCost)
        {
            secondBestCandidate = bestCandidate;
            bestCandidate = candidate;
            bestCost = cost;
        }
    }

    population.addBack(bestCandidate);
    population.addBack(secondBestCandidate);
}

int PEA::Genetic::partitionPopulation(Array<Array<size_t>>& population, Array<int>& costs, int low, int high)
{
    int pivot = costs.get(high);
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (costs.get(j) < pivot)
        {
            i++;
            costs.swap(i, j);
            population.swap(i, j);
        }
    }

    costs.swap(i + 1, high);
    population.swap(i + 1, high);

    return i + 1;
}

void PEA::Genetic::sortPopulation(Array<Array<size_t>>& population, Array<int>& costs, int low, int high)
{
    if (low >= high)
        return;

    int pivot = this->partitionPopulation(population, costs, low, high);

    this->sortPopulation(population, costs, low, pivot - 1);
    this->sortPopulation(population, costs, pivot + 1, high);
}

