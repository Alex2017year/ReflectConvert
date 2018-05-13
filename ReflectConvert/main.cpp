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
	// 不能这样操作，由于m_classInfo 是静态的，有什么办法？能够解决这个问题呢？
	// 此外需要引入智能指针
	Object* p = Object::CreateObject("A"); // 可以算作反射
	A* ap = dynamic_cast<A*>(p);
	ap->setId(1);

	Object* p1 = Object::CreateObject("A"); // 可以算作反射
	A* ap1 = dynamic_cast<A*>(p1);
	ap1->setId(2);
	
	Object* p2 = Object::CreateObject("A"); // 可以算作反射
	A* ap2 = dynamic_cast<A*>(p2);
	ap2->setId(3);
}


void test2()
{
	std::vector<Object*> grp = ResolveGroup("A"); // 保存注册的数据，便于之后在获取
	
	for (Object* pObj : grp)
	{
		A* ap = dynamic_cast<A*>(pObj);
		if (ap) ap->StringObj();
		delete ap;
	}
}


int main()
{
	// Object* p2 = Object::CreateObject("B"); // 失败，没有注册这种类型
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