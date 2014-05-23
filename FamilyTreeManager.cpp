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
		cout<<p->getName<<endl
			<<p->getBorn()<<endl
			<<p->getPassedAway()<<endl;
	} else {
		cout<<"해당 인물을 찾을 수 없습니다."<<endl;
	}

}


void FamilyTreeManager::show(){
	int i, j;
	Generation *g;
	Sibling *s;
	Person *p;

	for(i = 1; i <= t->getLastGene(); i++){
		g = t->get(i); //i번째 세대 정보
		cout<<"["<<i<<"번째 세대]"<<endl;
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

	cout<<"촌수계산 시작 대상의 이름을 입력하세요. : ";
	cin>>fromName;
	cout<<"촌수를 계산할 대상 이름을 입력하세요 : ";
	cin>>targetName;

	cout<<"검색을 시작합니다..."<<endl;
	
	//1. 목표 선정
	from = t->search(fromName);
	target = t->search(targetName);
	
	
	//2. 레벨확인
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

	//3. 세대 확인하면서 세대를 올라감.
	while( fromSb != targetSb){
		if( fLevel > tLevel){	//출발점의 세대가 아래일 경우
			fLevel--;
			pFrom[pFromCnt++] = from;
			from = fromSb->parent();
			fromSb = from->getSibling();
		} else if(fLevel < tLevel){//목표지점 세대가 아래일 경우
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
	cout<<"총 촌수 : "<<pFromCnt+pTargetCnt+(target != from ? 2 : 0)<<endl;
}