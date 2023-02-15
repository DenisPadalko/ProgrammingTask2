#include "Matrix.h"
#include "Exceptions.h"

Matrix::Matrix() : Columns(3), Rows(3)
{
	MatrixElements = new double* [Rows];
	for (size_t i = 0; i < Rows; ++i) 
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = j + 1;
		}
	}
};

Matrix::Matrix(const double** AnotherMatrix, const size_t AnotherMatrixRows,
               const size_t AnotherMatrixColumns) : Columns(AnotherMatrixColumns), Rows(AnotherMatrixRows)
{
	MatrixElements = new double* [Rows];
	for (size_t i = 0; i < Rows; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix[i][j];
		}
	}
};

Matrix::Matrix(const Matrix& AnotherMatrix) : Columns(AnotherMatrix.Columns), Rows(AnotherMatrix.Rows)
{
	MatrixElements = new double* [Rows];
	for (size_t i = 0; i < Rows; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix.MatrixElements[i][j];
		}
	}
};

Matrix::Matrix(Matrix&& AnotherMatrix) : MatrixElements(AnotherMatrix.MatrixElements), Columns(AnotherMatrix.Columns),
                                         Rows(AnotherMatrix.Rows)
{
	AnotherMatrix.MatrixElements = nullptr;
};

Matrix::Matrix(const int Number) : Columns(1), Rows(1)
{
	MatrixElements = new double* [1];
	MatrixElements[0] = new double[1];
	MatrixElements[0][0] = Number;
};

Matrix::Matrix(const char* AnotherMatrix) : Columns(1), Rows(0)
{
	size_t i = 0, j = 0;
	size_t Col = 1;
	while (AnotherMatrix[i] != '\0')
	{
		if (AnotherMatrix[i] == ',')
		{
			Col += 1;
		}
		else if (AnotherMatrix[i] == ';')
		{
			Rows += 1;
			Columns = Col;
			Col = 1;
		}
		i++;
	}
	MatrixElements = new double* [Rows];
	for (i = 0; i < Rows; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	const char s[6] = "[];, ";
	char* NextNumber;
	char* Number = strtok_s((char*)AnotherMatrix, s, &NextNumber);
	for (i = 0; i < Rows; ++i)
	{
		for (j = 0; j < Columns; j++)
		{
			MatrixElements[i][j] = strtod(Number, NULL);
			Number = strtok_s(NULL, s, &NextNumber);
		}
	}
};

Matrix::~Matrix()
{
	if (MatrixElements != nullptr)
	{
		for (size_t i = 0; i < Rows; ++i)
		{
			delete[] MatrixElements[i];
		}
		delete[] MatrixElements;
	}
};

Matrix& Matrix::operator=(const Matrix& AnotherMatrix)
{
	if (&AnotherMatrix == this) return *this;
	for (size_t i = 0; i < Rows; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;

	Columns = AnotherMatrix.Columns;
	Rows = AnotherMatrix.Rows;
	MatrixElements = new double* [Rows];
	for (size_t i = 0; i < Rows; i++)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix.MatrixElements[i][j];
		}
	}

	return *this;
};

Matrix& Matrix::operator=(Matrix&& AnotherMatrix)
{
	if (&AnotherMatrix == this) return *this;

	if(MatrixElements)
	{
		for (size_t i = 0; i < Rows; ++i)
		{
			delete[] MatrixElements[i];
		}
		delete[] MatrixElements;
	}

	Rows = AnotherMatrix.Rows;
	Columns = AnotherMatrix.Columns;
	MatrixElements = AnotherMatrix.MatrixElements;
	AnotherMatrix.MatrixElements = nullptr;

	return *this;
};

void Matrix::ShowMatrix() const
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			cout << MatrixElements[i][j] << " ";
		}
		cout << endl;
	}
};

void Matrix::ConvertMatrixToString(string& Str) const
{
	Str += '[';
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			Str += to_string(MatrixElements[i][j]);
			if (j < (Columns - 1))
			{
				Str += ", ";
			}
		}
		Str += "; ";
	}
	Str += ']';
};

double** Matrix::GetMatrix() const
{
	return MatrixElements;
};

void Matrix::SetMatrixElem(const double Elem, const size_t RowsPosition, const size_t ColumnsPosition)
{
	MatrixElements[RowsPosition][ColumnsPosition] = Elem;
};

