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
    // _children: 자식들의 Sibling 노드, _siblings: 현재의 Sibling 노드
	Sibling *_children, *_siblings;
    // _nextSibling: 동생 노드
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

