#include "..\..\inc\utils\Menu.hpp"
#include "..\..\inc\algorithms\BruteForce.hpp"
#include "..\..\inc\algorithms\BranchAndBound.hpp"
#include "..\..\inc\algorithms\DynamicProgramming.hpp"
#include "..\..\inc\utils\Timer.hpp"
#include "..\..\inc\utils\TSPsolver.hpp"
#include "..\..\inc\utils\MatrixReader.hpp"
#include "..\..\inc\utils\MatrixGenerator.hpp"

#include <limits>

void PEA::Menu::show()
{
	bool isFinished = false;

	while (!isFinished)
	{
		ActionType actionType = Menu::selectActionType();

		switch (actionType)
		{
		case ActionType::MANUAL_TESTS:
			Menu::manualTests();
			break;
		case ActionType::AUTOMATIC_TESTS:
			Menu::automaticTests();
			break;
		case ActionType::INVALID:
			std::cout << "You entered invalid data" << std::endl;
		case ActionType::EXIT:
		default:
			isFinished = true;
			break;
		}
	}
}

PEA::ActionType PEA::Menu::selectActionType()
{
	std::cout << "Select action:" << std::endl;
	std::cout << "[1] - Manual tests" << std::endl;
	std::cout << "[2] - Automatic tests" << std::endl;
	std::cout << "[3] - Exit" << std::endl;

	char actionType = Menu::getChar();

	system("cls");

	switch (actionType)
	{
	case '1':
		return ActionType::MANUAL_TESTS;
	case '2':
		return ActionType::AUTOMATIC_TESTS;
	case '3':
		return ActionType::EXIT;
	default:
		return ActionType::INVALID;
	}
}

void PEA::Menu::manualTests()
{
	std::cout << "Manual tests" << std::endl;
}

void PEA::Menu::automaticTests()
{
	std::cout << "Automatic tests" << std::endl;
}

int PEA::Menu::getNumber()
{
	std::cout << "Enter number: ";

	int number;
	std::cin >> number;

	return number;
}

PEA::ActionType PEA::Menu::getAnswer(std::string message)
{
	std::cout << message << std::endl;
	std::cout << "Enter [y] to confirm or [n] to cancel" << std::endl;
	
	char answer = Menu::getChar();

	switch (answer)
	{
	case 'y':
		return ActionType::YES_ANSWER;
		break;
	case 'n':
		return ActionType::NO_ANSWER;
		break;
	default:
		return ActionType::INVALID;
	}
}

char PEA::Menu::getChar()
{
	char answer;
	std::cin >> answer;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return answer;
}
