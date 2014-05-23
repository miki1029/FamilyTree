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
    void addPerson();
    void modifyPerson();
    void find();
    void show();
    void save();
};