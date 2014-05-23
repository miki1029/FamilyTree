#include <iostream>
#include "Sibling.h"
#include "Person.h"

Sibling::Sibling(int g, Person* p)
{
    _gene = g;
    _parent = p;
    _firstSibling = NULL;
    _count = 0;
}

Sibling::~Sibling(void)
{
    if (_count > 0)
    {
        Person* delNode = _firstSibling;
        while (delNode != delNode->nextSibling())
        {
            Person* nextNode = delNode->nextSibling();
            delete delNode;
            delNode = nextNode;
        }
        delete delNode;
    }
}

Person *Sibling::parent(){ return _parent; }
Person *Sibling::firstSibling(){ return _firstSibling;  }

Person* Sibling::siblingOfN(int n)
{
    if (n > _count)
    {
        cout << n << "번째 형제가 존재하지 않습니다." << endl;
        return NULL;
    }
    Person* nthSibling = _firstSibling;
    for (int i = 1; i < n; i++)
    {
        nthSibling = nthSibling->nextSibling();
    }
	return nthSibling;
}

void Sibling::addSibling(Person* s)
{
    if (_count == 0)
    {
        _firstSibling = s;
    }
    else
    {
        siblingOfN(_count)->addSibling(s);
    }
    s->setSibling(this);
    _count++;
}

void Sibling::traverse()
{
    if (_parent != NULL && _count > 0) 
        cout << "<" << _parent->getName() << "의 자식>" << endl;
    // Person 반복 호출
    for (int i = 1; i <= _count; i++)
    {
        Person* p = siblingOfN(i);
        cout << p->getName() << "/" << p->getBorn() << "/" << p->getPassedAway() << " ";
    }
    cout << endl;
}