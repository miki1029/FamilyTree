#pragma once
#include <string>
class Sibling;
using namespace std;

class Person
{
private:
	string _name
		, _born
		, _passedAway;
    // _children: �ڽĵ��� Sibling ���, _siblings: ������ Sibling ���
	Sibling *_children, *_siblings;
    // _nextSibling: ���� ���
	Person *_nextSibling;
public:
	Person(void);
	~Person(void);

	void addChild(Person* p);
	void addSibling(Person *p);

	/*
	void put(Sibling* cr);
	Sibling *get(string name);*/

	inline Person *nextSibling(){return _nextSibling;}
	inline Sibling* getChildren(){return _children;}
	inline void setName(string name){ _name = name; }
	inline string getName(){return _name; }
	inline void setBorn(string date){ _born = date; }
	inline string getBorn(string date){ return _born; }
	inline void setPassedAway(string date){ _passedAway = date; }
	inline string getPassedAway(){ return _passedAway; }

};

