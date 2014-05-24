#include "Person.h"
#include "Sibling.h"
#include "Generation.h"

Generation::Generation(int hashSize)
{
	_hashSize = hashSize;
    _numOfSibling = 0;
	_ht = new _HashTable[_hashSize];
	_tail = new _HashTable;
	_tail->nextChain = _tail; 
	for(int i = 0; i < _hashSize; i++)	_ht[i].nextChain = _tail;
}

Generation::~Generation(void)
{
	_HashTable *itr, *tmp ;

	for(int i = 0 ; i < _hashSize; i++){
		itr = _ht[i].nextChain;
		while(itr != NULL){
			tmp = itr;
			itr = itr->nextChain;
			delete tmp;
		}
	}
	delete [] _ht;
}

int Generation::_hashing(const string s){
	int h = 0;
    unsigned i = 0;
	while(i <= s.length())	h = h<<1^s[i++];
	return abs(h) % _hashSize;
}

int Generation::put(Sibling* cr){

	bool searchFlag = false;
	_HashTable *itr = NULL;
    int key;
    if (cr->parent() == NULL) key = 0;
    else key = _hashing(cr->parent()->getName());

		
	if ( _ht[key].nextChain == _tail){	// �ش� �ؽ����̺� ������ ���� ���
		_HashTable * item = new _HashTable;
		item->siblings = cr;
		item->nextChain = _ht[key].nextChain;
		_ht[key].nextChain = item;
	} else {
		for(itr = _ht[key].nextChain; itr->nextChain != _tail; itr = itr->nextChain);
		_HashTable * item = new _HashTable;
		item->siblings = cr;
		item->nextChain = itr->nextChain;
		itr->nextChain = item; 
    }
    _numOfSibling++;
    int originKeyNum = _keySet.size();
    _keySet.insert(key);
    if (originKeyNum == 0) return 1; // ���ο� ���� �߰�
    else return 0; // �Ϲ����� Sibling �߰�
}

Sibling *Generation::getSiblingByParentName(string name){
	int key = _hashing(name);
    _HashTable *itr = NULL;

    for (itr = _ht[key].nextChain; itr != _tail; itr = itr->nextChain) {
        // 1����
        if (itr->siblings->parent() == NULL) return NULL;
        // ������
        if (itr->siblings->parent()->getName().compare(name) == 0) {
            return itr->siblings;
        }
    }

    return NULL;
}

Sibling **Generation::getSiblingByParentNameArr(string name){
    int key = _hashing(name);
    _HashTable *itr = NULL;

    int numOfArr = 0;
    Sibling **arr = new Sibling*[_numOfSibling];

    for (itr = _ht[key].nextChain; itr != _tail; itr = itr->nextChain) {
        // 1����
        if (itr->siblings->parent() == NULL) return arr;
        // ������
        if (itr->siblings->parent()->getName().compare(name) == 0) {
            arr[numOfArr++] = itr->siblings;
        }
    }

    return arr;
}

int Generation::getNumOfSameParentName(string name)
{
    int key = _hashing(name);
    _HashTable *itr = NULL;

    int num = 0;

    for (itr = _ht[key].nextChain; itr != _tail; itr = itr->nextChain) {
        // 1����
        if (itr->siblings->parent() == NULL) return 0;
        // ������
        if (itr->siblings->parent()->getName().compare(name) == 0) {
            num++;
        }
    }

    return num;
}

void Generation::traverse()
{
    set<int>::iterator itr;
    // hashing�� �ݺ� ȣ��
    for (itr = _keySet.begin(); itr != _keySet.end(); itr++)
    {
        // chaining�� �ݺ� ȣ��
        for (_HashTable* curHT = _ht[*itr].nextChain;
            curHT != _tail;
            curHT = curHT->nextChain)
        {
            Sibling* curSB = curHT->siblings;
            // Person �ݺ� ȣ��
            curSB->traverse();
        }
    }
}

Sibling** Generation::getSiblingArr()
{
    int i = 0;
    Sibling** arr = new Sibling*[_numOfSibling];
    set<int>::iterator itr;
    // hashing�� �ݺ� ȣ��
    for (itr = _keySet.begin(); itr != _keySet.end(); itr++)
    {
        // chaining�� �ݺ� ȣ��
        for (_HashTable* curHT = _ht[*itr].nextChain;
            curHT != _tail;
            curHT = curHT->nextChain)
        {
            Sibling* curSB = curHT->siblings;
            // Person �ݺ� ȣ��
            arr[i++] = curSB;
        }
    }

	return arr;
}