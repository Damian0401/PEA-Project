#include "..\..\inc\utils\ResultWriter.hpp"

#include <fstream>


PEA::ResultWriter::ResultWriter()
	: _basePath(".\\")
{
}

PEA::ResultWriter::ResultWriter(std::string basePath)
	: _basePath(basePath)
{
}

void PEA::ResultWriter::write(std::string fileName, Array<size_t> vertices, Array<long long> times)
{
	std::ofstream file(_basePath + fileName);
	std::string header = "vertices;time";

	size_t verticesNumber = vertices.getSize();

	file << header << std::endl;
	for (size_t i = 0; i < verticesNumber; i++)
	{
		file << vertices.get(i) << ';' << times.get(i) << std::endl;
	}

	file.close();
}
