#pragma once

#include "Array.hpp"

namespace PEA 
{
	class Path
	{
	public:
		Path();
		Path(const Path& origin);
		Path(SDIZO::Array<size_t> vertices, int totalCost);
		void display();
		int getTotalCost();

	private:
		int _totalCost{ 0 };
		SDIZO::Array<size_t> _vertices;
	};
}
