#include "Person.h"
#include "Sibling.h"


Person::Person(string name, string born, string passedAway){
    _name = name;
    _born = born;
    _passedAway = passedAway;
    _nextSibling = this;
}

Person::~Person(void)
{
    delete _children;
}

void Person::addChild(Person* p){
    _children->addSibling(p);
}

void Person::addSibling(Person* p){
    _nextSibling = p;
}

void Person::setSibling(Sibling* sibling)
{
    _sibling = sibling;
    _children = new Sibling(_sibling->getGene() + 1, this);
}