void Matrix::SetMatrix(double** Matr)
{
	for (size_t i = 0; i < Rows; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;
	MatrixElements = Matr;
};

const size_t Matrix::GetRows() const
{
	return Rows;
};

void Matrix::SetRows(const int Number)
{
	Rows = Number;
};

const size_t Matrix::GetColumns() const
{
	return Columns;
};

void Matrix::SetColumns(const int Number)
{
	Columns = Number;
};

const bool IsThereAnOverflowWhenAdding(const double FirstNumber, const double SecondNumber)
{
	return ((SecondNumber > 0) && (FirstNumber > (DBL_MAX - SecondNumber))) ||
		((SecondNumber < 0) && (FirstNumber < (DBL_MIN - SecondNumber)));
}

const Matrix operator+ (Matrix Left, const Matrix& Right)
{
	return Left += Right;
};

const Matrix operator+ (Matrix Left, const int Number)
{
	return Left += Number;
};

const Matrix operator+ (Matrix Left, const char* Str)
{
	return Left + atoi(Str);
};

const bool IsThereAnOverflowWhenSubtracting(const double FirstNumber, const double SecondNumber) 
{
	return ((SecondNumber > 0) && (FirstNumber < (DBL_MIN + SecondNumber))) ||
		((SecondNumber < 0) && (FirstNumber > (DBL_MAX + SecondNumber)));
}

const Matrix operator- (Matrix Left, const Matrix& Right)
{
	return Left -= Right;
};

const Matrix operator- (Matrix Left, const int Number)
{
	return Left -= Number;
};

const Matrix operator- (Matrix Left, const char* Str)
{
	return Left - atoi(Str);
};

const Matrix operator* (Matrix Left, const Matrix& Right)
{
	return Left *= Right;
};

const Matrix operator* (Matrix Left, const int Number)
{
	return Left *= Number;
};

const Matrix operator* (Matrix Left, const char* Str)
{
	return Left * atoi(Str);
};

void GetMatr(const double** Mas, double** P, const int i, const int j, const int m)
{
	int di, dj;
	di = 0;
	for (size_t ki = 0; ki < m - 1; ++ki)
	{
		if (ki == i) di = 1;
		dj = 0;
		for (size_t kj = 0; kj < m - 1; ++kj)
		{
			if (kj == j) dj = 1;
			P[ki][kj] = Mas[ki + di][kj + dj];
		}
	}
}

const double FindDeterminant(const Matrix& M)
{
	double Determinant = 0;
	int k, n;
	double** P;
	P = new double* [M.GetRows()];
	for (int i = 0; i < M.GetRows(); ++i) P[i] = new double[M.GetRows()];
	k = 1;
	n = M.GetRows() - 1;
	if (M.GetRows() == 1)
	{
		return M.GetMatrix()[0][0];
	}
	if (M.GetRows() == 2)
	{
		Determinant = M.GetMatrix()[0][0] * M.GetMatrix()[1][1] - (M.GetMatrix()[1][0] * M.GetMatrix()[0][1]);
		return Determinant;
	}
	if (M.GetRows() > 2)
	{
		for (size_t i = 0; i < M.GetRows(); ++i)
		{
			GetMatr((const double**)M.GetMatrix(), P, i, 0, M.GetRows());
			Matrix TempMatrix((const double**)(P), n, n);
			Determinant = Determinant + k * M.GetMatrix()[i][0] * FindDeterminant(TempMatrix);
			k = -k;
		}
	}
	return Determinant;
}

int GetMinor(const double** A, double** B, int x, int y, int size)
{
	int XCount = 0, YCount = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (i != x)
		{
			YCount = 0;
			for (size_t j = 0; j < size; ++j)
			{
				if (j != y)
				{
					B[XCount][YCount] = A[i][j];
					YCount++;
				}
			}
			XCount++;
		}
	}
	return 0;
}

double FindArrayDeterminant(const double** A, const int Size)
{
	if (Size == 1)
	{
		return A[0][0];
	}
	else
	{
		int Det = 0;
		double** Minor = new double* [Size - 1];
		for (size_t i = 0; i < Size; ++i)
		{
			Minor[i] = new double[Size - 1];
		}
		for (size_t i = 0; i < Size; ++i)
		{
			GetMinor(A, Minor, 0, i, Size);
			Det += pow(-1, i) * A[0][i] * FindArrayDeterminant((const double**)Minor, Size - 1);
		}
		return Det;
	}
}

void FindAlgDop(const double** A, const int Size, double** B)
{
	int Det = FindArrayDeterminant(A, Size);
	if (Det > 0) Det = -1;
	else Det = 1;
	double** Minor = new double* [Size - 1];
	for (size_t i = 0; i < Size - 1; ++i)
	{
		Minor[i] = new double[Size - 1];
	}
	for (size_t j = 0; j < Size; ++j)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			GetMinor(A, Minor, j, i, Size);
			if ((i + j) % 2 == 0)
				B[j][i] = -Det * FindArrayDeterminant((const double**)Minor, Size - 1);
			else
				B[j][i] = Det * FindArrayDeterminant((const double**)Minor, Size - 1);
		}
	}
	for (size_t i = 0; i < Size - 1; ++i)
	{
		delete[] Minor[i];
	}
	delete[] Minor;
}

void Matrix::MatrixTransponation()
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = i; j < Columns; ++j)
		{
			swap(MatrixElements[i][j], MatrixElements[j][i]);
		}
	}
}

void Matrix::CreateNullMatrix(const size_t Rows, const size_t Columns) 
{
	MatrixElements = new double* [Rows];
	for (size_t i = 0; i < Rows; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = 0;
		}
	}
}

