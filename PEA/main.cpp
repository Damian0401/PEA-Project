#include <iostream>
#include "inc/algorithms/BruteForce.hpp"
#include "inc/algorithms/BranchAndBound.hpp"
#include "inc/algorithms/DynamicProgramming.hpp"
#include "inc/utils/Timer.hpp"
#include "inc/utils/TSPsolver.hpp"
#include "inc/utils/MatrixReader.hpp"
#include "inc/utils/MatrixGenerator.hpp"


int main()
{
    std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project1\\PEA\\data\\";

    PEA::MatrixReader reader(basePath);
    //auto matrix = reader.read("graph_17.txt");
    auto matrix = PEA::MatrixGenerator::generate(14);
    auto timeUnit = SDIZO::TimeUnit::MILLISECONDS;

    PEA::TSPsolver solver;
    std::cout << "Brute force" << std::endl;
    //solver.solve(matrix, PEA::BruteForce(), timeUnit, true);
    std::cout << std::string(15, '-') << std::endl;
    std::cout << "Dynamic programming" << std::endl;
    solver.solve(matrix, PEA::DynamicProgramming(), timeUnit, true);
    std::cout << std::string(15, '-') << std::endl;
    std::cout << "Branch and Bound" << std::endl;
    solver.solve(matrix, PEA::BranchAndBound(), timeUnit, true);
    std::cout << std::string(15, '-') << std::endl;

    matrix.display();
}

