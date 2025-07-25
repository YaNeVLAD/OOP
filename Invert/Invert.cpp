﻿#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const std::string INVALID_MATRIX_ERROR = "Invalid matrix";
const std::string USAGE_HINT = "Usage: invert.exe <input_file>";

using Matrix3x3d = std::array<std::array<double, 3>, 3>;

double GetDeterminant3x3(const Matrix3x3d& matrix)
{
	return (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+ (matrix[1][0] * matrix[2][1] * matrix[0][2])
		+ (matrix[0][1] * matrix[1][2] * matrix[2][0])
		- (matrix[0][2] * matrix[1][1] * matrix[2][0])
		- (matrix[0][1] * matrix[1][0] * matrix[2][2])
		- (matrix[1][2] * matrix[2][1] * matrix[0][0]);
}

double GetDeterminant2x2(const Matrix3x3d& matrix)
{
	return (matrix[0][0] * matrix[1][1])
		- (matrix[0][1] * matrix[1][0]);
}

void AssertIsMatrixInvertable(double determinant)
{
	if (determinant == 0)
	{
		throw std::runtime_error("Non-invertable");
	}
}

void AssertIsNumberInRange(double number)
{
	if (::isnan(number))
	{
		throw std::overflow_error("Evaluated number is out of range.");
	}
}

void AssertIsRowEmpty(std::istream& stream)
{
	if (stream.peek() != EOF)
	{
		throw std::runtime_error(INVALID_MATRIX_ERROR);
	}
}

std::ifstream TryOpenInputFile(const std::string& name)
{
	std::ifstream input(name);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open file " + name);
	}

	return input;
}

Matrix3x3d CreateMinor(const Matrix3x3d& matrix, size_t excludedRow, size_t excludedCol)
{
	Matrix3x3d minor{};

	size_t subRow = 0;
	size_t n = matrix.size();
	for (size_t i = 0; i < n; ++i)
	{
		if (i == excludedRow)
		{
			continue;
		}

		size_t subCol = 0;
		for (size_t j = 0; j < n; ++j)
		{
			if (j == excludedCol)
			{
				continue;
			}

			minor[subRow][subCol] = matrix[i][j];
			subCol++;
		}
		subRow++;
	}

	return minor;
}

double GetAlgebraicComplement(const Matrix3x3d& matrix, size_t excludedRow, size_t excludedCol)
{
	auto minor = CreateMinor(matrix, excludedRow, excludedCol);

	auto determinant = GetDeterminant2x2(minor);

	return std::pow(-1, excludedRow + excludedCol) * determinant;
}

Matrix3x3d MultiplyMatrixByNumber(const Matrix3x3d& matrix, double number)
{
	Matrix3x3d multiplied{};

	size_t n = matrix.size();
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			double value = matrix[i][j] * number;

			AssertIsNumberInRange(value);

			multiplied[i][j] = value;
		}
	}

	return multiplied;
}

Matrix3x3d CreateAdjugatedMatrix(const Matrix3x3d& matrix)
{
	Matrix3x3d adjugate{};

	size_t n = matrix.size();
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			adjugate[i][j] = GetAlgebraicComplement(matrix, i, j);
		}
	}

	return adjugate;
}

Matrix3x3d CreateTransposedMatrix(const Matrix3x3d& matrix)
{
	Matrix3x3d transpose{};

	size_t n = matrix.size();
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			transpose[i][j] = matrix[j][i];
		}
	}

	return transpose;
}

Matrix3x3d CreateInvertedMatrix(const Matrix3x3d& matrix)
{
	auto determinant = GetDeterminant3x3(matrix);

	AssertIsMatrixInvertable(determinant);

	auto transposed = CreateTransposedMatrix(matrix);
	auto adjugated = CreateAdjugatedMatrix(transposed);

	return MultiplyMatrixByNumber(adjugated, 1 / determinant);
}

double TryReadNumber(std::istream& input)
{
	double number;
	if (!(input >> number))
	{
		throw std::invalid_argument(INVALID_MATRIX_ERROR);
	}

	return number;
}

std::string TryReadLine(std::istream& input)
{
	std::string line;
	if (!std::getline(input, line))
	{
		throw std::runtime_error(INVALID_MATRIX_ERROR);
	}

	return line;
}

Matrix3x3d ReadMatrix(std::istream& input)
{
	Matrix3x3d matrix{};

	for (auto& row : matrix)
	{
		auto line = TryReadLine(input);

		std::istringstream iss(line);
		for (double& value : row)
		{
			value = TryReadNumber(iss);
		}

		AssertIsRowEmpty(iss);
	}

	return matrix;
}

void PrintMatrix(const Matrix3x3d& matrix)
{
	for (auto& row : matrix)
	{
		for (auto& value : row)
		{
			std::cout << std::fixed << std::setprecision(3) << value << "\t";
		}
		std::cout << std::endl;
	}
}

int HandleConsoleInput()
{
	auto matrix = ReadMatrix(std::cin);

	auto inverted = CreateInvertedMatrix(matrix);

	PrintMatrix(inverted);

	return EXIT_SUCCESS;
}

int HandleFileInput(const std::string& name)
{
	auto input = TryOpenInputFile(name);

	auto matrix = ReadMatrix(input);

	auto inverted = CreateInvertedMatrix(matrix);

	PrintMatrix(inverted);

	return EXIT_SUCCESS;
}

int HandleArgument(const std::string& argument)
{
	if (argument == "-h" || argument == "--help")
	{
		std::cout << USAGE_HINT << std::endl;

		return EXIT_SUCCESS;
	}

	return HandleFileInput(argument);
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 1)
		{
			return HandleConsoleInput();
		}
		else if (argc == 2)
		{
			return HandleArgument(argv[1]);
		}
		else
		{
			throw std::invalid_argument("Wrong argument count. " + USAGE_HINT);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
