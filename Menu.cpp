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
    while(matMap.find(name) != matMap.end()){
        cout << "That name is being used, choose another: " << endl;
        cin >> name;
    }
    Matrix* m1 = new Matrix(0,0);
    cout << "Enter matrix starting with \'[\', rows separated by \';\', entries separated by \',\', and ending with \']\'" << endl;
    cin >> *m1;
    if(!matMap.insert({name, m1}).second){
        cout << "Insert failed, please try again" << endl;
    }
}
