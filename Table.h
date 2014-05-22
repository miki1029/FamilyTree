#pragma once
#include "Slot.h"

class Table
{
private:
	Slot* _slots;
    int _size;
    int _lastGene;

public:
	Table(void);
	~Table(void);

	void addGene(Slot);
    inline int getLastGene() { return _lastGene; }
};