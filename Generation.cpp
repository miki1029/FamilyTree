#include "Person.h"
#include "Sibling.h"
#include "Generation.h"

Generation::Generation(int hashSize=1)
{
	_hashSize = hashSize;
	_ht = new _HashTable[_hashSize];
	_tail = new _HashTable;
	_tail->nextChain = _tail; 
	for(int i = 0; i < _hashSize; i++)	_ht[i].nextChain = _tail;

	_currIdx = 0; _currHt = NULL;
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
	int h = 0, i=0;
	while(i <= s.length())	h = h<<1^s[i++];
	return abs(h) % _hashSize;
}

void Generation::put(Sibling* cr){

	bool searchFlag = false;
	_HashTable *itr = NULL;
    int key;
    if (cr->parent() == NULL) key = 0;
    else key = _hashing(cr->parent()->getName());

		
	if ( _ht[key].nextChain == _tail){	// 해당 해시테이블에 내용이 없을 경우
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
}
Sibling *Generation::getSiblingByParentName(string name){
	int key = _hashing(name);
	_HashTable *itr = NULL;

	for(itr = _ht[key].nextChain;
		itr != _tail
			&& itr->siblings->parent()->getName().compare(name) ;
		itr = itr->nextChain);

	if(itr == _tail) return NULL;

	return itr->siblings;
	
}

Sibling *Generation::siblingOfN(int n){
	_HashTable *itr ;
	int ti, i = 1;

	for(ti = 0; ti < _hashSize; ti++){
		for(itr = _ht[ti].nextChain; itr != itr; itr=itr->nextChain){
			if(i == n) return itr->siblings;
			i++;
		}
	}
	return NULL;
}

void Generation::moveToBegin(){
	_currHt = NULL;
}
Sibling *Generation::next(){
	if(_currHt == NULL){
		_currHt = _ht[0].nextChain;

		if( _currHt != _currHt->nextChain)	return _currHt->siblings;
	} 

	while( _currIdx < _hashSize 
		&&  _currHt != _currHt->nextChain ) {
			_currHt = _currHt->nextChain;
			if( _currHt != _currHt->nextChain ) return _currHt->siblings;
			else _currIdx++;
	}

	return NULL;
}