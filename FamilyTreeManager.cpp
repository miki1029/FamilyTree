#include <iostream>
#include "FamilyTreeManager.h"
#include "Person.h"
#include "Generation.h"
using namespace std;

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
    cout << "";
}

void FamilyTreeManager::find(){
	string name;
	Person *p;
	
	cout<<"�˻��� �������� �Է��ϼ���\n>>";
	cin>>name;

	p = t.search(name);
	if( p ){
		cout<<p->getBorn()<<endl;
	} else {
		cout<<"�ش� �ι��� ã�� �� �����ϴ�."<<endl;
	}

}


void FamilyTreeManager::show(){
	int i;
	Generation *g;

	for(i = 1; i < t.getLastGene(); i++){
		g = t.get(i);
		
	}
}