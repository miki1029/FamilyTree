#pragma once
#include "Person.h"
class Children
{
private:
	Person* _firstChild;

public:
	Children(void);
	~Children(void);

	void setParent(Person* p);
	inline Person* firstSibiling(){ return _firstChild; };
	Person* sibilingofN(int n);
	int count();
	int getGene();
	
};

