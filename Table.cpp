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
    _slots[++_lastGene]->
}