const Matrix& Matrix::operator+=(const Matrix& AnotherMatrix)
{
	if ((Rows != AnotherMatrix.Rows) || (Columns != AnotherMatrix.Columns))
	{
		throw MatricesDoNotMatch("Matrices don't match. Failed to add matrices");
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			if (IsThereAnOverflowWhenAdding(MatrixElements[i][j], AnotherMatrix.MatrixElements[i][j]))
			{
				throw OverflowWhenAddingMatrices("An overflow occurred while adding matrices");
			}
			else MatrixElements[i][j] += AnotherMatrix.MatrixElements[i][j];
		}
	}
	return *this;
};

const Matrix& Matrix::operator+=(const int Number)
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			if (IsThereAnOverflowWhenAdding(MatrixElements[i][j], Number))
			{
				throw OverflowWhenAddingMatrices("An overflow occurred while adding matrices");
			}
			else MatrixElements[i][j] += Number;
		}
	}
	return *this;
};

const Matrix& Matrix::operator-=(const Matrix& AnotherMatrix)
{
	if ((Rows != AnotherMatrix.Rows) || (Columns != AnotherMatrix.Columns))
	{
		throw MatricesDoNotMatch("Matrices don't match. Failed to subtract matrices");
	}
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			if (IsThereAnOverflowWhenSubtracting(MatrixElements[i][j], AnotherMatrix.MatrixElements[i][j]))
			{
				throw OverflowWhenSubtractingMatrices("An overflow occurred while subtracting matrices");
			}
			else MatrixElements[i][j] -= AnotherMatrix.MatrixElements[i][j];
		}
	}
	return *this;
};

const Matrix& Matrix::operator-=(const int Number)
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			if (IsThereAnOverflowWhenSubtracting(MatrixElements[i][j], Number))
			{
				throw OverflowWhenSubtractingMatrices("An overflow occurred while subtracting matrices");
			}
			else MatrixElements[i][j] -= Number;
		}
	}
	return *this;
};

const Matrix& Matrix::operator*=(const Matrix& AnotherMatrix)
{
	if (Columns != AnotherMatrix.Rows)
	{
		throw MatricesDoNotMatch("Matrices don't match. Failed to multiply matrices");
	}
	Matrix Temp = move(*this);
	Columns = AnotherMatrix.Columns;
	CreateNullMatrix(Rows, Columns);
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			for (size_t k = 0; k < AnotherMatrix.Rows; ++k)
			{
				MatrixElements[i][j] += Temp.MatrixElements[i][k] * AnotherMatrix.MatrixElements[k][j];
			}
		}
	}
	return *this;
};

const Matrix& Matrix::operator*=(const int Number)
{
	for (size_t i = 0; i < Rows; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] *= Number;
		}
	}
	return *this;
};

const bool operator<(const Matrix& Left, const Matrix& Right)
{
	if (Left == Right) return false;
	if ((Left.Rows != Right.Rows) || (Left.Columns != Right.Columns))
	{
		throw MatricesCanNotBeCompared("Those matrices cannot be compared");
	}
	float FirstResult = Left.CalculateSumOfElementsInDiagonals();
	float SecondResult = Right.CalculateSumOfElementsInDiagonals();
	if(FirstResult == SecondResult)
	{
		FirstResult = Left.CalculateTraceOfTheMatrix();
		SecondResult = Right.CalculateTraceOfTheMatrix();
		if(FirstResult < SecondResult) return false;
		else return true;
	}
	else if(FirstResult < SecondResult) return true;
	else return false;
};

const bool operator>(const Matrix& Left, const Matrix& Right)
{
	return Right < Left;
};

const bool operator>=(const Matrix& Left, const Matrix& Right)
{
	return !(Left < Right);
};

const bool operator<=(const Matrix& Left, const Matrix& Right)
{
	return !(Right < Left);
};

const bool operator==(const Matrix& Left, const Matrix& Right)
{
	if (&Left == &Right) return true;
	if ((Left.Rows != Right.Rows) || (Left.Columns != Right.Columns))
	{
		throw MatricesCanNotBeCompared("Those matrices cannot be compared");
	}
	bool Result = false;
	for (size_t i = 0; i < Left.Rows; ++i)
	{
		for (size_t j = 0; j < Left.Columns; ++j)
		{
			if (Left.MatrixElements[i][j] != Right.MatrixElements[i][j]) return false;
		}
	}
	return true;
};

const bool operator!=(const Matrix& Left, const Matrix& Right)
{
	return !(Left == Right);
};

ostream& operator<<(ostream& out, const Matrix& M)
{
	for(size_t i = 0; i < M.Rows; ++i)
	{
		for(size_t j = 0; j < M.Columns; ++j)
		{
			out << M.MatrixElements[i][j] << " ";
		}
		out << endl;
	}
	return out;
}


const float Matrix::CalculateSumOfElementsInDiagonals() const
{
	float Result = 0;
	for(int i = 0; i < Rows; ++i)
	{
		Result += MatrixElements[i][i];
	}
	for(int i = Rows - 1; i >= 0; --i)
	{
		Result += MatrixElements[i][i];
	}
	return Result;
}

const float Matrix::CalculateTraceOfTheMatrix() const
{
	float Result = 0;
	for(size_t i = 0; i < Rows; ++i)
	{
		Result += MatrixElements[i][i];
	}
	return Result;
}