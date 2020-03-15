#include <iostream>
#include <fstream>
#include <vector>
#include <cfloat>
#include <iomanip>
#include <cmath>
#include <array>
#include <sstream>

const std::string templateOfNumbers = "0123456789";
constexpr int MATRIX_3X3_SIZE = 3;
constexpr int MATRIX_2x2_SIZE = 2;
typedef std::array<float, MATRIX_3X3_SIZE> Matrix3x3Row;
typedef std::array<Matrix3x3Row, 3> Matrix3x3;
typedef std::array<std::array<float, MATRIX_2x2_SIZE>, MATRIX_2x2_SIZE> Matrix2x2;

bool IsNumeric(const std::string& string)
{
    size_t offset = 0;
    if (string[offset] == '-')
    {
        ++offset;
    }
    return string.find_first_not_of(templateOfNumbers, offset) == std::string::npos;
}

void PrintMatrix(const Matrix3x3& matrix)
{
    for (auto& row : matrix)
    {
        for (auto elem : row)
        {
            std::cout << std::fixed << std::setprecision(3) << std::setw(10) << elem << "  ";
        }
        std::cout << std::endl;
    }
}

Matrix3x3 MultiplyMatrixByNumber(Matrix3x3& matrix, float number)
{
    Matrix3x3 resultMatrix = matrix;

    for (auto& row : resultMatrix)
    {
        for (auto& elem : row)
        {
            elem *= number;
        }
    }

    return resultMatrix;
}

float GetDeterminant2x2(const Matrix2x2& algExpr)
{
    return algExpr[0][0] * algExpr[1][1] - algExpr[0][1] * algExpr[1][0];
}

float GetMinorMatrixElem(const Matrix3x3& matrix, size_t row, size_t col)
{
    Matrix2x2 minor;
    size_t minorRowIndex = 1;
    size_t minorColIndex = 1;

    for (size_t i = 0; i < MATRIX_3X3_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_3X3_SIZE; j++)
        {
            if ((i != row) && (j != col))
            {
                minor[minorRowIndex - 1][minorColIndex - 1] = matrix[i][j];

                if (minorColIndex == MATRIX_2x2_SIZE)
                {
                    minorRowIndex++;
                    minorColIndex = 1;
                }
                else
                {
                    minorColIndex++;
                }
            }
        }
    }

    return GetDeterminant2x2(minor);
}

Matrix3x3 GetMinorMatrix(const Matrix3x3& matrix)
{
    Matrix3x3Row minorMatrixRow;
    Matrix3x3 minorMatrix;
    int sign = 1;

    for (size_t rowIndex = 0; rowIndex < MATRIX_3X3_SIZE; rowIndex++)
    {
        for (size_t colIndex = 0; colIndex < MATRIX_3X3_SIZE; colIndex++)
        {
            minorMatrixRow[colIndex] = sign *  GetMinorMatrixElem(matrix, rowIndex, colIndex);
            sign = -sign;
        }
        minorMatrix[rowIndex] = minorMatrixRow;
    }

    return minorMatrix;
}

Matrix3x3 GetTransposedMatrix(const Matrix3x3& matrix)
{
    for (size_t i = 0; i < MATRIX_3X3_SIZE - 1; i++)
    {
        for (size_t j = 0; j < MATRIX_3X3_SIZE; j++)
        {
            if ((i != j) && (j > i))
            {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    return matrix;
}

float GetDeterminant3x3(const Matrix3x3& matrix)
{
    return (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) + (matrix[0][2] * matrix[1][0] * matrix[2][1])
           - (matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]);
}


Matrix3x3Row ParseMatrixRow(const std::string& row)
{
    std::stringstream rowStream(row);
    std::string elem;
    size_t elemIndex = 0;
    Matrix3x3Row matrixRow;

    if (row.empty())
    {
        throw std::runtime_error("Delete empty rows from file");
    }

    while (getline(rowStream, elem, ' '))
    {
        if (!IsNumeric(elem))
        {
            throw std::runtime_error("Matrix must contain only decimal numbers");
        }

        if (elemIndex + 1 > MATRIX_3X3_SIZE)
        {
            throw std::runtime_error("Matrix is not 3x3");
        }
        matrixRow[elemIndex] = (stof(elem));
        elemIndex++;
    }

    if (elemIndex < MATRIX_3X3_SIZE)
    {
        throw std::runtime_error("Matrix is not 3x3");
    }

    return matrixRow;
}

void InitMatrixFromFile(const std::string &fileName, Matrix3x3 &matrix)
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Cant open file");
    }
    if (inputFile.peek() == EOF)
    {
        throw std::runtime_error("File is empty");
    }
    size_t rowIndex = 0;
    std::string row;

    while (getline(inputFile, row))
    {
        Matrix3x3Row matrixRow = ParseMatrixRow(row);
        if (rowIndex + 1 > MATRIX_3X3_SIZE)
        {
            throw std::runtime_error("Matrix is not 3x3");
        }
        matrix[rowIndex] = matrixRow;
        rowIndex++;
    }
    if (rowIndex != MATRIX_3X3_SIZE)
    {
        throw std::runtime_error("Matrix is not 3x3");
    }

}

std::string GetInputFileName(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::runtime_error("Wrong quantity of parameters!\nUsage: invert.exe <file.txt> \n");
    }
    if (argv[1] == "")
    {
        throw std::runtime_error("File name can\'t be empty\n");
    }

    return argv[1];
}

Matrix3x3 Invert3x3Matrix(const Matrix3x3 &matrix)
{
    float det = GetDeterminant3x3(matrix);
    if (det == 0)
    {
        throw std::logic_error("Determinant is zero. Inverted matrix do not exist");
    }
    Matrix3x3 transposedMatrix = GetTransposedMatrix(matrix);
    Matrix3x3 minoreMatrix = GetMinorMatrix(transposedMatrix);
    return MultiplyMatrixByNumber(minoreMatrix, 1 / det);
}

int main(int argc, char* argv[])
{
    try
    {
        std::string fileName = GetInputFileName(argc, argv);
        Matrix3x3 matrix;
        InitMatrixFromFile(fileName, matrix);
        Matrix3x3 invertedMatrix = Invert3x3Matrix(matrix);
        PrintMatrix(invertedMatrix);
    }
    catch (const std::exception & e)
    {
        std::cout << e.what() << '\n';
    }
}