#pragma once

#include <string>

namespace PEA
{
	struct Instance
	{
		int optimalCost;
		std::string fileName;

		Instance(int optimalCost, std::string fileName) {
			this->optimalCost = optimalCost;
			this->fileName = fileName;
		}
	};
}