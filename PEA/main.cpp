#include <iostream>
#include "inc/algorithms/BruteForce.hpp"
#include "inc/algorithms/BranchAndBound.hpp"
#include "inc/utils/Timer.hpp"
#include "inc/utils/TSPsolver.hpp"
#include "inc/utils/MatrixReader.hpp"


int main()
{
    std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project1\\PEA\\data\\";

    PEA::MatrixReader reader(basePath);
    auto matrix = reader.read("graph_1.txt");

    PEA::TSPsolver solver;
    solver.solve(matrix, PEA::BruteForce(), SDIZO::TimeUnit::MILLISECONDS, true);
    std::cout << std::string(15, '-') << std::endl;
    solver.solve(matrix, PEA::BranchAndBound(), SDIZO::TimeUnit::MILLISECONDS, true);
}

