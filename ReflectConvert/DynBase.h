#pragma once
#include <string>
using namespace std;

class Object;
class ClassInfo;
typedef Object* (*ObjectConstructorFn)(void);
bool Register(ClassInfo *ci);

/*
	这个类的作用是为了保存类的型和构造函数
*/
class ClassInfo
{
public:
	ClassInfo(const string className, ObjectConstructorFn ctor) :
		m_className(className), m_objectConstructor(ctor) 
	{
		Register(this);
	}

	virtual ~ClassInfo() {}

	// 空的构造函数
	Object* CreateObject() const { return m_objectConstructor ? (*m_objectConstructor)() : NULL; }
	bool IsDynamic() const { return NULL != m_objectConstructor; }
	const string GetClassName() const { return m_className; }
	ObjectConstructorFn GetConstructor() const { return m_objectConstructor; }
public:
	string m_className;							// 类的名称
	ObjectConstructorFn m_objectConstructor;	// 类的构造函数
};


// 使用static 定义这个ClassInfo类的成员变量，会被所有类共享
#define DECLARE_CLASS(name) \
		protected: \
			static ClassInfo ms_classInfo; \
		public: \
			virtual ClassInfo* GetClassInfo() const; \
			static Object* CreateObject();

#define IMPLEMENT_CLASS_COMMON(name, func) \
		ClassInfo name::ms_classInfo((#name), \
				  (ObjectConstructorFn) func); \
		ClassInfo* name::GetClassInfo() const \
			{ return &name::ms_classInfo; }

#define IMPLEMENT_CLASS(name) \
	IMPLEMENT_CLASS_COMMON(name, name::CreateObject) \
	Object* name::CreateObject() \
		{ return new name; }

class Object
{
	DECLARE_CLASS(Object)
public:
	Object() {};
	virtual ~Object() {};
	static bool Register(ClassInfo* ci);
	static Object* CreateObject(string name);
};

