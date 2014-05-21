#pragma once
#include <string>
#include "Children.h"
using namespace std;

class Person
{
private:
	string _name
		, _born
		, _passedAway;
public:
	Person(void);
	~Person(void);

	Children* getChildren();
	void addChild(Person* p);

	inline void getName(string name){ _name = name };
	inline string setName(){return _name; };
	inline void setBorn(string date){ _born = date; }
	inline string getBorn(string date){ return _born; }
	inline void setPassedAway(string date){ _passedAway = date; }
	inline string getPassedAway(){ return _passedAway; }
};

