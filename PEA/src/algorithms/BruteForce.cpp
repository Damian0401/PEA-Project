#include "..\..\inc\algorithms\BruteForce.hpp"

#include <iostream>

PEA::Path* PEA::BruteForce::execute(AdjacencyMatrix& matrix)
{
    SDIZO::Array<size_t> numbers;
    for (size_t i = 0; i < matrix.getVerticesNumber(); i++)
    {
        numbers.addBack(i);
    }

    int cost = this->getCost(numbers, matrix);
    Path* bestSolution = new Path(numbers, cost);

    bool isNextPermutation = true;
    while(isNextPermutation)
    {
        cost = this->getCost(numbers, matrix);
        if (bestSolution->getTotalCost() > cost)
        {
            delete bestSolution;
            bestSolution = new Path(numbers, cost);
        }
        isNextPermutation = this->nextPermutation(numbers);
    }

	return bestSolution;
}

bool PEA::BruteForce::nextPermutation(SDIZO::Array<size_t>& array)
{
    /*
    * Algorithm source:
    * https://takeuforward.org/data-structure/next_permutation-find-next-lexicographically-greater-permutation/
    */
    int n = array.getSize(), k, l;
    for (k = n - 2; k > 0; k--) {
        if (array.get(k) < array.get(k + 1)) {
            break;
        }
    }
    if (k < 1) {
        array.reverse(1, array.getSize() - 1);
        return false;
    }
    else {
        for (l = n - 1; l > k; l--) {
            if (array.get(l) > array.get(k)) {
                break;
            }
        }
        array.swap(k, l);
        array.reverse(k + 1, array.getSize() - 1);
        return true;
    }
}

int PEA::BruteForce::getCost(SDIZO::Array<size_t>& numbers, PEA::AdjacencyMatrix& matrix)
{
    int cost = 0;
    int size = numbers.getSize();
    for (size_t i = 0; i < size - 1; i++)
    {
        cost += matrix.getCost(numbers.get(i), numbers.get(i + 1));
    }
    cost += matrix.getCost(numbers.get(size - 1), numbers.get(0));
    return cost;
}

