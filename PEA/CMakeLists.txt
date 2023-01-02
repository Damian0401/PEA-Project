# CMakeList.txt : CMake project for PEA, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("PEA")

# Add source to this project's executable.
add_executable (PEA   "main.cpp" "inc/structures/AdjacencyMatrix.hpp" "src/structures/AdjacencyMatrix.cpp" "inc/algorithms/AlgorithmBase.hpp"    "inc/structures/Path.hpp" "inc/structures/Array.hpp" "src/structures/Array.cpp" "src/structures/Path.cpp" "inc/utils/Timer.hpp" "src/utils/Timer.cpp" "inc/algorithms/BruteForce.hpp" "src/algorithms/BruteForce.cpp" "inc/utils/enums/TimeUnit.hpp" "inc/utils/TSPsolver.hpp" "src/utils/TSPsolver.cpp" "inc/utils/MatrixReader.hpp" "src/utils/MatrixReader.cpp" "inc/algorithms/BranchAndBound.hpp" "src/algorithms/BranchAndBound.cpp" "inc/algorithms/DynamicProgramming.hpp" "src/algorithms/DynamicProgramming.cpp" "inc/utils/MatrixGenerator.hpp" "src/utils/MatrixGenerator.cpp" "inc/utils/Menu.hpp" "src/utils/Menu.cpp"  "inc/utils/enums/ActionType.hpp" "inc/utils/enums/Algorithm.hpp" "inc/utils/TestProvider.hpp" "src/utils/TestProvider.cpp" "inc/utils/ResultWriter.hpp" "src/utils/ResultWriter.cpp" "inc/algorithms/SimulatedAnnealing.hpp" "src/algorithms/SimulatedAnnealing.cpp" "inc/algorithms/TabuSearch.hpp" "src/algorithms/TabuSearch.cpp" "inc/utils/RandomGenerator.hpp" "src/utils/RandomGenerator.cpp" "inc/structures/Instance.hpp" "inc/structures/Result.hpp" "inc/structures/TestResult.hpp" "inc/algorithms/Genetic.hpp" "src/algorithms/Genetic.cpp" "inc/utils/enums/MutationType.hpp" "inc/utils/enums/CrossoverType.hpp")

# TODO: Add tests and install targets if needed.
