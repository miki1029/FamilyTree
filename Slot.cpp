#include "Slot.h"


Slot::Slot(int hashSize=1)
{
	_hashSize = hashSize;
	_ht = new _HashTable[_hashSize];
	_tail = new _HashTable;
	_tail->nextChain = _tail; 
	for(int i = 0; i < _hashSize; i++)	_ht[i].nextChain = _tail;
}


Slot::~Slot(void)
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

int Slot::_hashing(const string s){
	int h = 0, i=0;
	while(i <= s.length)	h = h<<1^s[i++];
	return abs(h) % _hashSize;
}

void Slot::addGeneChildren(Sibling* cr){
}