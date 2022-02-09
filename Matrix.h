#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <iostream>
#include <ostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include "InconsistentDimensionsException.h"
#include "IndexOutOfBoundsException.h"
#include "SingularMatrixException.h"
#include "NonSquareMatrixException.h"
#include "DomainException.h"
//using namespace std;
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
	friend istream& operator>>(istream& in, Matrix& mat);
	double operator ()(int row, int col);
	Matrix operator ()(int row, int col, double val);
	Matrix rref();
	double determinant();
	int getRows();
	int getColumns();
	Matrix swapRows(int row1, int row2);
	Matrix transpose(); 
	Matrix eigenValues();
	double trace();
	int rank();
private:
	int rows;
	int columns;
	vector<vector<double>> values;
	void rowOperations(int row1, int row2, double mul);
	Matrix seperateMatrix();
	double determinant(vector<vector<double>> mat,int n);
};
Matrix operator *(int val, Matrix& mat);
Matrix operator *(double val, Matrix& mat);
Matrix identity(int n);
#endif
