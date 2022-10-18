# CMakeList.txt : CMake project for PEA, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("PEA")

# Add source to this project's executable.
add_executable (PEA   "main.cpp" "inc/structures/AdjacencyMatrix.hpp" "src/structures/AdjacencyMatrix.cpp")

# TODO: Add tests and install targets if needed.
