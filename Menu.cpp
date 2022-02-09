#include "Matrix.h"
#include <map>

using namespace std;

int main(){
    map<string, Matrix> matrices;
    cout << "Welcome to the Calculator App!" << endl;
    cout << "Please enter in a matrix" << endl;
    Matrix* m1 = new Matrix(1,1);
    cin >> *m1;
    cout << *m1;
    return 0;
}

int menuOptions(){

}
