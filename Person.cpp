#include "Person.h"
#include "Sibling.h"


Person::Person()
{
	_children = new Sibling(_siblings->getGene()+1, this);
	_nextSibling = this;
}

Person::Person(string name, string born, string passedAway){
	_name = name;
	_born = born;
	_passedAway = passedAway;
}


Person::~Person(void)
{
	delete _children;
}

void Person::addChild(Person* p){
	_children->addSibling(p);
}

void Person::addSibling(Person* p){
	Person *itr;

	for(itr = this; itr->nextSibling() != itr; itr=itr->nextSibling());
	itr->_nextSibling = p;
}
