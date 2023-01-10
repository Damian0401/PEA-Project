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

void PEA::ResultWriter::writeExtended(const std::string& fileName, Array<double>& values, 
	const std::string& valueName, Array<double>& averageErros, Array<long long>& averageTimes)
{
	std::ofstream file(_basePath + fileName);
	std::string header = valueName + ";average time;average error";

	file << header << std::endl;
	for (size_t i = 0; i < values.getSize(); i++)
	{
		file << values.get(i) << ';' << averageTimes.get(i) 
			<< ';' << averageErros.get(i) << std::endl;
	}

	file.close();
}
