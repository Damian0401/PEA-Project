#pragma once

#include "../structures/Array.hpp"
#include "../structures/Result.hpp"

#include <string>


namespace PEA
{
	using namespace SDIZO;

	class ResultWriter
	{
	public:
		ResultWriter();
		ResultWriter(std::string basePath);
		void write(std::string fileName, Array<size_t> vertices, Array<long long> times);
		void writeExtended(const std::string& fileName, Array<double>& values, 
			const std::string& valueName, Array<double>& averageErros, Array<long long>& averageTimes);

	private:
		std::string _basePath;

	};

}