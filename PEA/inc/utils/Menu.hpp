#pragma once

#include "enums/ActionType.hpp"

#include <iostream>


namespace PEA
{
	class Menu
	{
	public:
		static void show();

	private:
		static ActionType selectActionType();
		static void manualTests();
		static void automaticTests();
		static int getNumber();
		static ActionType getAnswer(std::string message);
		static char getChar();
	};
}

