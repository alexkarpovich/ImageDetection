#include "../headers/Matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <cassert>

Matrix::Matrix() {

}

Matrix::Matrix(int m, int n) {
	this->m = m;
	this->n = n;
	this->matrix = new double*[m];
	for (int i = 0; i < m; i++) {
		this->matrix[i] = new double[n];
	}
}

Matrix::Matrix(double ** matrix, int m, int n) {
	this->matrix = new double*[m];
	for (int i = 0; i < m; i++) {
		this->matrix[i] = new double[n];
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			this->matrix[i][j] = matrix[i][j];
		}
	}

	this->n = n;
	this->m = m;
}

Matrix::~Matrix() {
	for (int i = 0; i < m; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
Matrix::Matrix(const Matrix& Matrix) {
	m = Matrix.m;
	n = Matrix.n;
	matrix = new double*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new double[n];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = Matrix.matrix[i][j];
		}
	}
}

double ** Matrix::getMatrix() {
	return this->matrix;
}

Matrix Matrix::operator=(const Matrix& B) {
	m = B.m;
	n = B.n;
	matrix = new double*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new double[n];
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = B.matrix[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator +(const Matrix & B) {

	if (!(m == B.m && n == B.n))
		exit(0);

	Matrix C(m, n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			C.matrix[i][j] = matrix[i][j] + B.matrix[i][j];
		}

	return *(new Matrix(C));
}

Matrix Matrix::operator-(const Matrix& B) {
	if (!(m == B.m && n == B.n)) {
		exit(0);
	}

	Matrix C(m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			C.matrix[i][j] = matrix[i][j] - B.matrix[i][j];
		}
	}

	return *(new Matrix(C));
}

Matrix Matrix::operator*(const Matrix& B) {
	if (n != B.m)
		exit(0);

	Matrix C(m, B.n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < B.n; j++) {
			C.matrix[i][j] = 0;
		}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < B.n; j++) {
			for (int k = 0; k < n; k++) {
				C.matrix[i][j] += (matrix[i][k]) * (B.matrix[k][j]);
			}
		}

	return *(new Matrix(C));
}

double Matrix::det() {
	if (m != n) {
		exit(1);
	}

	return _det(matrix, m);
}

double Matrix::norm() {
	if (m == n && m == 1) {
		return matrix[0][0];
	}

	double sum = 0, max = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			sum += matrix[i][j];
		}
		if (!i) {
			max = sum;
			sum = 0;
		} else {
			if (max < sum)
				max = sum;
			sum = 0;
		}
	}

	return max;
}

double Matrix::_det(double **A, int N) {
	int i, j;
	double **M;
	double D = 0;

	if (N == 2) {
		D = A[0][0] * A[1][1] - A[0][1] * A[1][0];
	} else {
		M = new double*[N - 1];

		for (i = 0; i < N; i++) {
			for (j = 0; j < N - 1; j++) {
				if (j < i) {
					M[j] = A[j];
				} else {
					M[j] = A[j + 1];
				}
			}
			D += pow(-1, (double) (i + j)) * _det(M, N - 1) * A[i][N - 1];
		}
		delete M;
	}

	return D;

}
Matrix& Matrix::invert() {
	Matrix M(this->matrix, m, n);

	double ** T = new double*[M.m];
	for (int i = 0; i < m; i++)
		T[i] = new double[M.m];

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			T[i][j] = (i == j ? 1 : 0);

	for (int i = 0; i < m; i++) {
		double tmp = M.matrix[i][i];
		for (int j = m - 1; j >= 0; j--) {
			T[i][j] /= tmp;
			M.matrix[i][j] /= tmp;
		}
		for (int j = 0; j < m; j++)
			if (j != i) {
				tmp = M.matrix[j][i];
				for (int k = m - 1; k >= 0; k--) {
					T[j][k] -= T[i][k] * tmp;
					M.matrix[j][k] -= M.matrix[i][k] * tmp;
				}
			}
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			M.matrix[i][j] = T[i][j];

	return *(new Matrix(M));
}

Matrix& Matrix::transpose() {
	Matrix T(n, m);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			T.setValue(j, i, matrix[i][j]);
		}
	}

	return *(new Matrix(T));
}

double Matrix::getValue(int i, int j) const {
	return matrix[i][j];
}

void Matrix::setValue(int i, int j, double value) {
	matrix[i][j] = value;
}

int Matrix::getRowCount() {
	return m;
}

int Matrix::getColCount() {
	return n;
}
