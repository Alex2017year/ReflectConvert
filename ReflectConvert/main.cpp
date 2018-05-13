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
	Object* p = Object::CreateObject("A");

	A* ap = dynamic_cast<A*>(p);
	ap->StringObj();


	delete p;
	system("pause");
	return 0;
}