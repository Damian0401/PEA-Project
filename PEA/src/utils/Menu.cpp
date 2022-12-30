#include "..\..\inc\utils\Menu.hpp"
#include "..\..\inc\algorithms\BruteForce.hpp"
#include "..\..\inc\algorithms\BranchAndBound.hpp"
#include "..\..\inc\algorithms\DynamicProgramming.hpp"
#include "..\..\inc\algorithms\SimulatedAnnealing.hpp"
#include "..\..\inc\algorithms\TabuSearch.hpp"
#include "..\..\inc\utils\Timer.hpp"
#include "..\..\inc\utils\TSPsolver.hpp"
#include "..\..\inc\utils\MatrixReader.hpp"
#include "..\..\inc\utils\MatrixGenerator.hpp"
#include "..\..\inc\utils\TestProvider.hpp"
#include "..\..\inc\utils\ResultWriter.hpp"
#include "..\..\inc\structures\Instance.hpp"

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
		case ActionType::EXTENDED_TESTS:
			Menu::extendedTests();
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
	std::cout << "[1] - Manual tests" << std::endl;
	std::cout << "[2] - Generate tests" << std::endl;
	std::cout << "[3] - Automatic tests" << std::endl;
	std::cout << "[4] - Extended tests" << std::endl;
	std::cout << "[0] - Exit" << std::endl;

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
		return ActionType::EXTENDED_TESTS;
	case '0':
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

	AdjacencyMatrix matrix = Menu::readMatrix(fileName);
	std::cout << "Size: " << matrix.getVerticesNumber() << std::endl;
	matrix.display();

	Algorithm algorithm = Menu::selectAlgorithm();
	TSPsolver solver;
	TimeUnit timeUnit = TimeUnit::MICROSECONDS;

	switch (algorithm)
	{
	case PEA::Algorithm::BRUTE_FORCE:
		solver.solve(matrix, BruteForce(), timeUnit, true);
		break;
	case PEA::Algorithm::DYNAMIC_PROGRAMMING:
		solver.solve(matrix, DynamicProgramming(), timeUnit, true);
		break;
	case PEA::Algorithm::BRANCH_AND_BOUND:
		solver.solve(matrix, BranchAndBound(), timeUnit, true);
		break;
	case PEA::Algorithm::SIMULATED_ANNEALING:
		solver.solve(matrix, SimulatedAnnealing(), timeUnit, true);
		break;
	case PEA::Algorithm::TABU_SEARCH:
		solver.solve(matrix, TabuSearch(), timeUnit, true);
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
	case PEA::Algorithm::SIMULATED_ANNEALING:
		base = new SimulatedAnnealing();
		fileName = "simulated-annealing.csv";
		break;
	case PEA::Algorithm::TABU_SEARCH:
		base = new SimulatedAnnealing();
		fileName = "tabu-search.csv";
		break;
	case PEA::Algorithm::NOT_IMPLEMENTED:
	default:
		std::cout << "Not implemented" << std::endl;
		return;
	}

	TestProvider provider;
	std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project\\PEA\\results\\part-1\\";

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
	AdjacencyMatrix matrix = generator.generate(verticesNumber);
	matrix.display();

	Algorithm algorithm = Menu::selectAlgorithm();
	TSPsolver solver;
	TimeUnit timeUnit = TimeUnit::MICROSECONDS;

	switch (algorithm)
	{
	case PEA::Algorithm::BRUTE_FORCE:
		solver.solve(matrix, BruteForce(), timeUnit, true);
		break;
	case PEA::Algorithm::DYNAMIC_PROGRAMMING:
		solver.solve(matrix, DynamicProgramming(), timeUnit, true);
		break;
	case PEA::Algorithm::BRANCH_AND_BOUND:
		solver.solve(matrix, BranchAndBound(), timeUnit, true);
		break;
	case PEA::Algorithm::SIMULATED_ANNEALING:
		solver.solve(matrix, SimulatedAnnealing(), timeUnit, true);
		break;
	case PEA::Algorithm::TABU_SEARCH:
		solver.solve(matrix, TabuSearch(), timeUnit, true);
		break;
	case PEA::Algorithm::NOT_IMPLEMENTED:
	default:
		std::cout << "Not implemented" << std::endl;
		break;
	}
}

void PEA::Menu::extendedTests()
{
	int instancesNumber = 7;
	int* instances = new int[]{
		20, 30, 40, 50, 60, 70, 80
	};

	std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project\\PEA\\results\\part-2\\";
	TestProvider provider;
	TimeUnit timeUnit = TimeUnit::MILLISECONDS;
	ResultWriter writer(basePath);
	int repeatsNumber = 10;

	SDIZO::Array<size_t> verticesNumbers;
	SDIZO::Array<long long> averageTimes;
	for (size_t i = 0; i < instancesNumber; i++)
	{
		auto result = provider.performTests(SimulatedAnnealing(), 
			timeUnit, repeatsNumber, instances[i]);
		averageTimes.addBack(result);
		verticesNumbers.addBack(instances[i]);
		std::cout << "Done." << std::endl;
	}
	writer.write("simulated-annealing.csv", verticesNumbers, averageTimes);

	averageTimes.clear();

	for (size_t i = 0; i < instancesNumber; i++)
	{
		auto result = provider.performTests(TabuSearch(), 
			timeUnit, repeatsNumber, instances[i]);
		averageTimes.addBack(result);
		std::cout << "Done." << std::endl;
	}
	writer.write("tabu-search.csv", verticesNumbers, averageTimes);

	delete[] instances;
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

PEA::AdjacencyMatrix PEA::Menu::readMatrix(std::string fileName)
{
	std::string basePath = "C:\\Users\\szkol\\Desktop\\PEA\\PEA-Project\\PEA\\data\\";
	MatrixReader reader(basePath);
	AdjacencyMatrix matrix = reader.read(fileName);

	return matrix;
}

PEA::Algorithm PEA::Menu::selectAlgorithm()
{
	std::cout << "Select algorithm:" << std::endl;
	std::cout << "[1] - Brute Force" << std::endl;
	std::cout << "[2] - Dynamic programming" << std::endl;
	std::cout << "[3] - Branch and Bound" << std::endl;
	std::cout << "[4] - Simulated annealing" << std::endl;
	std::cout << "[5] - Tabu search" << std::endl;

	char algorithm = Menu::getChar();

	switch (algorithm)
	{
	case '1':
		return Algorithm::BRUTE_FORCE;
	case '2':
		return Algorithm::DYNAMIC_PROGRAMMING;
	case '3':
		return Algorithm::BRANCH_AND_BOUND;
	case '4':
		return Algorithm::SIMULATED_ANNEALING;
	case '5':
		return Algorithm::TABU_SEARCH;
	default:
		return Algorithm::NOT_IMPLEMENTED;
	}
}
