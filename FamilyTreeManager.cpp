#include <iostream>
#include <fstream>
#include <Windows.h>
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
    //delete t; // �� ������ ������ �𸣰���
}

void FamilyTreeManager::printMenu()
{
    fflush(stdin);
    getchar();
    system("cls");
    cout << "========================================" << endl
         << "    1. ������ �߰�" << endl
         << "    2. ������ Ž��" << endl
         << "    3. ������ ����" << endl
         << "    4. ��ü ������ ���" << endl
         << "    5. �̼� ���" << endl
         << "    6. ���� ����" << endl
         << "    7. ���α׷� ����" << endl
         << "========================================" << endl
         << "�޴� ���� >> ";
}

void FamilyTreeManager::addPerson()
{
    cout << "�������� �߰��մϴ�." << endl;
    if (t->getLastGene() < 1)
    {
        // rootSibling �ʱ�ȭ
        Sibling* rootSibling = new Sibling(1, NULL);
        t->get(1)->put(rootSibling);

        // ���� �Է�
        string familyName, name, born, passedAway;
        cout << "������ ���� �߰��մϴ�." << endl;
        cout << "��¥�� yyyy-mm-dd ��������, ������ ������ -�� �Է��մϴ�." << endl;
        cout << " ����: "; cin >> familyName;
        cout << " �̸�: "; cin >> name;
        cout << " �������(yyyy-mm-dd): "; cin >> born;
        cout << " ����(������ 0000-00-00): "; cin >> passedAway;

        // ���� ����
        t->setFamilyName(familyName);

        // rootSibling�� ������ �߰�
        Person* newPerson = new Person(name, born, passedAway);
        rootSibling->addSibling(newPerson);
        t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        t->increaseLastGene();
    }
    else
    {
        Person* parent;

        cout << t->getFamilyName() << " ������ �������� �߰��մϴ�." << endl;
        cout << "�߰��� �������� �θ� �̸��� �Է��� �ּ���." << endl;
        parent = _findPerson();
        if (parent == NULL) {
            return;
        }
        cout << endl;

        // ���� �Է�
        string name, born, passedAway;
        cout << parent->getName() << "�� �ڽ��� �߰��մϴ�." << endl;
        cout << "��¥�� yyyy-mm-dd ��������, ������ ������ -�� �Է��մϴ�." << endl;
        cout << " �̸�: "; cin >> name;
        cout << " �������: "; cin >> born;
        cout << " ����: "; cin >> passedAway;

        // parent�� �ڽ����� �߰�
        Person* newPerson = new Person(name, born, passedAway);
        parent->addChild(newPerson);
        int putResult = t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        if(putResult) t->increaseLastGene();
    }
    cout << "�������� �߰��Ͽ����ϴ�." << endl;
}

Person* FamilyTreeManager::_findPerson()
{
    string findName;
    Person *p;
    int g;

    cout << ">> "; cin >> findName;
    cout << endl;

    cout << "���� ���� �˰� �ֽ��ϱ�?(Y: ���� �Է�, N:0 �Է�) "; cin >> g;
    cout << endl;

    if (g == 0) p = t->search(findName);
    else if (g > 0) p = t->search(g, findName);
    else { cout << "�߸��� �Է��Դϴ�." << endl; return NULL; }
    if (p == NULL) { cout << findName << "�� �������� �ʽ��ϴ�." << endl; return NULL; }

    if (p) {
        int arrSize = 10;
        int numOfArr = 0;
        Person** arr = new Person*[arrSize];

        char ch;
        _printPerson(p);
        while (true)
        {
            cout << endl;
            cout << "ã���� �ι��� �½��ϱ�?(Y/n) "; cin >> ch;
            if (ch != 'n') return p;
            cout << "���� ���������� �� �˻��Ͻðڽ��ϱ�?(Y/n) "; cin >> ch;
            cout << endl;
            if (ch != 'n') {
                arr[numOfArr++] = p;

                p = t->search(arr, numOfArr, findName);
                if (p == NULL)
                {
                    cout << "���������� �����ϴ�." << endl;
                    return NULL;
                }
                _printPerson(p);
            }
            else break;
        }
        return p;
    }
    else {
        cout << "�ش� �ι��� ã�� �� �����ϴ�." << endl;
        return NULL;
    }
}

