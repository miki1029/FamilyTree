#include <iostream>
#include "FamilyTreeManager.h"
#include "Person.h"
#include "Generation.h"
using namespace std;

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
    cout << "";
}

void FamilyTreeManager::find(){
	string name;
	Person *p;
	
	cout<<"검색할 구성원을 입력하세요\n>>";
	cin>>name;

	p = t.search(name);
	if( p ){
		cout<<p->getBorn()<<endl;
	} else {
		cout<<"해당 인물을 찾을 수 없습니다."<<endl;
	}

}


void FamilyTreeManager::show(){
	int i;
	Generation *g;

	for(i = 1; i < t.getLastGene(); i++){
		g = t.get(i);
		
	}
}