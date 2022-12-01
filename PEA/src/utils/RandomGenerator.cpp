#include "..\..\inc\utils\RandomGenerator.hpp"

#include <random>

size_t PEA::RandomGenerator::generate(size_t min, size_t max)
{

	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> values(min, max);

	return values(gen);
}
