#pragma once
#include "Slot.h"

class Table
{
private:
	Slot* slots;

public:
	Table(void);
	~Table(void);

	void addGene();
	int getLastGene();
};

