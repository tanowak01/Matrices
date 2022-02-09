#include "Menu.h"
using namespace std;
int main(){
    Menu menu = Menu();
    menu.createNewMatrix();
}
Menu::Menu(){}
void Menu::createNewMatrix(){
    cout << "What is the name of this matrix?" << endl;
    string name;
    cin >> name;
    cout << matMap[name];
    Matrix* m1 = new Matrix(0,0);
    cin >> *m1;
    
}
