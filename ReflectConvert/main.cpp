#include <iostream>
#include <cstring>
#include "DynBase.h"

using namespace std;

class A : public Object
{
	DECLARE_CLASS(A)
public:
	A() 
	{
		cout << hex << reinterpret_cast<long>(this) << " A constructor! " << endl;
	}

	~A()
	{
		cout << hex << reinterpret_cast<long>(this) << " A destructor! " << endl;
	}

public:
	void StringObj() const
	{
		cout << "This is Class A" << endl;
	}
};
IMPLEMENT_CLASS(A)



int main()
{
	Object* p = Object::CreateObject("A"); // ������������

	A* ap = dynamic_cast<A*>(p);
	if (!ap) ap->StringObj();


	Object* p2 = Object::CreateObject("B"); // ʧ�ܣ�û��ע����������
	A* ap2 = dynamic_cast<A*>(p2);
	if (!ap2) ap2->StringObj();


	delete p2;
	delete p;
	system("pause");
	return 0;
}