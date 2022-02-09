#ifndef MENU_HEADER
#define MENU_HEADER

#include "Matrix.h"
#include <map>
class Menu{
public:
    Menu();
    void createNewMatrix();
    void addMatrix();
    Matrix* subtractMatrix();
    Matrix* multiplyMatrix();
    Matrix* multiplyScalar();
    Matrix* powerMatrix();
    Matrix* rrefMatrix();
    double  getDeterminant();
    Matrix* swapRowsMatrix();
    Matrix* getTranspose();
    double  getTrace();
    int     getRank();
    map<string, Matrix*> matMap;
};

#endif
