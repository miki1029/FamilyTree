#include <iostream>
#include "FamilyTreeManager.h"
#include "Person.h"
#include "Sibling.h"
#include "Generation.h"
using namespace std;

FamilyTreeManager::FamilyTreeManager()
{
    t = new Table(51);
}

FamilyTreeManager::~FamilyTreeManager()
{
    //delete t;
}

void FamilyTreeManager::printMenu()
{
    cout << "�޴�" << endl;
    cout << "1. ������ �߰�" << endl
         << "2. ������ Ž��" << endl
         << "3. ������ ����" << endl
         << "4. ��ü ������ ���" << endl
         << "5. �̼� ���" << endl
         << "6. ���� ����" << endl
         << "7. ���α׷� ����" << endl
         << ">> ";
}

void FamilyTreeManager::addPerson()
{
    cout << "�������� �߰��մϴ�." << endl;
    if (t->getLastGene() < 1)
    {
        string name, born, passedAway;
        cout << "1����� ���� �߰��մϴ�." << endl;
        cout << " �̸�: "; cin >> name;
        cout << " �������(yyyy-mm-dd): "; cin >> born;
        cout << " ����(������ 0000-00-00): "; cin >> passedAway;

        Sibling* rootSibling = new Sibling(1, NULL);
        Person* newPerson = new Person(name, born, passedAway);
        t->get(1)->put(rootSibling);
        rootSibling->addSibling(newPerson);
        t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        t->increaseLastGene();
    }
    else
    {
        string parentName;
        Person* parent;
        int g;
        Person** arr = new Person*[10];
        cout << "�߰��� �������� �θ� �̸��� �Է��� �ּ���." << endl;
        cout << ">> "; cin >> parentName;
        cout << "���� ���� �˰� �ֽ��ϱ�?(Y: ���� �Է�, N:0 �Է�) "; cin >> g;

        if (g == 0) parent = t->search(parentName);
        else if (g > 0) parent = t->search(g, parentName);
        else { cout << "�߸��� �Է��Դϴ�." << endl; return; }
        if (parent == NULL) { cout << parentName << "�� �������� �ʽ��ϴ�." << endl; return; }

        string name, born, passedAway;
        cout << parentName << "�� �ڽ��� �߰��մϴ�." << endl;
        cout << " �̸�: "; cin >> name;
        cout << " �������(yyyy-mm-dd): "; cin >> born;
        cout << " ����(������ 0000-00-00): "; cin >> passedAway;

        Person* newPerson = new Person(name, born, passedAway);
        parent->addChild(newPerson);
        t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        t->increaseLastGene();
    }
}

void FamilyTreeManager::find(){
	string name;
	Person *p;
	
	cout<<"�˻��� �������� �Է��ϼ���\n>>";
	cin>>name;

	p = t->search(name);
	if( p ){
		cout<<p->getBorn()<<endl;
	} else {
		cout<<"�ش� �ι��� ã�� �� �����ϴ�."<<endl;
	}

}


void FamilyTreeManager::show(){
	int i;
	Generation *g;

	for(i = 1; i < t->getLastGene(); i++){
		g = t->get(i);
		
	}
}