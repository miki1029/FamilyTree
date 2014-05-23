#include <iostream>
#include "FamilyTreeManager.h"
#define EXIT_CODE 7
using namespace std;

int main(int argc, char** argv)
{
    FamilyTreeManager manager;
    int menu = 0;

	manager.load();

    while (menu != EXIT_CODE)
    {
        manager.printMenu();
        cin >> menu;
        switch (menu)
        {
        case 1:
            manager.addPerson();
            break;
        case 2:
            manager.find();
            break;
        case 3:
            manager.modifyPerson();
            break;
        case 4:
            manager.show();
            break;
        case 5:
            manager.findPath();
            break;
        case 6:
            manager.save();
            break;
        }
    }

	return 0;
}