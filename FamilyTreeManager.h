#pragma once
#include "Table.h";

class FamilyTreeManager
{
private :
	Table t;
public:
    void printMenu();
    void addPerson();
    void modifyPerson();
    void find();
    void show();
    void save();
};