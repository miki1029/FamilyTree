#pragma once
#include <string>
#include <set>
using namespace std;

class Person;
class Sibling;

class Generation
{
private:
	int _hashSize;
    int _numOfSibling;
	struct _HashTable {
		Sibling *siblings;
		_HashTable *nextChain;
	};
    _HashTable *_ht, *_tail;

    set<int> _keySet;

	int _hashing(const string);
public:
	Generation(int hashSize);
	~Generation(void);

    int put(Sibling *s);

    Sibling *getSiblingByParentName(string name);
    Sibling **getSiblingByParentNameArr(string name);
    int getNumOfSameParentName(string name);

    inline _HashTable *getHashTable() { return _ht; }
    inline set<int> keySet() { return _keySet; };

    void traverse();
    Sibling** getSiblingArr();
    inline int getNumOfSibling() { return _numOfSibling; }
};