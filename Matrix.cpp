#include "Matrix.h"

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

Matrix::Matrix(vector<vector<int>> init)
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
		if(power <1 &&  power > -1)
			throw DomainException();
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

istream& operator>>(istream& in, Matrix& mat){
	string entire;
	vector<string> rows;
	in.clear();
	getline(in, entire, ']');
	while(entire.at(0) == '\n' || entire.at(0) == ' '){
		entire = entire.substr(1);
	}
	while(entire.at(0) != '['){
		cout << "Matrices must start with a \'[\' and end with \']\'" << endl;
		cout << entire<< endl;
		getline(in, entire, ']');	
	}
	entire = entire.substr(1);
	string entryDelim = ",";
	string lineDelim = ";";
	while(entire.find(lineDelim) != string::npos){
		rows.push_back(entire.substr(0,entire.find(lineDelim)));
		entire = entire.substr(entire.find(lineDelim)+1);
	}
	if(entire != "")
		rows.push_back(entire);
	vector<int> columns = vector<int>();
////////////////////////////////////////////////
	for(int i = 0; i < rows.size(); i++){
		//cout << rows.at(i) << endl;
		int counter = 0;
		string temp = rows.at(i);
		while(temp.find(entryDelim) != string::npos){
			counter++;
			temp = temp.substr(temp.find(entryDelim)+1);
		}
		columns.push_back(counter+1);
	}
	bool sameSize = true;
	for(int i = 1; i < columns.size(); i ++){
		if(columns.at(0) != columns.at(i)){
			sameSize = false;
		}
	}
	if(!sameSize){
		throw InconsistentDimensionsException();
	}
	vector<vector<double>> values = vector<vector<double>>(rows.size());
	for(int i = 0; i < values.size(); i ++){
		values[i] = vector<double>(columns[i]);
	}
	try{
		for(int i = 0; i < rows.size(); i ++){
			string temp = rows.at(i);
			int j = 0;
			while(temp.find(entryDelim) != string::npos){
				values[i][j] = stod(temp.substr(0,temp.find(entryDelim)));
				temp = temp.substr(temp.find(entryDelim)+1);
				j++;
			}
			values[i][j] = stod(temp);
		}
	}
	catch(const std::invalid_argument& oor){
		cout << "Please make sure that the values are entered correctly\nComma deliminated columns and semi-colon deliminated rows" << endl;
	}
	mat.columns = columns[0];
	mat.rows = rows.size();
	mat.values = values;
	return in;
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
	if(rows != columns){
		throw NonSquareMatrixException();
	}
	return determinant(values, rows);
}

double Matrix::determinant(vector<vector<double>> mat,int n){
	double det;
	//Base case
	if(n == 2){
   		return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	}
	vector<vector<double>> subMat = vector<vector<double>>(mat.size());
	for(int i = 0; i < mat.size(); i ++){
		subMat[i] = vector<double>(mat[0].size());
	}
	for (int x = 0; x < n; x++) {
		int subi = 0;
		for (int i = 1; i < n; i++) {
		int subj = 0;
			for (int j = 0; j < n; j++) {
				if (j == x)
					continue;
				subMat[subi][subj] = mat[i][j];
				subj++;
			}
		subi++;
		}
		det = det + (pow(-1, x) * mat[0][x] * determinant(subMat, n - 1 ));
	}
	return det;
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

Matrix Matrix::transpose(){
	vector<vector<double>> trans = vector<vector<double>>(columns);
	for(int i = 0; i < columns; i++){
		trans[i] = vector<double>(rows);
	}
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			trans[j][i] = values[i][j]; 
		}
	}
	return Matrix(trans);
}

double Matrix::trace(){
	if(rows != columns){
		throw NonSquareMatrixException();
	}
	double sum = 0;
	for(int i =0; i < rows; i ++){
		sum += values[i][i];
	}
	return sum;
}

int Matrix::rank(){
	Matrix temp((*this).rref());
	int rank = 0;
	for(int i = 0; i < temp.rows; i++){
		for(int j = 0; j < temp.columns; j++){
			if(values[i][j] == 1){
				rank++;
				break;
			}
		}
	}
	//cout << "Rank: " << rank << endl;
	return rank;
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
