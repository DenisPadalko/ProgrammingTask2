#pragma once
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;
class Matrix
{
private:
	double** MatrixElements;
	size_t Columns;
	size_t Rows;
public:
	Matrix();
	Matrix(const double** AnotherMatrix, const size_t AnotherMatrixRows, const size_t AnotherMatrixColumns);
	Matrix(const Matrix& AnotherMatrix);
	Matrix(Matrix&& AnotherMatrix);
	Matrix(const int Number);
	Matrix(const char* AnotherMatrix);
	~Matrix();
	Matrix& operator=(const Matrix& AnotherMatrix);
	Matrix& operator=(Matrix&& AnotherMatrix);
	void ShowMatrix() const;
	void ConvertMatrixToString(string& Str) const;
	double** GetMatrix() const;
	void SetMatrixElem(const double Elem, const size_t RowsPosition, const size_t ColumnsPosition);
	void SetMatrix(double** Matr);
	const size_t GetRows() const;
	void SetRows(const int Number);
	const size_t GetColumns() const;
	void SetColumns(const int Number);

	friend const Matrix operator+ (Matrix Left, const Matrix& Right);
	friend const Matrix operator+ (Matrix Left, const int Number);
	friend const Matrix operator+ (Matrix Left, const char* Str);
	friend const Matrix operator- (Matrix Left, const Matrix& Right);
	friend const Matrix operator- (Matrix Left, const int Number);
	friend const Matrix operator- (Matrix Left, const char* Str);
	friend const Matrix operator* (Matrix Left, const Matrix& Right);
	friend const Matrix operator* (Matrix Left, const int Number);
	friend const Matrix operator* (Matrix Left, const char* Str);

	const Matrix& operator+=(const Matrix& AnotherMatrix);
	const Matrix& operator+=(const int Number);
	const Matrix& operator-=(const Matrix& AnotherMatrix);
	const Matrix& operator-=(const int Number);
	const Matrix& operator*=(const Matrix& AnotherMatrix);
	const Matrix& operator*=(const int Number);

	friend const bool operator<(const Matrix& Left, const Matrix& Right);
	friend const bool operator>(const Matrix& Left, const Matrix& Right);
	friend const bool operator>=(const Matrix& Left, const Matrix& Right);
	friend const bool operator<=(const Matrix& Left, const Matrix& Right);
	friend const bool operator==(const Matrix& Left, const Matrix& Right);
	friend const bool operator!=(const Matrix& Left, const Matrix& Right);

	friend ostream& operator<<(ostream& out, const Matrix& M);

	void MatrixTransponation();
	void CreateNullMatrix(const size_t Rows, const size_t Columns);

	const float CalculateSumOfElementsInDiagonals() const;
	const float CalculateTraceOfTheMatrix() const;
};

const double FindDeterminant(const Matrix& M);