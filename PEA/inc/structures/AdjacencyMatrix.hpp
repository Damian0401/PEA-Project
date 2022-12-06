#pragma once

namespace PEA {

	class AdjacencyMatrix
	{
	public:
		AdjacencyMatrix(size_t verticesNumber, int* data);
		AdjacencyMatrix(const AdjacencyMatrix& origin);
		~AdjacencyMatrix();

		void display();
		int** getRoot();
		size_t getVerticesNumber();
		int getCost(size_t from, size_t to);
		void setCost(size_t from, size_t to, int cost);
	private:
		size_t _verticesNumber;
		int** _root = nullptr;

		void allocateMemory();
		void insertData(int* data);
		void deallocateMemory();
		void copyData(int** data);
	};

}