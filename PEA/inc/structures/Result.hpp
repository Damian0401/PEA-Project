#pragma once

#include "Path.hpp"

namespace PEA
{
	struct Result
	{
		Path path;
		long long time;

		Result(Path path, long long time) {
			this->path = path;
			this->time = time;
		}
	};
}