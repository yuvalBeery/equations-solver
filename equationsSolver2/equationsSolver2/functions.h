#pragma once
#include <iostream>
#include "fraction.h"
#define MAX_ARRAY_LENGTH 9
#define DEFAULT_ARRAY_LENGTH 3
int currentArrayLength = DEFAULT_ARRAY_LENGTH;


//convert system string to standart string
void MarshalString(System::String^ s, std::string& os) {
	using namespace System::Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

void switchRows(fraction matrix[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH + 1], int row1, int row2)
{
	fraction tmpRow[MAX_ARRAY_LENGTH + 1];
	for (int i = 0; i < MAX_ARRAY_LENGTH + 1; i++)
		tmpRow[i] = fraction();
	for (int i = 0; i < currentArrayLength + 1; i++)
	{
		tmpRow[i] = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = tmpRow[i];
	}
}

bool arrangeMatrix(fraction matrix[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH + 1], int row)
{
	for (int i = row + 1; i < currentArrayLength; i++)
	{
		if (matrix[i][row].numerator != 0)
		{
			switchRows(matrix, row, i);
			return true;
		}
	}

	for (int i = 0; i < row; i++)
	{
		if (matrix[i][row].numerator != 0 && matrix[i][i].numerator == 0)
		{
			switchRows(matrix, row, i);
			return true;
		}
	}

	return false;
}

void solve(fraction matrix[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH + 1])
{
	for (int column = 0; column < currentArrayLength; column++)
	{
		if (matrix[column][column].numerator == 0)
		{
			if (!arrangeMatrix(matrix, column))
				continue;
		}

		for (int row = 0; row < currentArrayLength; row++)
		{
			if (row != column)
			{
				for (int i = column + 1; i < currentArrayLength + 1; i++)
				{
					matrix[row][i] = matrix[row][i] - (matrix[column][i] * matrix[row][column] / matrix[column][column]);
				}
				matrix[row][column] = long long(0);
			}
		}
	}
	for (int i = 0; i < currentArrayLength; i++)
	{
		for (int j = i + 1; j < currentArrayLength + 1; j++)
		{
			if (matrix[i][i].numerator != 0)
				matrix[i][j] /= matrix[i][i];
		}
		if (matrix[i][i].numerator != 0)
			matrix[i][i] = long long(1);
	}
}


void setValueArray(fraction matrix[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH + 1], std::string valueArray[MAX_ARRAY_LENGTH], bool isSimulated)
{
	std::string tmpValue;
	for (int i = 0; i < currentArrayLength; i++)
	{
		if (matrix[i][i].numerator == 0)
		{
			if (matrix[i][currentArrayLength].numerator == 0)
				valueArray[i] = "0/0";
			else
				valueArray[i] = "1/0";
		}

		else
		{
			valueArray[i] = matrix[i][currentArrayLength].show(isSimulated);
			for (int j = i + 1; j < currentArrayLength; j++)
			{
				if (matrix[i][j].numerator != 0)
				{
					if (long double(matrix[i][j].numerator) / long double(matrix[i][j].base) > 0)
					{
						if (matrix[i][j].show(true) == "1")
						{
							MarshalString(" - " + "x" + "[" + (j + 1) + "]", tmpValue);
							valueArray[i] += tmpValue;
						}
						else
							valueArray[i] += " - " + matrix[i][j].show(isSimulated) + "x" + "[" + std::to_string(j + 1) + "]";
					}

					else
					{
						matrix[i][j].numerator = std::abs(matrix[i][j].numerator);
						matrix[i][j].base = std::abs(matrix[i][j].base);

						if (matrix[i][j].show(true) == "1")
						{
							MarshalString(" + " + "x" + "[" + (j + 1) + "]", tmpValue);
							valueArray[i] += tmpValue;
						}
						else
							valueArray[i] += " + " + matrix[i][j].show(isSimulated) + "x" + "[" + std::to_string(j + 1) + "]";
					}
				}
			}
		}
	}
}