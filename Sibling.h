#pragma once
class Person;

class Sibling
{
private:
    int _gene;
    Person* _parent;
    Person* _firstSibling;
    int _count;

public:
    Sibling(int g, Person* p);
    ~Sibling(void);

    Person* parent();
    Person* firstSibling();
    Person* siblingOfN(int n);
    void addSibling(Person* s);
    inline int count() { return _count; }
    inline int getGene() { return _gene; }

    void traverse();
};

