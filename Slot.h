#pragma once
#include "Sibling.h"

class Slot
{
private:
	int _hashSize;
	struct _HashTable {
		Sibling *siblings;
		_HashTable *nextChain;
	};
	_HashTable *_ht, *_tail;

	int _hashing(const string);
public:
	Slot(int hashSize);
	~Slot(void);

	void addGeneChildren(Sibling* cr);

};