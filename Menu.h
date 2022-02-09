#ifndef MENU_HEADER
#define MENU_HEADER

#include "Matrix.h"
#include <map>
class Menu{
public:
    Menu();
    void createNewMatrix();
    void addMatrix();
    void subtractMatrix();
    void multiplyMatrix();
    void multiplyScalar();
    void powerMatrix();
    void rrefMatrix();
    double  getDeterminant();
    void swapRowsMatrix();
    void getTranspose();
    double  getTrace();
    int     getRank();
    map<string, Matrix*> matMap;
};

#endif
