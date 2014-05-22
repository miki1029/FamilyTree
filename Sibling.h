#pragma once
#include "Person.h"
class Sibling
{
private:
    int _gene;
    Person* _parent;
	Person* _firstSibling;
    int _numOfSibling;

public:
    Sibling(int g, Person* p);
    ~Sibling(void);

    inline Person* parent() { return _parent;  }
    inline Person* firstSibling(){ return _firstSibling; };
	Person* siblingOfN(int n);
    void addSibling(Person* s);
	int count();
    inline int getGene() { return _gene; }
	
};

