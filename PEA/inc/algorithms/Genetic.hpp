#pragma once

#include "AlgorithmBase.hpp"
#include "../utils/enums/MutationType.hpp"
#include "../utils/enums/CrossoverType.hpp"

namespace PEA
{
	using namespace SDIZO;


	class Genetic : public AlgorithmBase
	{
	public:
		Path* execute(AdjacencyMatrix& matrix) override;

		friend class Menu;

	private:
		int calculateCost(AdjacencyMatrix& matrix, Array<size_t>& vertices);
		void updateBestSolution(AdjacencyMatrix& matrix, 
			Array<size_t>& current, Array<size_t>& candidate, size_t& stopSize);
		void generateIndexes(size_t& firstIndex, size_t& secondIndex, size_t verticesNumber);
		void mutation(Array<size_t>& vertices);
		void swapMutation(Array<size_t>& vertices);
		void insertMutation(Array<size_t>& vertices);
		void invertMutation(Array<size_t>& vertices);
		void scrambleMutation(Array<size_t>& vertices);
		Array<size_t> crossover(Array<size_t>& firstParent, Array<size_t>& secondParent);
		Array<size_t> getInitialSolution(size_t verticesNumber);
		Array<size_t> OXCrossover(Array<size_t>& firstParent, Array<size_t>& secondParent);
		void updatePopulation(AdjacencyMatrix& matrix, Array<Array<size_t>>& population, Array<Array<size_t>>& candidates);
		int partitionPopulation(Array<Array<size_t>>& population, Array<int>& costs, int low, int high);
		void sortPopulation(Array<Array<size_t>>& population, Array<int>& costs, int low, int high);

		float _mutationRate = 0.5;
		MutationType _mutationType = MutationType::INVERT;
		float _crossoverRate = 0.5;
		CrossoverType _crossoverType = CrossoverType::OX;
		size_t _stopSize = 1000;
		size_t _populationSize = 200;
		size_t _populationNumber = 3000;
		size_t _eliteSize = 0.5 * _populationSize;
		size_t _alphaSize = 0.1 * _populationSize;
	};

}