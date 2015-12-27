#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <string.h>

using namespace std;

class Matrix{

public:
	Matrix(int m, int n);
	Matrix(double ** matrix, int n, int m);
	Matrix();
	~Matrix();
	Matrix(const Matrix& Matrix);

	Matrix operator = (const Matrix& Matrix);
	Matrix operator +(const Matrix& B);
	Matrix operator -(const Matrix& B);
	Matrix operator *(const Matrix& B);

	double det();
	double norm();
	double getValue(int i, int j) const;
	void setValue(int i, int j, double value);
	int getRowCount();
	int getColCount();
	double ** getMatrix();
	Matrix& invert();
	Matrix& transpose();

	int m;
	int n;
	double ** matrix;

private:

	double _det(double **A, int N);
};

#endif
