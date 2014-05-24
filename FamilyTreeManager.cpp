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
    //delete t; // 왜 에러가 나는지 모르겠음
}

void FamilyTreeManager::printMenu()
{
    fflush(stdin);
    getchar();
    system("cls");
    cout << "========================================" << endl
         << "    1. 구성원 추가" << endl
         << "    2. 구성원 탐색" << endl
         << "    3. 구성원 수정" << endl
         << "    4. 전체 구성도 출력" << endl
         << "    5. 촌수 계산" << endl
         << "    6. 파일 저장" << endl
         << "    7. 프로그램 종료" << endl
         << "========================================" << endl
         << "메뉴 선택 >> ";
}

void FamilyTreeManager::addPerson()
{
    cout << "구성원을 추가합니다." << endl;
    if (t->getLastGene() < 1)
    {
        // rootSibling 초기화
        Sibling* rootSibling = new Sibling(1, NULL);
        t->get(1)->put(rootSibling);

        // 정보 입력
        string familyName, name, born, passedAway;
        cout << "시조를 먼저 추가합니다." << endl;
        cout << "날짜는 yyyy-mm-dd 형식으로, 기일이 없으면 -을 입력합니다." << endl;
        cout << " 성씨: "; cin >> familyName;
        cout << " 이름: "; cin >> name;
        cout << " 생년월일(yyyy-mm-dd): "; cin >> born;
        cout << " 기일(없으면 0000-00-00): "; cin >> passedAway;

        // 성씨 설정
        t->setFamilyName(familyName);

        // rootSibling의 형제로 추가
        Person* newPerson = new Person(name, born, passedAway);
        rootSibling->addSibling(newPerson);
        t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        t->increaseLastGene();
    }
    else
    {
        Person* parent;

        cout << t->getFamilyName() << " 가문의 구성원을 추가합니다." << endl;
        cout << "추가할 구성원의 부모 이름을 입력해 주세요." << endl;
        parent = _findPerson();
        if (parent == NULL) {
            return;
        }
        cout << endl;

        // 정보 입력
        string name, born, passedAway;
        cout << parent->getName() << "의 자식을 추가합니다." << endl;
        cout << "날짜는 yyyy-mm-dd 형식으로, 기일이 없으면 -을 입력합니다." << endl;
        cout << " 이름: "; cin >> name;
        cout << " 생년월일: "; cin >> born;
        cout << " 기일: "; cin >> passedAway;

        // parent의 자식으로 추가
        Person* newPerson = new Person(name, born, passedAway);
        parent->addChild(newPerson);
        int putResult = t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
        if(putResult) t->increaseLastGene();
    }
    cout << "구성원을 추가하였습니다." << endl;
}

Person* FamilyTreeManager::_findPerson()
{
    string findName;
    Person *p;
    int g;

    cout << ">> "; cin >> findName;
    cout << endl;

    cout << "세대 수를 알고 있습니까?(Y: 숫자 입력, N:0 입력) "; cin >> g;
    cout << endl;

    if (g == 0) p = t->search(findName);
    else if (g > 0) p = t->search(g, findName);
    else { cout << "잘못된 입력입니다." << endl; return NULL; }
    if (p == NULL) { cout << findName << "이 존재하지 않습니다." << endl; return NULL; }

    if (p) {
        int arrSize = 10;
        int numOfArr = 0;
        Person** arr = new Person*[arrSize];

        char ch;
        _printPerson(p);
        while (true)
        {
            cout << endl;
            cout << "찾으신 인물이 맞습니까?(Y/n) "; cin >> ch;
            if (ch != 'n') return p;
            cout << "다음 동명이인을 더 검색하시겠습니까?(Y/n) "; cin >> ch;
            cout << endl;
            if (ch != 'n') {
                arr[numOfArr++] = p;

                p = t->search(arr, numOfArr, findName);
                if (p == NULL)
                {
                    cout << "동명이인이 없습니다." << endl;
                    return NULL;
                }
                _printPerson(p);
            }
            else break;
        }
        return p;
    }
    else {
        cout << "해당 인물을 찾을 수 없습니다." << endl;
        return NULL;
    }
}

void FamilyTreeManager::_printPerson(Person* p)
{
    cout << p->getName() << "의 정보" << endl
        << "세대: " << p->getSibling()->getGene() << endl
        << "이름: " << p->getName() << endl
        << "생년월일: " << p->getBorn() << endl
        << "기일: " << p->getPassedAway() << endl;
}

