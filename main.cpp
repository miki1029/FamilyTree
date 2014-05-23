#include <iostream>
#include "FamilyTreeManager.h"
#define EXIT_CODE 7
using namespace std;

int main(int argc, char** argv)
{
    FamilyTreeManager manager;
    int menu = 0;

    while (menu != EXIT_CODE)
    {
        manager.printMenu();
        cin >> menu;
        switch (menu)
        {
        case 1:
            manager.addPerson();
            break;
        }
    }

	return 0;
}