# CMakeList.txt : CMake project for PEA, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("PEA")

# Add source to this project's executable.
add_executable (PEA   "main.cpp" "inc/structures/AdjacencyMatrix.hpp" "src/structures/AdjacencyMatrix.cpp" "inc/algorithms/AlgorithmBase.hpp"    "inc/structures/Path.hpp" "inc/structures/Array.hpp" "src/structures/Array.cpp" "src/structures/Path.cpp" "inc/utils/Timer.hpp" "src/utils/Timer.cpp" "inc/algorithms/BruteForce.hpp" "src/algorithms/BruteForce.cpp" "inc/utils/TimeUnit.hpp" "inc/utils/TSPsolver.hpp" "src/utils/TSPsolver.cpp" "inc/utils/MatrixReader.hpp" "src/utils/MatrixReader.cpp" "inc/algorithms/BranchAndBound.hpp" "src/algorithms/BranchAndBound.cpp")

# TODO: Add tests and install targets if needed.
