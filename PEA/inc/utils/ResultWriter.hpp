#pragma once

#include "../structures/Array.hpp"

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

	private:
		std::string _basePath;

	};

}