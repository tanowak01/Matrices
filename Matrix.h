#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
//need to implement the rref
//need to implement the determinant
//need to add destructor
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
	Matrix rref();
	double determinant();
	int getRows();
	int getColumns();
	void swapRows(int row1, int row2);
private:
	int rows;
	int columns;
	vector<vector<double>> values;
	void rowOperations(int row1, int row2, double mul){
		for(int i = 0; i < columns; i ++){
			values[row2][i] = values[row2][i] - values[row1][i] * mul;
		}
	}
};
Matrix operator *(int val, Matrix& mat);
Matrix operator *(double val, Matrix& mat);
Matrix identity(int n);
#endif
