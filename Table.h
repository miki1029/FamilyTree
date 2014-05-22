#pragma once
#include "Generation.h"

class Table
{
private:
	Generation** _slots;
    int _size;
    int _lastGene;

public:
	Table(void);
	~Table(void);

	void addGene();
    inline int getLastGene() { return _lastGene; }
};