#include "Matrix.h"
#include "DimensionMismatchException.h"
#include "InconsistentDimensionsException.h"
#include "IndexOutOfBoundsException.h"
#include "SingularMatrixException.h"
using namespace std;
int main() {
	Matrix m1(vector<vector<double>>{ {1,2},{3,4}});	
	Matrix m4(vector<vector<double>>{ {10, 11}, { 12,18 }});
	Matrix m2(vector<vector<double>>{{3,4}});
	Matrix m3(vector<vector<double>>{ {4} ,{9}});
	cout << m1;
	cout << m4;
	cout << m1 - m4;
	return 0;
}

Matrix::Matrix(int row, int col)
{
	//cout << "ROWCOL" << endl;
	this->rows = row;
	this->columns = col;
	
	values = vector<vector<double>>(rows);
	for (int i = 0; i < row; i++) {
		values[i] = vector<double>(columns);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			values[i][j] = 0;
		}
	}

}

Matrix::Matrix(const Matrix& mat)
{
	//cout << "MATRIX" << endl;
	this->columns = mat.columns;
	this->rows = mat.rows;
	values = vector<vector<double>>(rows);
	for (unsigned int i = 0; i < mat.values.size(); i++) {
		for (unsigned int j = 0; j < mat.values[i].size(); j++) {
			values[i] = vector<double>(columns);
		}
	}
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.columns; j++) {
			this->values[i][j] = mat.values[i][j];
		}
	}
}

Matrix::Matrix(vector<vector<double>> init)
{
	//cout << "VECTOR" << endl;
	int	size = init[0].size();
	for (unsigned int i = 0; i < init.size(); i++) {
		if (init[i].size() != size) {
			throw InconsistentDimensionsException();
		}
	}
	this->rows = init.size();
	this->columns = init[0].size();
	values = vector<vector<double>>(rows);
	for (unsigned int i = 0; i < init.size(); i++) {
			values[i] = vector<double>(columns);
	}
	for (unsigned int i = 0; i < init.size(); i++) {
		for (unsigned int j = 0; j < init[0].size(); j++) {
			values[i][j] = init[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& mat1, const Matrix& mat2)
{
	if (mat1.rows != mat2.rows) {
		throw InconsistentDimensionsException();
	}
	else {
		rows = mat1.rows;
		columns = mat1.columns + mat2.columns;
		values = vector<vector<double>>(rows);
		for (unsigned int i = 0; i < mat1.values.size(); i++) {
			values[i] = vector<double>(columns);
		}
		for (int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < mat1.values[0].size() + mat2.values[0].size(); j++) {
				if (j < mat1.values[0].size()) {
					values[i][j] = mat1.values[i][j];
				}
				else {
					values[i][j] = mat2.values[i][j-mat1.values[0].size()];
				}
			}
		}
	}
}

Matrix operator+(Matrix& mat1, Matrix& mat2)
{	
	if (mat1.rows == mat2.rows && mat1.columns == mat2.columns) {
		for (int i = 0; i < mat1.rows; i++) {
			for (int j = 0; j < mat1.columns; j++) {
				mat1.values[i][j] += mat2.values[i][j];
			}
		}
	}
	else {
		throw DimensionMismatchException();
	}
	return mat1;
}

Matrix operator-(Matrix& mat1, Matrix& mat2)
{
	if (mat1.rows == mat2.rows && mat1.columns == mat2.columns) {
		for (int i = 0; i < mat1.rows; i++) {
			for (int j = 0; j < mat1.columns; j++) {
				mat1.values[i][j] -= mat2.values[i][j];
			}
		}
	}
	else {
		throw DimensionMismatchException();
	}
	return mat1;
}

Matrix operator*(Matrix& mat1, Matrix& mat2)
{	
	Matrix retMat(mat1.rows, mat2.columns);
	if (mat1.columns == mat2.rows) {
		for (unsigned int i = 0; i < mat1.values.size(); i++)
			for (unsigned int j = 0; j < mat2.values[0].size(); j++)
				for (unsigned int k = 0; k < mat1.values[0].size(); k++) {
					retMat.values[i][j] += mat1.values[i][k] * mat2.values[k][j];
				}
	}
	else {
		throw DimensionMismatchException();
	}
	return retMat;
}

Matrix operator*(Matrix& mat, int val)
{
	Matrix retMat(mat);
	for (unsigned int i = 0; i < retMat.values.size(); i++) {
		for (unsigned int j = 0; j < retMat.values[0].size(); j++) {
			retMat.values[i][j] = mat.values[i][j] * val;
		}
	}
	return retMat;
}

Matrix operator*(Matrix& mat, double val)
{
	Matrix retMat(mat);
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.columns; j++) {
			retMat.values[i][j] = mat.values[i][j] * val;
		}
	}
	return retMat;
}

Matrix operator^(Matrix& mat, int power)
{
	if (mat.columns == mat.rows) {
		//power = 0
		if (power == 0) {
			return identity(mat.columns);
		}
		//either negative or positive power
		else {
			Matrix retMat(mat);
			if (power > 0) {
				for (int i = 1; i < power; i++) {
					retMat = retMat * mat;
				}
				return retMat;
			}
			//power is negative
			else {
				if (mat.determinant() == 0) {
					throw SingularMatrixException();
				}
				else {

				}
			}
		}
	}
	else {
		throw DimensionMismatchException();
	}
}

ostream& operator<<(ostream& out, const Matrix& mat)
{
	for (unsigned int i = 0; i < mat.values.size(); i++) {
		for (unsigned int j = 0; j < mat.values[0].size(); j++) {
			cout << mat.values[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}

double Matrix::operator()(int row, int col)
{
	//in bounds
	if (0 <= row && row < rows && 0 <= col && col < columns) {
		return values[row][col];
	}
	else {
		throw IndexOutOfBoundsException();
	}
}

void Matrix::operator()(int row, int col, double val)
{
	//in bounds
	if (0 <= row && row < rows && 0 <= col && col < columns) {
		values[row][col] = val;
	}
	else {
		throw IndexOutOfBoundsException();
	}
}

Matrix Matrix::rref() {
	return ;
}

double Matrix::determinant()
{/*
	if (rows != columns)
		throw DimensionMismatchException();
	else {
		if (rows == 1)
			return values[0][0];
		else {
			Matrix cofactors(rows,columns);
			int multiplier = 1;
			for(int i = 0; i < )
		}
	}*/
	return 0;
}

int Matrix::getColumns() {
	return columns;
}

int Matrix::getRows() {
	return rows;
}

Matrix operator*(int val, Matrix& mat)
{
	return mat * val;
}

Matrix operator*(double val, Matrix& mat)
{
	return mat * val;
}

Matrix identity(int n)
{
	Matrix retMat(n, n);
	for (int i = 0; i < n; i++)
		retMat(i, i, 1);
	return retMat;
}