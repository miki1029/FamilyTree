#include "Sibling.h"

Sibling::Sibling(int g, Person* p)
{
    _gene = g;
    _parent = p;
    _numOfSibling = 0;
}


Sibling::~Sibling(void)
{
}

Person* Sibling::siblingOfN(int n)
{
    
	return NULL;
}

void Sibling::addSibling(Person* s)
{
    if (_numOfSibling == 0)
    {
        _firstSibling = s;
        _numOfSibling++;
    }
}

int Sibling::count()
{

}

int Sibling::getGene()
{

}