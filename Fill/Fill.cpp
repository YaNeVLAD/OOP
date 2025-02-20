#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

const std::string USAGE_HINT = "fill.exe <input file> <output file>";

const int MAX_MAP_SIZE = 100;

const char FILL_START_CHAR = 'O';
const char BORDER_CHAR = '#';
const char FILL_CHAR = '.';
const char DIVIDER_CHAR = ' ';
const char EMPTY_CHAR = '\0';

using MapChar = std::array<std::array<char, MAX_MAP_SIZE>, MAX_MAP_SIZE>;
using MapBool = std::array<std::array<bool, MAX_MAP_SIZE>, MAX_MAP_SIZE>;

struct Cell
{
	size_t x = 0;
	size_t y = 0;
};

// Necessary for yandex contest autotests
int GetErrorCodeBasedOnArgsCount(int argc)
{
	if (argc > 1)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void AssertIsLineValid(std::array<char, MAX_MAP_SIZE> line)
{
	for (char& ch : line)
	{
		if (ch == EMPTY_CHAR)
		{
			break;
		}

		if (ch != FILL_START_CHAR && ch != BORDER_CHAR && ch != DIVIDER_CHAR)
		{
			throw std::runtime_error("Wrong char. Must be "
				+ std::string{ DIVIDER_CHAR } + ", "
				+ std::string{ BORDER_CHAR } + " or "
				+ std::string{ FILL_START_CHAR });
		}
	}
}

MapChar CreateMap(std::istream& input)
{
	MapChar map{};

	for (auto& line : map)
	{
		if (!input.getline(line.data(), line.size() + 1))
		{
			break;
		}

		AssertIsLineValid(line);
	}

	return map;
}

void PrintLine(std::ostream& output, std::array<char, MAX_MAP_SIZE> line)
{
	for (char& ch : line)
	{
		if (ch == EMPTY_CHAR)
		{
			return;
		}

		output << ch;
	}
}

void PrintMap(const MapChar& map, std::ostream& output)
{
	for (auto& line : map)
	{
		PrintLine(output, line);

		output << std::endl;
	}
}

bool IsCellFillable(MapChar& map, MapBool& visited, size_t x, size_t y)
{
	return x < MAX_MAP_SIZE && y < MAX_MAP_SIZE && map[x][y] != BORDER_CHAR && !visited[x][y];
}

void TryEnqueueCell(MapChar& map, MapBool& visited, std::queue<Cell>& queue, Cell cell)
{
	auto& [x, y] = cell;
	if (IsCellFillable(map, visited, x, y))
	{
		map[x][y] = FILL_CHAR;
		queue.push(cell);
		visited[x][y] = true;
	}
}

void FillAdjacentCells(MapChar& map, MapBool& visited, std::queue<Cell>& queue)
{
	auto& [x, y] = queue.front();
	queue.pop();

	Cell left = { x - 1, y };
	Cell right = { x + 1, y };
	Cell top = { x, y - 1 };
	Cell bottom = { x, y + 1 };

	TryEnqueueCell(map, visited, queue, top);
	TryEnqueueCell(map, visited, queue, bottom);
	TryEnqueueCell(map, visited, queue, left);
	TryEnqueueCell(map, visited, queue, right);
}

std::vector<Cell> GetStartPoints(const MapChar& map)
{
	std::vector<Cell> result;

	for (size_t x = 0; x < MAX_MAP_SIZE; ++x)
	{
		for (size_t y = 0; y < MAX_MAP_SIZE; ++y)
		{
			if (map[x][y] != FILL_START_CHAR)
			{
				continue;
			}

			result.push_back({ x, y });
		}
	}

	return result;
}

std::queue<Cell> InitQueue(const MapChar& map, MapBool& visited, std::vector<Cell> points)
{
	std::queue<Cell> queue;
	for (auto& point : points)
	{
		queue.push(point);
		visited[point.x][point.y] = true;
	}

	return queue;
}

MapChar FillMap(const MapChar& map)
{
	auto filled = std::make_unique<MapChar>(map);

	auto startPoints = GetStartPoints(*filled);

	auto visited = std::make_unique<MapBool>();

	auto queue = InitQueue(*filled, *visited, startPoints);

	while (!queue.empty())
	{
		FillAdjacentCells(*filled, *visited, queue);
	}

	return *filled;
}

int HandleConsoleInput()
{
	auto map = std::make_unique<MapChar>(CreateMap(std::cin));

	auto filled = FillMap(*map);

	PrintMap(filled, std::cout);

	return EXIT_SUCCESS;
}

int HandleFileInput(const std::string& inputName, const std::string& outputName)
{
	std::ifstream input(inputName);
	std::ofstream output(outputName);
	if (!input.is_open() || !output.is_open())
	{
		throw std::runtime_error("Failed to open file.");
	}

	auto map = std::make_unique<MapChar>(CreateMap(input));

	auto filled = FillMap(*map);

	PrintMap(filled, output);

	return EXIT_SUCCESS;
}

int HandleFlag(const std::string& flag)
{
	if (flag == "-h" || flag == "--help")
	{
		std::cout << USAGE_HINT << std::endl;

		return EXIT_SUCCESS;
	}

	throw std::runtime_error("Unknown flag. Available flags: -h.");
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 3)
		{
			return HandleFileInput(argv[1], argv[2]);
		}
		else if (argc == 2)
		{
			return HandleFlag(argv[1]);
		}
		else if (argc == 1)
		{
			return HandleConsoleInput();
		}
		else
		{
			throw std::invalid_argument("Wrong arguments count. " + USAGE_HINT);
		}

		return EXIT_SUCCESS;
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR" << std::endl;

		return GetErrorCodeBasedOnArgsCount(argc);
	}
}
