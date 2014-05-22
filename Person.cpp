#include "Person.h"


Person::Person()
{
	_children = new Sibling();
	_children->setParent(_siblings->getGene()+1, this);
}


Person::~Person(void)
{
	delete _children;
}

void Person::addChild(Person* p){
	_children->addSibling(p);
}