void FamilyTreeManager::_printPerson(Person* p)
{
    cout << p->getName() << "�� ����" << endl
        << "����: " << p->getSibling()->getGene() << endl
        << "�̸�: " << p->getName() << endl
        << "�������: " << p->getBorn() << endl
        << "����: " << p->getPassedAway() << endl;
}

void FamilyTreeManager::find()
{
    cout << "�˻��� �������� �̸��� �Է��� �ּ���." << endl;
    Person *p = _findPerson();

    while (p != NULL) {
        fflush(stdin);
        getchar();
        int menu = 0;
        cout << "----------------------------------------" << endl
            << p->getName() << "�� ���� ���踦 Ž���մϴ�." << endl
            << "1. �θ� Ž��" << endl
            << "2. ù° ���� Ž��" << endl
            << "3. ���� Ž��" << endl
            << "4. ù° �ڽ� Ž��" << endl
            << "5. Ž�� ����" << endl
            << "----------------------------------------" << endl
            << "�޴� ���� >> "; cin >> menu;
        cout << endl;
        switch (menu) {
        case 1:
            if (p->getSibling()->parent() == NULL) {
                cout << "������ �θ��� ������ �����ϴ�." << endl;
            }
            else {
                cout << "�θ� ";
                p = p->getSibling()->parent();
                _printPerson(p);
            }
            break;
        case 2:
            if (p == p->getSibling()->firstSibling()) {
                cout << p->getName() << "��(��) �̹� ù°�Դϴ�." << endl;
            }
            else {
                cout << "ù° ���� ";
                p = p->getSibling()->firstSibling();
                _printPerson(p);
            }
            break;
        case 3:
            if (p == p->nextSibling()) {
                cout << p->getName() << "��(��) �̹� �����Դϴ�." << endl;
            }
            else {
                cout << "���� ";
                p = p->nextSibling();
                _printPerson(p);
            }
            break;
        case 4:
            if (p->getChildren()->firstSibling() == NULL) {
                cout << p->getName() << "��(��) �ڽ��� �����ϴ�." << endl;
            }
            else {
                cout << "ù° �ڽ� ";
                p = p->getChildren()->firstSibling();
                _printPerson(p);
            }
            break;
        case 5:
            cout << "Ž���� �����մϴ�." << endl;
            return;
        }
    }
}

void FamilyTreeManager::modifyPerson()
{
    cout << "������ �������� �̸��� �Է��� �ּ���." << endl;
    Person *p = _findPerson();
    cout << endl;
    if (p != NULL)
    {
        string name, born, passedAway;
        cout << p->getName() << "�� ������ �����մϴ�." << endl;

        cout << "�̸�: "; cin >> name;
        cout << "�������: "; cin >> born;
        cout << "����: "; cin >> passedAway;

        p->setName(name);
		p->setBorn(born);
		p->setPassedAway(passedAway);
        cout << "�����Ǿ����ϴ�." << endl;
	} else {
        cout << "�ش� �ι��� ã�� �� �����ϴ�." << endl;
	}
}

void FamilyTreeManager::show(){
    cout << t->getFamilyName() << " ���� ����" << endl << endl;
    t->traverse();
}

