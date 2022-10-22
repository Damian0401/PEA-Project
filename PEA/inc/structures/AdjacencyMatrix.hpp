#pragma once

namespace PEA {

	class AdjanencyMatrix
	{
	public:
		AdjanencyMatrix(size_t verticesNumber, int* data);
		AdjanencyMatrix(const AdjanencyMatrix& origin);
		~AdjanencyMatrix();

		void displayMatrix();
		int** getRoot();
		size_t getVerticesNumber();
		int getCost(size_t from, size_t to);
	private:
		size_t _verticesNumber;
		int** _root = nullptr;

		void allocateMemory();
		void insertData(int* data);
		void deallocateMemory();
		void copyData(int** data);
	};

}