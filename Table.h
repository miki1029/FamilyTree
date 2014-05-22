#pragma once
#include "Generation.h"

class Table
{
private:
	Generation** _table;
    int _size;
    int _lastGene;

    void expandTable(int num);

public:
	Table(int size);
	~Table(void);

    void put(Generation *g);
    inline Generation *get(int i) { return _table[i]; }
    inline int getLastGene() { return _lastGene; }

	Person *search(int gene, string name);
	Person *search(string name);
};