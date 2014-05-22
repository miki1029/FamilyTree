#include "Table.h"

Table::Table(void)
{
    // 0 �ε����� ������� ����(���� ���� �ε����� �����ϰ� �ϱ� ����)
    _size = 50;
    _slots = new Generation*[_size]();
    _lastGene = 0;
}


Table::~Table(void)
{
}


void Table::addGene()
{
   // _slots[++_lastGene]->
}

Person *Table::search(int gene, string name){
	Sibling *s = _slots[gene+1]->get(name);

	if(s)	return s->parent();

	return NULL;
}

Person *Table::search(string name){
	Sibling *s;
	for(int i = _lastGene; i > 0; i--){
		s = _slots[i]->get(name);

		if(s) return s->parent();
	}
	return NULL;
}