#pragma once
#include "Children.h"

class Slot
{
private:
	int hashing(const string);
public:
	Slot(void);
	~Slot(void);

	void addGeneChildren(Children* cr);

};