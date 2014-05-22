#include "Table.h"

Table::Table(void)
{
    // 0 인덱스는 사용하지 않음(세대 수와 인덱스를 동일하게 하기 위함)
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