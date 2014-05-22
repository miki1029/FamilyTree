#pragma once
#include "Person.h"
class Sibling
{
private:
    int _gene;
    Person* _parent;
	Person* _firstSibling;
    int _count;

public:
    Sibling(int g, Person* p);
    ~Sibling(void);

    inline Person* parent() { return _parent;  }
    inline Person* firstSibling() { return _firstSibling; };
	Person* siblingOfN(int n);
    void addSibling(Person* s);
    inline int count() { return _count; }
    inline int getGene() { return _gene; }
};

