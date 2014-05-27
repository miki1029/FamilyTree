#pragma once
#include "Table.h"

class FamilyTreeManager
{
private :
	Table *t;

    Person* _findPerson();
    void _printPerson(Person* p);

	bool checkNo(string s){	return s.compare("N")  == 0 || s.compare("n") == 0 ||  s.compare("¤Ì") == 0 ;	}
	bool checkYes(string s){return s.compare("Y") == 0 || s.compare("y") == 0 || s.compare("¤Ë") == 0 ;	}

public:
	FamilyTreeManager();
    ~FamilyTreeManager();

    void printMenu();
	void load();
    
    void addPerson();       // 1
    void find();            // 2
    void modifyPerson();    // 3
    void show();            // 4
    void findPath();        // 5
    void save();            // 6
};