#include "..\..\inc\utils\MatrixReader.hpp"

#include <fstream>
#include <stdexcept>

PEA::MatrixReader::MatrixReader()
	: _basePath(".\\")
{
}

PEA::MatrixReader::MatrixReader(std::string basePath)
	: _basePath(basePath)
{
}

PEA::AdjanencyMatrix PEA::MatrixReader::read(std::string fileName, bool useBasePath)
{
	if (useBasePath)
		fileName = _basePath + fileName;

	std::ifstream file(fileName);
	
	if (file.fail())
		throw new std::invalid_argument("Invalid file name");

	int verticesNumber = 0;

	file >> verticesNumber;
	int dataSize = verticesNumber * verticesNumber;

	int* data = new int[dataSize];
	for (size_t i = 0; i < dataSize; i++)
	{
		file >> data[i];
	}

	AdjanencyMatrix matrix(verticesNumber, data);
	delete[] data;

	return matrix;
}
