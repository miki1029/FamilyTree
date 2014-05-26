#include <iostream>
#include "FamilyTreeManager.h"
#define EXIT_CODE 7
using namespace std;

int main(int argc, char** argv)
{
    FamilyTreeManager manager;
    int menu = 0;
    string sMenu;

    manager.load();

    while (true)
    {
        manager.printMenu();
        cin >> sMenu;
        cout << endl;

        if (sMenu.compare("1") == 0){
            manager.addPerson();
        }
        else if (sMenu.compare("2") == 0){
            manager.find();
        }
        else if (sMenu.compare("3") == 0) {
            manager.modifyPerson();
        }
        else if (sMenu.compare("4") == 0) {
            manager.show();
        }
        else if (sMenu.compare("5") == 0) {
            manager.findPath();
        }
        else if (sMenu.compare("6") == 0) {
            manager.save();
        }
        else if (sMenu.compare("7") == 0) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << sMenu << " : 해당 입력은 올바르지 않은 입력입니다." << endl;
        }
    }

    return 0;
}