#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
//need to implement the determinant
class Matrix {
public:
	Matrix(int row, int col);
	Matrix(const Matrix& mat);
	Matrix(vector<vector<int>> init);
	Matrix(vector<vector<double>> init);
	Matrix(const Matrix& mat1, const Matrix& mat2);
	friend Matrix operator +(Matrix& mat1, Matrix& mat2);
	friend Matrix operator -(Matrix& mat1, Matrix& mat2);
	friend Matrix operator *(Matrix& mat1, Matrix& mat2);
	friend Matrix operator *(Matrix& mat, int val);
	friend Matrix operator *(Matrix& mat, double val);
	friend Matrix operator ^(Matrix& mat, double power);
	friend ostream& operator<<(ostream& out, const Matrix& mat);
	double operator ()(int row, int col);
	Matrix operator ()(int row, int col, double val);
	Matrix rref();
	double determinant();
	int getRows();
	int getColumns();
	Matrix swapRows(int row1, int row2);
private:
	int rows;
	int columns;
	vector<vector<double>> values;
	void rowOperations(int row1, int row2, double mul);
	Matrix seperateMatrix();
	vector<vector<int>> getSigns();
};
Matrix operator *(int val, Matrix& mat);
Matrix operator *(double val, Matrix& mat);
Matrix identity(int n);
#endif
