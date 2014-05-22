#pragma once
#include <string>
using namespace std;

class Person;
class Sibling;

class Generation
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
	Generation(int hashSize);
	~Generation(void);

	void put(Sibling *s);
	Sibling *get(string name);


};