void FamilyTreeManager::find()
{
    cout << "검색할 구성원의 이름을 입력해 주세요." << endl;
    Person *p = _findPerson();

    while (p != NULL) {
        fflush(stdin);
        getchar();
        int menu = 0;
        cout << "----------------------------------------" << endl
            << p->getName() << "의 가족 관계를 탐색합니다." << endl
            << "1. 부모 탐색" << endl
            << "2. 첫째 형제 탐색" << endl
            << "3. 동생 탐색" << endl
            << "4. 첫째 자식 탐색" << endl
            << "5. 탐색 종료" << endl
            << "----------------------------------------" << endl
            << "메뉴 선택 >> "; cin >> menu;
        cout << endl;
        switch (menu) {
        case 1:
            if (p->getSibling()->parent() == NULL) {
                cout << "시조는 부모의 정보가 없습니다." << endl;
            }
            else {
                cout << "부모 ";
                p = p->getSibling()->parent();
                _printPerson(p);
            }
            break;
        case 2:
            if (p == p->getSibling()->firstSibling()) {
                cout << p->getName() << "이(가) 이미 첫째입니다." << endl;
            }
            else {
                cout << "첫째 형제 ";
                p = p->getSibling()->firstSibling();
                _printPerson(p);
            }
            break;
        case 3:
            if (p == p->nextSibling()) {
                cout << p->getName() << "이(가) 이미 막내입니다." << endl;
            }
            else {
                cout << "막내 ";
                p = p->nextSibling();
                _printPerson(p);
            }
            break;
        case 4:
            if (p->getChildren()->firstSibling() == NULL) {
                cout << p->getName() << "은(는) 자식이 없습니다." << endl;
            }
            else {
                cout << "첫째 자식 ";
                p = p->getChildren()->firstSibling();
                _printPerson(p);
            }
            break;
        case 5:
            cout << "탐색을 종료합니다." << endl;
            return;
        }
    }
}

void FamilyTreeManager::modifyPerson()
{
    cout << "수정할 구성원의 이름을 입력해 주세요." << endl;
    Person *p = _findPerson();
    cout << endl;
    if (p != NULL)
    {
        string name, born, passedAway;
        cout << p->getName() << "의 정보를 수정합니다." << endl;

        cout << "이름: "; cin >> name;
        cout << "생년월일: "; cin >> born;
        cout << "기일: "; cin >> passedAway;

        p->setName(name);
		p->setBorn(born);
		p->setPassedAway(passedAway);
        cout << "수정되었습니다." << endl;
	} else {
        cout << "해당 인물을 찾을 수 없습니다." << endl;
	}
}

void FamilyTreeManager::show(){
    cout << t->getFamilyName() << " 가문 족보" << endl << endl;
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

	cout<<"촌수계산 시작 대상의 이름을 입력해 주세요." << endl;
    from = _findPerson();
    if (from == NULL) return;
    cout << endl;

	cout<<"촌수를 계산할 대상 이름을 입력해 주세요." << endl;
    target = _findPerson();
    if (target == NULL) return;
    cout << endl;

	cout<<"검색을 시작합니다..."<<endl;
    cout << endl;
	
	//1. 목표 선정
    fromSb = from->getSibling();
    targetSb = target->getSibling();

	oFrom = from;
	oTarget = target;
	
	//2. 레벨확인
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

	//3. 세대 확인하면서 세대를 올라감.
	while( from != target){
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
	cout<<"총 촌수 : "<<pFromCnt+pTargetCnt+(target != from ? 2 : 0)<<endl;
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
        cout << "Save 성공!" << endl;
	}
}

void FamilyTreeManager::load(){
	ifstream fin;
    string familyName, pname, name, born, passedAway;
	fin.open("data.ftl");

	if(fin.is_open()){
        cout << "저장된 파일을 부르시겠습니까?(Y/n) ";
        char op;
        cin >> op;
        cout << endl;
        if (op != 'n')
        {
		    while( !fin.eof() ){

			    if (t->getLastGene() < 1)
			    {
				    // rootSibling 초기화
				    Sibling* rootSibling = new Sibling(1, NULL);
				    t->get(1)->put(rootSibling);

                    fin >> familyName >> name >> born >> passedAway;

                    // 성씨 설정
                    t->setFamilyName(familyName);

				    // rootSibling의 형제로 추가
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

				    if (parent == NULL) { cout << pname << "이 존재하지 않습니다." << endl; continue;/* return; */}

				    // parent의 자식으로 추가
				    Person* newPerson = new Person(name, born, passedAway);
				    parent->addChild(newPerson);
				    int putResult = t->get(newPerson->getChildren()->getGene())->put(newPerson->getChildren());
				    if(putResult) t->increaseLastGene();
				
				    cout<< pname << " " <<name<<" "<<born<<" "<<passedAway<<" Loaded"<<endl;
			    }
            }
            cout << endl << "Load 성공!" << endl;
        }
        else
        {
            cout << "새로 시작합니다." << endl
                << "저장시 기존 데이터가 손실됩니다." << endl
                << "아무 키나 눌러 주세요." << endl;
        }
		fin.close();
	}
    else
    {
        cout << "data.ftl 파일이 없습니다." << endl
            << "새로 시작하려면 아무 키나 눌러 주세요." << endl;
    }
}