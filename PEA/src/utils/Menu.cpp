#include "..\..\inc\utils\Menu.hpp"
#include "..\..\inc\algorithms\BruteForce.hpp"
#include "..\..\inc\algorithms\BranchAndBound.hpp"
#include "..\..\inc\algorithms\DynamicProgramming.hpp"
#include "..\..\inc\utils\Timer.hpp"
#include "..\..\inc\utils\TSPsolver.hpp"
#include "..\..\inc\utils\MatrixReader.hpp"
#include "..\..\inc\utils\MatrixGenerator.hpp"
#include "..\..\inc\utils\TestProvider.hpp"
#include "..\..\inc\utils\ResultWriter.hpp"

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
		case ActionType::GENERATE_TESTS:
			Menu::generateTests();
			break;
		case ActionType::AUTOMATIC_TESTS:
			Menu::automaticTests();
			break;
		case ActionType::INVALID:
			std::cout << "You entered invalid data" << std::endl;
			break;
		case ActionType::NO_ACTION:
			break;
		case ActionType::EXIT:
		default:
			isFinished = true;
			break;
		}
	}
}

PEA::ActionType PEA::Menu::selectActionType()
{
	std::cout << std::string(15, '-') << std::endl;
	std::cout << "Select action:" << std::endl;
	std::cout << "[1] - Manual tests from file" << std::endl;
	std::cout << "[2] - Generate tests" << std::endl;
	std::cout << "[3] - Automatic tests" << std::endl;
	std::cout << "[4] - Exit" << std::endl;

	char actionType = Menu::getChar();

	system("cls");

	switch (actionType)
	{
	case '1':
		return ActionType::MANUAL_TESTS;
	case '2':
		return ActionType::GENERATE_TESTS;
	case '3':
		return ActionType::AUTOMATIC_TESTS;
	case '4':
		return Menu::getAnswer("Are you really want to exit?")
			? ActionType::EXIT 
			: ActionType::NO_ACTION;
	default:
		return ActionType::INVALID;
	}
}

void PEA::Menu::manualTests()
{
	std::cout << "Manual tests" << std::endl;
	std::cout << "Enter file name: ";

	std::string fileName;
	std::cin >> fileName;

	AdjanencyMatrix matrix = Menu::readMatrix(fileName);
	std::cout << "Size: " << matrix.getVerticesNumber() << std::endl;
	matrix.display();

	Algorithm algorithm = Menu::selectAlgorithm();
	TSPsolver solver;

	switch (algorithm)
	{
	case PEA::Algorithm::BRUTE_FORCE:
		solver.solve(matrix, BruteForce(), TimeUnit::MICROSECONDS, true);
		break;
	case PEA::Algorithm::DYNAMIC_PROGRAMMING:
		solver.solve(matrix, DynamicProgramming(), TimeUnit::MICROSECONDS, true);
		break;
	case PEA::Algorithm::BRANCH_AND_BOUND:
		solver.solve(matrix, BranchAndBound(), TimeUnit::MICROSECONDS, true);
		break;
	case PEA::Algorithm::NOT_IMPLEMENTED:
	default:
		std::cout << "Not implemented" << std::endl;
		break;
	}
}

void PEA::Menu::automaticTests()
{
	std::cout << "Automatic tests" << std::endl;
	Algorithm algorithm = Menu::selectAlgorithm();
	AlgorithmBase* base;
	std::string fileName;

	switch (algorithm)
	{
	case PEA::Algorithm::BRUTE_FORCE:
		base = new BruteForce();
		fileName = "brute-force.csv";
		break;
	case PEA::Algorithm::DYNAMIC_PROGRAMMING:
		base = new DynamicProgramming();
		fileName = "dynamic-programming.csv";
		break;
	case PEA::Algorithm::BRANCH_AND_BOUND:
		base = new BranchAndBound();
		fileName = "branch-and-bound.csv";
		break;
	case PEA::Algorithm::NOT_IMPLEMENTED:
	default:
		std::cout << "Not implemented" << std::endl;
		return;
	}

	TestProvider provider;
	std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project1\\PEA\\results\\";

	std::cout << "Select start range" << std::endl;
	int start = Menu::getNumber();

	std::cout << "Select end range" << std::endl;
	int end = Menu::getNumber();

	if (end <= start)
	{
		std::cout << "Invalid range" << std::endl;
		return;
	}

	Array<size_t> vertices;
	Array<long long> times;

	for (size_t i = start; i <= end; i++)
	{
		vertices.addBack(i);
		long long time = provider.performTests(*base, TimeUnit::MICROSECONDS, 100, i);
		times.addBack(time);
		std::cout << "finished " << i << ": " << time  << "us" << std::endl;
	}

	delete base;

	ResultWriter writer(basePath);
	writer.write(fileName, vertices, times);
}

void PEA::Menu::generateTests()
{
	std::cout << "Generate tests" << std::endl;
	std::cout << "Select vertices number: " << std::endl;

	int verticesNumber = Menu::getNumber();

	MatrixGenerator generator;
	AdjanencyMatrix matrix = generator.generate(verticesNumber);
	matrix.display();

	Algorithm algorithm = Menu::selectAlgorithm();
	TSPsolver solver;

	switch (algorithm)
	{
	case PEA::Algorithm::BRUTE_FORCE:
		solver.solve(matrix, BruteForce(), TimeUnit::MICROSECONDS, true);
		break;
	case PEA::Algorithm::DYNAMIC_PROGRAMMING:
		solver.solve(matrix, DynamicProgramming(), TimeUnit::MICROSECONDS, true);
		break;
	case PEA::Algorithm::BRANCH_AND_BOUND:
		solver.solve(matrix, BranchAndBound(), TimeUnit::MICROSECONDS, true);
		break;
	case PEA::Algorithm::NOT_IMPLEMENTED:
	default:
		std::cout << "Not implemented" << std::endl;
		break;
	}
}

int PEA::Menu::getNumber()
{
	std::cout << "Enter number: ";

	int number;
	std::cin >> number;

	return number;
}

bool PEA::Menu::getAnswer(std::string message)
{
	std::cout << message << std::endl;
	std::cout << "Enter [y] to confirm or [n] to cancel" << std::endl;
	
	char answer = Menu::getChar();

	switch (answer)
	{
	case 'y':
		return true;
	case 'n':
	default:
		return false;
	}
}

char PEA::Menu::getChar()
{
	char answer;
	std::cin >> answer;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return answer;
}

PEA::AdjanencyMatrix PEA::Menu::readMatrix(std::string fileName)
{
	std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project1\\PEA\\data\\";
	MatrixReader reader(basePath);
	AdjanencyMatrix matrix = reader.read(fileName);

	return matrix;
}

PEA::Algorithm PEA::Menu::selectAlgorithm()
{
	std::cout << "Select algorithm:" << std::endl;
	std::cout << "[1] - Brute Force" << std::endl;
	std::cout << "[2] - Dynamic programming" << std::endl;
	std::cout << "[3] - Branch and Bound" << std::endl;

	char algorithm = Menu::getChar();

	switch (algorithm)
	{
	case '1':
		return Algorithm::BRUTE_FORCE;
	case '2':
		return Algorithm::DYNAMIC_PROGRAMMING;
	case '3':
		return Algorithm::BRANCH_AND_BOUND;
	default:
		return Algorithm::NOT_IMPLEMENTED;
	}
}
