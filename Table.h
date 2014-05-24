#pragma once
#include <string>
using namespace std;
class Generation;
class Person;

class Table
{
private:
	Generation** _table;
    int _size;
    int _lastGene;
    string familyName; // ¼º¾¾

    void expandTable(int num);

public:
	Table(int size);
	~Table(void);

    void put(Generation *g);
    inline Generation *get(int i) { return _table[i]; }
    
    inline int getLastGene() { return _lastGene; }
    void increaseLastGene();
    inline void setFamilyName(string n) { familyName = n; }
    inline string getFamilyName() { return familyName; }

	Person *search(int gene, string name);
	Person *search(string name);
    
    void traverse();
};