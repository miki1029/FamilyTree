#pragma once
#include "Table.h"

class FamilyTreeManager
{
private :
	Table *t;

public:
    FamilyTreeManager();
    ~FamilyTreeManager();

    void printMenu();
    
    void addPerson();       // 1
    void find();            // 2
    void modifyPerson();    // 3
    void show();            // 4
    void findPath();        // 5
    void save();            // 6
};