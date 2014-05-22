#include "Table.h"

Table::Table(int size=50)
{
    // 0 �ε����� ������� ����(���� ���� �ε����� �����ϰ� �ϱ� ����)
    _size = size;
    _table = new Generation*[_size]();
    _lastGene = 0;
}


Table::~Table(void)
{
    delete[] _table;
}

void Table::expandTable(int num=20)
{
    _size += num;
    Generation** newTable = new Generation*[_size]();
    for (int i = 1; i <= _lastGene; i++)
    {
        newTable[i] = _table[i];
    }
    _table = newTable;
}

void Table::put(Generation *g)
{
    if (_lastGene >= _size - 1) // 50�������̸� 49�ε������� �����Ƿ�
    {
        expandTable();
    }
    _table[++_lastGene] = g;
}

Person *Table::search(int gene, string name){
    Sibling *s = _table[gene + 1]->get(name);

	if(s)	return s->parent();

	return NULL;
}

Person *Table::search(string name){
	Sibling *s;
	for(int i = _lastGene; i > 0; i--){
        s = _table[i]->get(name);

		if(s) return s->parent();
	}
	return NULL;
}