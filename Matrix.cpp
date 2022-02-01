#include "Matrix.h"
#include "InconsistentDimensionsException.h"
#include "IndexOutOfBoundsException.h"
#include "SingularMatrixException.h"
#include "NonSquareMatrixException.h"
using namespace std;
int main() {
	Matrix m(vector<vector<double>>{{1,2,3},{5,6,7},{9,8,1}});
	cout << m;
	cout << (m ^ (-2));
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
		//for (unsigned int j = 0; j < mat.values[i].size(); j++) {
			values[i] = vector<double>(columns);
		//}
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
		throw InconsistentDimensionsException();
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
		throw InconsistentDimensionsException();
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
		throw InconsistentDimensionsException();
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

Matrix operator^(Matrix& mat, double power)
{
	if (mat.columns == mat.rows) {
		//power = 0
		if (power == 0) {
			return identity(mat.columns);
		}
		//either negative or positive power
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
				Matrix adj(mat, identity(mat.rows));
				adj.rref();
				double newPower = power * -1;
				Matrix ret(adj.seperateMatrix());
				return ret^newPower;
			}
		}
	}
	else {
		throw NonSquareMatrixException();
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

Matrix Matrix::operator()(int row, int col, double val)
{
	//in bounds
	if (0 <= row && row < rows && 0 <= col && col < columns) {
		values[row][col] = val;
	}
	else {
		throw IndexOutOfBoundsException();
	}
	return *this;
}

Matrix Matrix::rref() {
	for(int i = 0; i < rows; i ++){
		if(i < columns && values[i][i] != 0){//we have a pivot
			double div = 1.0 / values[i][i];
			for(int j = 0; j < columns; j++){//simplifying current row
				values[i][j] = div * values[i][j];
			}
			//row reduction of values below the current row
			for(int lower = i+1; lower < rows; lower++){
				rowOperations(i, lower, values[lower][i]);
			}
			//row reduction of the values above the current row
			for(int upper = 0; upper < i; upper++){
				rowOperations(i, upper, values[upper][i]);
			}
		}
		if(i < columns && values[i][i] == 0){
			for(int nextNonZero = i; nextNonZero < rows; nextNonZero++){
				//nextNonZero cannot stay as i by definition
				if(values[nextNonZero][i] != 0){
					cout << "Swap" << endl << swapRows(i+1, i);
					i--;
					break;
				}
			}
		}
	}
	return *this;
}

double Matrix::determinant()
{
	return 1;
}

int Matrix::getColumns() {
	return columns;
}

int Matrix::getRows() {
	return rows;
}

Matrix Matrix::swapRows(int row1, int row2) {
	vector<double> temp = vector<double>(columns);
	temp = values[row1];
	values[row1] = values[row2];
	values[row2] = temp;
	return *this;
}

void Matrix::rowOperations(int row1, int row2, double mul){
		for(int i = 0; i < columns; i ++){
			values[row2][i] = values[row2][i] - values[row1][i] * mul;
		}
	}

Matrix Matrix::seperateMatrix(){
		vector<vector<double>> temp = vector<vector<double>>(rows);
		for(unsigned int i = 0; i < temp.size(); i ++){
			temp[i] = vector<double>(columns/2);
		}
		for(int i = 0; i < rows; i ++){
			for(int j = columns/2; j < columns; j++){
				temp[i][j-(columns/2)] = values[i][j];
			}
		}
		return Matrix(temp);
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
