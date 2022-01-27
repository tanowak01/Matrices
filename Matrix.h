#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
class Matrix {
public:
	Matrix(int row, int col);
	Matrix(const Matrix& mat);
	Matrix(vector<vector<double>> init);
	Matrix(const Matrix& mat1, const Matrix& mat2);
	friend Matrix operator +(Matrix& mat1, Matrix& mat2);
	friend Matrix operator -(Matrix& mat1, Matrix& mat2);
	friend Matrix operator *(Matrix& mat1, Matrix& mat2);
	friend Matrix operator *(Matrix& mat, int val);
	friend Matrix operator *(Matrix& mat, double val);
	friend Matrix operator ^(Matrix& mat, int power);
	friend ostream& operator<<(ostream& out, const Matrix& mat);
	double operator ()(int row, int col);
	void operator ()(int row, int col, double val);
	//Matrix rref();
	double determinant();

private:
	int rows;
	int columns;
	vector<vector<double>> values;
};
Matrix identity(int n);
#endif