void FamilyTreeManager::findPath(){
	Person **pFrom, **pTarget;
    Person *from = NULL, *target = NULL, *oFrom = NULL, *oTarget = NULL;
	Sibling *fromSb, *targetSb;
	int fLevel=0, tLevel=0;
	int pFromCnt =0, pTargetCnt=0; 

	pFrom = new Person*[t->getLastGene()];
	pTarget = new Person*[t->getLastGene()];

	cout<<"�̼���� ���� ����� �̸��� �Է��� �ּ���." << endl;
    from = _findPerson();
    if (from == NULL) return;
    cout << endl;

	cout<<"�̼��� ����� ��� �̸��� �Է��� �ּ���." << endl;
    target = _findPerson();
    if (target == NULL) return;
    cout << endl;

	cout<<"�˻��� �����մϴ�..."<<endl;
    cout << endl;
	
	//1. ��ǥ ����
    fromSb = from->getSibling();
    targetSb = target->getSibling();

	oFrom = from;
	oTarget = target;
	
	//2. ����Ȯ��
	for(int i = 1; i <= t->getLastGene() && (!fromSb && !targetSb); i++){
		if(fromSb == NULL){
			fromSb = t->get(i)->getSiblingByParentName(from->getName());
		}	
		if(targetSb == NULL){
			targetSb= t->get(i)->getSiblingByParentName(target->getName());
		}
	}

	if(fromSb)	fLevel = fromSb->getGene();
	if(targetSb) tLevel = targetSb->getGene();

	//3. ���� Ȯ���ϸ鼭 ���븦 �ö�.
	while( from != target){
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
	//cout<<oFrom->getName()<<endl;
    for (int i = 0; i < pFromCnt; i++) {
        _printPerson(pFrom[i]);
        cout << endl;
        //cout<<pFrom[i]->getName()<<endl;
    }
	//related parent

	//cout<<from->getName()<<endl;
    _printPerson(from);
    cout << endl;
	//if(	fromSb->parent() != oFrom ) cout<<fromSb->parent()->getName()<<endl;
	//from after related parent to target
	//for(int i = pTargetCnt-1; i >= 0; i--) cout<<pTarget[i]->getName()<<endl; 
    for (int i = pTargetCnt - 1; i >= 0; i--) {
        _printPerson(pTarget[i]);
        cout << endl;
    }
	//cout<<oTarget->getName()<<endl;
	cout<<"�� �̼� : "<<pFromCnt+pTargetCnt+(target != from ? 2 : 0)<<endl;
}

void FamilyTreeManager::save()
{
	ofstream fout;
	string pname;
	Person *p;
	Generation *g;
	Sibling **s;
	int i, j;

	fout.open("data.ftl");

	if(fout.is_open()){
		g = t->get(1);
		s = g->getSiblingArr();

		for(i = 0; i < g->getNumOfSibling(); i++){
			p = s[i]->firstSibling();
			for(int j = 0; j < s[i]->count(); j++){
				fout<<t->getFamilyName()<<" "<<p->getName()<<" "<<p->getBorn()<<" "<<p->getPassedAway();
				p = p->nextSibling();
			} 
		}

		for(i = 2; i <= t->getLastGene(); i++){
			
			g = t->get(i);
			s = g->getSiblingArr();
			
			for(j = 0; j < g->getNumOfSibling(); j++){
				pname = s[j]->parent()->getName();
				p = s[j]->firstSibling();
				for(int k = 0; k < s[j]->count(); k++){
					fout<<endl<<pname<<" "<<p->getName()<<" "<<p->getBorn()<<" "<<p->getPassedAway();
					p = p->nextSibling();
				} 
			}
		}
		fout.close();
        cout << "Save ����!" << endl;
	}
}

void FamilyTreeManager::load(){
	ifstream fin;
    string familyName, pname, name, born, passedAway;
	fin.open("data.ftl");

	if(fin.is_open()){
        cout << "����� ������ �θ��ðڽ��ϱ�?(Y/n) ";
        char op;
        cin >> op;
        cout << endl;
        if (op != 'n')
        {
		    while( !fin.eof() ){

			    if (t->getLastGene() < 1)
			    {
				    // rootSibling �ʱ�ȭ
				    Sibling* rootSibling = new Sibling(1, NULL);
				    t->get(1)->put(rootSibling);

                    fin >> familyName >> name >> born >> passedAway;

                    // ���� ����
                    t->setFamilyName(familyName);

				    // rootSibling�� ������ �߰�
				    Person* newPerson = new Person(name, born, passedAway);
				    rootSibling->addSibling(newPerson);
				    t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
				    t->increaseLastGene();
				    cout<<familyName<<" "<<name<<" "<<born<<" "<<passedAway<<" Loaded"<<endl;
			    }
			    else
			    {
				
				    Person* parent;
				    fin >> pname >> name >> born >> passedAway;
				
				    parent = t->search(pname);

				    if (parent == NULL) { cout << pname << "�� �������� �ʽ��ϴ�." << endl; continue;/* return; */}

				    // parent�� �ڽ����� �߰�
				    Person* newPerson = new Person(name, born, passedAway);
				    parent->addChild(newPerson);
				    int putResult = t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
				    if(putResult) t->increaseLastGene();
				
				    cout<< pname << " " <<name<<" "<<born<<" "<<passedAway<<" Loaded"<<endl;
			    }
            }
            cout << endl << "Load ����!" << endl;
        }
        else
        {
            cout << "���� �����մϴ�." << endl
                << "����� ���� �����Ͱ� �սǵ˴ϴ�." << endl
                << "�ƹ� Ű�� ���� �ּ���." << endl;
        }
		fin.close();
	}
    else
    {
        cout << "data.ftl ������ �����ϴ�." << endl
            << "���� �����Ϸ��� �ƹ� Ű�� ���� �ּ���." << endl;
    }
}