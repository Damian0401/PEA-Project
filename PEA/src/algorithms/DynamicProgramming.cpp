#include "..\..\inc\algorithms\DynamicProgramming.hpp"

#include <climits>
#include <iostream>


PEA::Path* PEA::DynamicProgramming::execute(AdjanencyMatrix& matrix)
{
    this->allocateMemory(matrix.getVerticesNumber());
    Path* solution = this->examineNextLevel(matrix, 0, 0b1);
    this->deallocateMemory(matrix.getVerticesNumber());

	return new Path(*solution);
}

void PEA::DynamicProgramming::allocateMemory(size_t verticesNumber)
{
    _subsolutions = new Path ** [verticesNumber];
    for (size_t i = 0; i < verticesNumber; i++)
    {
        _subsolutions[i] = new Path * [(1 << verticesNumber) - 1]{};
    }
    _finalVerticesMask = (1 << verticesNumber) - 1;
}

void PEA::DynamicProgramming::deallocateMemory(size_t verticesNumber)
{
    for (size_t i = 0; i < verticesNumber; i++)
    {
        for (size_t j = 0; j < (1 << verticesNumber) - 1; j++)
        {
            delete _subsolutions[i][j];
        }
        delete[] _subsolutions[i];
    }
    delete[] _subsolutions;

    _subsolutions = nullptr;
    _finalVerticesMask = 0;
}

PEA::Path* PEA::DynamicProgramming::examineNextLevel(AdjanencyMatrix& matrix, int currentVertex, int visitedVerticesMask)
{
    if (visitedVerticesMask == _finalVerticesMask)
    {
        Path* path = new Path();
        path->addVertex(currentVertex, matrix.getCost(currentVertex, 0));
        return path;
    }

    Path* solutionToExamine = _subsolutions[currentVertex][visitedVerticesMask];
    if (solutionToExamine != nullptr)
        return new Path(*solutionToExamine);

    solutionToExamine = new Path();
    solutionToExamine->addVertex(-1, INT_MAX);
    auto cost = solutionToExamine->getTotalCost();

    for (size_t i = 0; i < matrix.getVerticesNumber(); i++)
    {
        if (i == currentVertex || (visitedVerticesMask & (1 << i)))
            continue;

        Path* path = this->examineNextLevel(matrix, i, visitedVerticesMask | (1 << i));
        int cost = matrix.getCost(currentVertex, i);
        
        if (path->getTotalCost() + cost < solutionToExamine->getTotalCost())
        {
            delete solutionToExamine;
            solutionToExamine = path;
            solutionToExamine->addVertex(currentVertex, cost);
        }
        else
        {
            delete path;
        }
    }

    _subsolutions[currentVertex][visitedVerticesMask] = solutionToExamine;
    return new Path(*solutionToExamine);
}




/**
    \brief Given a complete, undirected, weighted graph in the form of an adjacency matrix,
           returns the smallest tour that visits all nodes and starts and ends at the same
           node. This dynamic programming solution runs in O(n^2 * 2^n).
    \return the minimum cost to complete the tour
*/
//int tsp(const vector<vector<int>>& cities, int pos, int visited, vector<vector<int>>& state)
//{
//    if (visited == ((1 << cities.size()) - 1))
//        return cities[pos][0]; // return to starting city
//
//    if (state[pos][visited] != INT_MAX)
//        return state[pos][visited];
//
//    for (int i = 0; i < cities.size(); ++i)
//    {
//        // can't visit ourselves unless we're ending & skip if already visited
//        if (i == pos || (visited & (1 << i)))
//            continue;
//
//        int distance = cities[pos][i] + tsp(cities, i, visited | (1 << i), state);
//        if (distance < state[pos][visited])
//            state[pos][visited] = distance;
//    }
//
//    return state[pos][visited];
//}
//
//int main()
//{
//    vector<vector<int>> cities = { { 0, 20, 42, 35 },
//                                   { 20, 0, 30, 34 },
//                                   { 42, 30, 0, 12 },
//                                   { 35, 34, 12, 0 }
//    };
//
//    vector<vector<int>> state(cities.size());
//    for (auto& neighbors : state)
//        neighbors = vector<int>((1 << cities.size()) - 1, INT_MAX);
//
//    cout << "minimum: " << tsp(cities, 0, 1, state) << endl;
//
//    return 0;
//}