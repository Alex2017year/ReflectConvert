#include <iostream>
#include <cstring>
#include <vector>
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

	void setId(int id)
	{
		m_id = id;
	}

public:
	void StringObj() const
	{
		cout << "This is Class A id: " << m_id << endl;
	}
private:
	int m_id;
};
IMPLEMENT_CLASS(A)


void test()
{
	// ������������������m_classInfo �Ǿ�̬�ģ���ʲô�취���ܹ������������أ�
	// ������Ҫ��������ָ��
	Object* p = Object::CreateObject("A"); // ������������
	A* ap = dynamic_cast<A*>(p);
	ap->setId(1);

	Object* p1 = Object::CreateObject("A"); // ������������
	A* ap1 = dynamic_cast<A*>(p1);
	ap1->setId(2);
	
	Object* p2 = Object::CreateObject("A"); // ������������
	A* ap2 = dynamic_cast<A*>(p2);
	ap2->setId(3);
}


void test2()
{
	std::vector<Object*> grp = ResolveGroup("A"); // ����ע������ݣ�����֮���ڻ�ȡ
	
	for (Object* pObj : grp)
	{
		A* ap = dynamic_cast<A*>(pObj);
		if (ap) ap->StringObj();
		delete ap;
	}
}


int main()
{
	// Object* p2 = Object::CreateObject("B"); // ʧ�ܣ�û��ע����������
	// A* ap2 = dynamic_cast<A*>(p2);
	// if (ap2) ap2->StringObj();

	test();
	test2();

	ReleaseAll();
	// delete p2;
	// delete p;
	system("pause");
	return 0;
}