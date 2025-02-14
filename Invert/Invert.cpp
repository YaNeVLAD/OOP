#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

const std::string USAGE_HINT = "Usage: invert.exe <input_file>";

using Matrix3x3d = std::array<std::array<double, 3>, 3>;

double Determinant3x3(const Matrix3x3d& matrix)
{
	return (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+ (matrix[1][0] * matrix[2][1] * matrix[0][2])
		+ (matrix[0][1] * matrix[1][2] * matrix[2][0])
		- (matrix[0][2] * matrix[1][1] * matrix[2][0])
		- (matrix[0][1] * matrix[1][0] * matrix[2][2])
		- (matrix[1][2] * matrix[2][1] * matrix[0][0]);
}

double Determinant2x2(const Matrix3x3d& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

double AlgebraicComplement(const Matrix3x3d& matrix, size_t excludedRow, size_t excludedCol)
{
	Matrix3x3d submatrix{};

	size_t subRow = 0;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		if (i == excludedRow)
		{
			continue;
		}

		size_t subCol = 0;
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (j == excludedCol)
			{
				continue;
			}

			submatrix[subRow][subCol] = matrix[i][j];
			subCol++;
		}
		subRow++;
	}

	double minor = Determinant2x2(submatrix);

	return std::pow(-1, excludedRow + excludedCol) * minor;
}

Matrix3x3d MultiplyMatrixByNumber(const Matrix3x3d& matrix, double number)
{

	Matrix3x3d multiplied{};
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			multiplied[i][j] = (matrix[i][j] * number);
		}
	}

	return multiplied;
}

double ReadNumber(std::istream& input)
{
	double number;
	if (!(input >> number))
	{
		throw std::invalid_argument("Invalid matrix");
	}

	return number;
}

Matrix3x3d ReadMatrix(std::istream& input)
{
	Matrix3x3d matrix{};
	for (auto& row : matrix)
	{
		for (auto& value : row)
		{
			value = ReadNumber(input);
		}
	}

	return matrix;
}

void PrintMatrix(const Matrix3x3d& matrix)
{
	for (auto& row : matrix)
	{
		for (auto& value : row)
		{
			std::cout << std::fixed << std::setprecision(3) << value << " ";
		}
		std::cout << std::endl;
	}
}

Matrix3x3d CreateAdjugateMatrix(const Matrix3x3d& transposed)
{
	Matrix3x3d matrix{};
	for (size_t i = 0; i < transposed.size(); ++i)
	{
		for (size_t j = 0; j < transposed.size(); ++j)
		{
			matrix[i][j] = AlgebraicComplement(transposed, i, j);
		}
	}

	return matrix;
}

Matrix3x3d TransposeMatrix(const Matrix3x3d& matrix)
{
	Matrix3x3d transposed{};
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[0].size(); ++j)
		{
			transposed[i][j] = matrix[j][i];
		}
	}

	return transposed;
}

Matrix3x3d InvertMatrix(const Matrix3x3d& matrix)
{
	auto determinant = Determinant3x3(matrix);
	if (determinant == 0)
	{
		throw std::runtime_error("Non-invertable");
	}

	return MultiplyMatrixByNumber(CreateAdjugateMatrix(TransposeMatrix(matrix)), 1 / determinant);
}

int HandleConsoleInput()
{
	PrintMatrix(InvertMatrix(ReadMatrix(std::cin)));

	return EXIT_SUCCESS;
}

int HandleFileInput(const std::string& name)
{
	std::ifstream input(name);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open file" + name);
	}

	PrintMatrix(InvertMatrix(ReadMatrix(input)));

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
		else if (argc == 2 && argv[1])
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
