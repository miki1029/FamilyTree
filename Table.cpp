#include <iostream>
#include <cmath>
#include "Generation.h"
#include "Sibling.h"
#include "Table.h"

Table::Table(int size)
{
    // 0 �ε����� ������� ����(���� ���� �ε����� �����ϰ� �ϱ� ����)
    _size = size;
    _table = new Generation*[_size]();
    for (int i = 0; i < _size; i++)
    {
        double genSize = i * log(i);
        if (genSize < 10 || i == 0) genSize = 10.0;
        _table[i] = new Generation((int)genSize);
    }
    _lastGene = 0;
}

Table::~Table(void)
{
    for (int i = 0; i < _size; i++)
    {
        delete _table[i];
    }
    delete[] _table;
}

void Table::expandTable(int num=20)
{
    Generation** newTable = new Generation*[_size + num]();
    // ���� Generation ������ ����
    for (int i = 1; i <= _size; i++)
    {
        newTable[i] = _table[i];
    }
    // ���ο� Generation �Ҵ�
    for (int i = _size; i < _size + num; i++)
    {
        double genSize = i * log(i);
        if (genSize < 10) genSize = 10.0;
        newTable[i] = new Generation((int)genSize);
    }
    _table = newTable;
    _size += num;
}

void Table::increaseLastGene()
{
    _lastGene++;
    if (_lastGene >= _size - 2)
    { // size=51�϶� �ε����� 50���� �ְ� 49������� ����(Sibling���� ���� ��ǻ� 50���� ��) Ȯ��
        expandTable();
    }
}

Person *Table::search(int gene, string name){
    Sibling *s = _table[gene + 1]->getSiblingByParentName(name);

	if(s)	return s->parent();

	return NULL;
}

Person *Table::search(string name){
	Sibling *s;
	for(int i = _lastGene+1; i > 0; i--){
        s = _table[i]->getSiblingByParentName(name);

		if(s) return s->parent();
	}
	return NULL;
}

Person *Table::search(Person** arr, int n, string name)
{
    Sibling *s;
    bool find = false;
    for (int i = _lastGene + 1; i > 0; i--){
        for (int j = 0; j < _table[i]->getNumOfSameParentName(name); j++) {
            s = _table[i]->getSiblingByParentNameArr(name)[j];
            if (s) {
                for (int i = 0; i < n; i++) {
                    if (s->parent() == arr[i]) find = true;
                }
                if (!find) {
                    return s->parent();
                }
            }
        }
    }
    return NULL;
}

void Table::traverse()
{
    for (int i = 1; i <= _lastGene; i++)
    {
        Generation* g = _table[i];
        cout << "[" << i << "��° ����]" << endl;
        g->traverse();
        cout << endl;
    }
}