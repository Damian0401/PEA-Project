#pragma once

namespace PEA {

	class AdjanencyMatrix
	{
	public:
		AdjanencyMatrix(size_t edgeNumber, int* data);
		AdjanencyMatrix(const AdjanencyMatrix& origin);
		~AdjanencyMatrix();

		void displayMatrix();
		int** getRoot();
	private:
		size_t _edgeNumber;
		int** _root = nullptr;

		void allocateMemory();
		void insertData(int* data);
		void deallocateMemory();
		void copyData(int** data);
	};

}