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
		cout<<p->getName<<endl
			<<p->getBorn()<<endl
			<<p->getPassedAway()<<endl;
	} else {
		cout<<"�ش� �ι��� ã�� �� �����ϴ�."<<endl;
	}

}


void FamilyTreeManager::show(){
	int i, j;
	Generation *g;
	Sibling *s;
	Person *p;

	for(i = 1; i <= t->getLastGene(); i++){
		g = t->get(i); //i��° ���� ����
		cout<<"["<<i<<"��° ����]"<<endl;
		while( (s = g->next()) != NULL){
			p = s->firstSibling;
			while(p->nextSibling != p){
				cout<<p->getName()<<"/"<<p->getBorn()<<"/"<<p->getPassedAway()<<" ";
			}
		}
		cout<<endl
			<<"==========================================="<<endl;;
	}
}

void FamilyTreeManager::findPath(){
	string fromName, targetName;
	Person **pFrom, **pTarget;
	Person *from, *target;
	Sibling *fromSb, *targetSb;
	int fLevel=0, tLevel=0;
	int pFromCnt =0, pTargetCnt=0; 

	pFrom = new Person*[t->getLastGene()];
	pTarget = new Person*[t->getLastGene()];

	cout<<"�̼���� ���� ����� �̸��� �Է��ϼ���. : ";
	cin>>fromName;
	cout<<"�̼��� ����� ��� �̸��� �Է��ϼ��� : ";
	cin>>targetName;

	cout<<"�˻��� �����մϴ�..."<<endl;
	
	//1. ��ǥ ����
	from = t->search(fromName);
	target = t->search(targetName);
	
	
	//2. ����Ȯ��
	for(int i = 1; i <= t->getLastGene; i++){
		if(fromSb == NULL){
			fromSb = t->get(i)->getSiblingByParentName(from->getName());
			if(fromSb != NULL) fLevel = i; 
		}	
		if(targetSb == NULL){
			targetSb= t->get(i)->getSiblingByParentName(target->getName());
			if(targetSb != NULL) tLevel = i;
		}
	}

	//3. ���� Ȯ���ϸ鼭 ���븦 �ö�.
	while( fromSb != targetSb){
		if( fLevel > tLevel){	//������� ���밡 �Ʒ��� ���
			fLevel--;
			pFrom[pFromCnt++] = from;
			from = fromSb->parent();
			fromSb = from->getSibling();
		} else if(fLevel < tLevel){//��ǥ���� ���밡 �Ʒ��� ���
			tLevel--;
			pTarget[pTargetCnt++] = target;
			target = targetSb->parent();
			targetSb = target->getSibling();
		} else {
			fLevel--;
			tLevel--;

			pFrom[pFromCnt++] = from;
			from = fromSb->parent();
			fromSb = from->getSibling();

			pTarget[pTargetCnt++] = target;
			target = targetSb->parent();
			targetSb = target->getSibling();

		}
	}
	
	//from to related parent
	for(int i = 0; i < pFromCnt; i++) cout<<pFrom[i]->getName()<<endl;
	//related parent
	cout<<pTarget[pTargetCnt-1]->getSibling()->parent()<<endl;
	//from after related parent to target
	for(int i = pTargetCnt-1; i >= 0; i--) cout<<pTarget[i]->getName()<<endl; 
	cout<<"�� �̼� : "<<pFromCnt+pTargetCnt+(target != from ? 2 : 0)<<endl;
}