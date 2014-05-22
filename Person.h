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
	Sibling *_children, *_sibling;
    // _nextSibling: 동생 노드
	Person *_nextSibling;
public:
	Person(string name, string born, string passedAway);
	~Person(void);

	void addChild(Person* p);
	void addSibling(Person *p);

	inline Person *nextSibling(){return _nextSibling;}

	inline Sibling* getChildren(){return _children;}
    inline void setSibling(Sibling* sibling) { _sibling = sibling; }
    inline Sibling* getSibling(){ return _sibling; }
	inline void setName(string name){ _name = name; }
	inline string getName(){return _name; }
	inline void setBorn(string date){ _born = date; }
	inline string getBorn(){ return _born; }
	inline void setPassedAway(string date){ _passedAway = date; }
	inline string getPassedAway(){ return _passedAway; }

};

