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
    cout << "메뉴" << endl;
    cout << "1. 구성원 추가" << endl
         << "2. 구성원 탐색" << endl
         << "3. 구성원 수정" << endl
         << "4. 전체 구성도 출력" << endl
         << "5. 촌수 계산" << endl
         << "6. 파일 저장" << endl
         << "7. 프로그램 종료" << endl
         << ">> ";
}

void FamilyTreeManager::addPerson()
{
    cout << "구성원을 추가합니다." << endl;
    if (t->getLastGene() < 1)
    {
        string name, born, passedAway;
        cout << "1대손을 먼저 추가합니다." << endl;
        cout << " 이름: "; cin >> name;
        cout << " 생년월일(yyyy-mm-dd): "; cin >> born;
        cout << " 기일(없으면 0000-00-00): "; cin >> passedAway;

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
        cout << "추가할 구성원의 부모 이름을 입력해 주세요." << endl;
        cout << ">> "; cin >> parentName;
        cout << "세대 수를 알고 있습니까?(Y: 숫자 입력, N:0 입력) "; cin >> g;

        if (g == 0) parent = t->search(parentName);
        else if (g > 0) parent = t->search(g, parentName);
        else { cout << "잘못된 입력입니다." << endl; return; }
        if (parent == NULL) { cout << parentName << "이 존재하지 않습니다." << endl; return; }

        string name, born, passedAway;
        cout << parentName << "의 자식을 추가합니다." << endl;
        cout << " 이름: "; cin >> name;
        cout << " 생년월일(yyyy-mm-dd): "; cin >> born;
        cout << " 기일(없으면 0000-00-00): "; cin >> passedAway;

        Person* newPerson = new Person(name, born, passedAway);
        parent->addChild(newPerson);
        t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        t->increaseLastGene();
    }
}

void FamilyTreeManager::find(){
	string name;
	Person *p;
	
	cout<<"검색할 구성원을 입력하세요\n>>";
	cin>>name;

	p = t->search(name);
	if( p ){
		cout<<p->getBorn()<<endl;
	} else {
		cout<<"해당 인물을 찾을 수 없습니다."<<endl;
	}

}


void FamilyTreeManager::show(){
	int i;
	Generation *g;

	for(i = 1; i < t->getLastGene(); i++){
		g = t->get(i);
		
	}
}