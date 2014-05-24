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
    string _familyName; // 성씨

    void expandTable(int num);

public:
	Table(int size);
	~Table(void);

    void put(Generation *g);
    inline Generation *get(int i) { return _table[i]; }
    
    inline int getLastGene() { return _lastGene; }
    void increaseLastGene();
    inline void setFamilyName(string n) { _familyName = n; }
    inline string getFamilyName() { return _familyName; }

    // 세대에서 검색
	Person *search(int gene, string name);
    // 전체에서 검색
	Person *search(string name);
    // 동명이인 검색
    Person *search(Person** arr, int n, string name);
    
    void traverse();
};