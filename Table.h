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
    string _familyName; // ����

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

    // ���뿡�� �˻�
	Person *search(int gene, string name);
    // ��ü���� �˻�
	Person *search(string name);
    // �������� �˻�
    Person *search(Person** arr, int n, string name);
    
    void traverse();
};