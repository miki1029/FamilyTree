#include <iostream>
using namespace std;
//test
//test2
class Node {
private:
    Node* next;
public:
    bool hasNext();
    Node* next();
};

class DummyNode : public Node {
private:
    int key; // 세대의 수
    Node* parent;
public:
    int getKey();
    void setKey(int k);
    Node* getParent();
    void setParent(Node* p);
};

class PersonNode : public Node {
private:
    DummyNode* firstNode;
    DummyNode* childNode;
    string name;
    string born;
    string passedAway;
public:
    string getName();
    void setName(string n);
    string getBorn();
    void setBorn(string n);
    string getPassedAway();
};

class Slot {
private:
    DummyNode* dummyNode;
    Slot* next;
public:
    bool hasNext();
    Slot* next();
};

class Table {
private:
    Slot** table;
    int size;
public:
    Slot* get(int k);
    void set(Slot* v);
};