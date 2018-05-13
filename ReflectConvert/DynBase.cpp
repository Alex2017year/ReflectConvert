#include "DynBase.h"
#include <iostream>
#include <vector>
#include <map>

// 释放内存的问题
static std::map<string, ClassInfo*> *classInfoMap = NULL;  // 保存类型名称与类的型映射关系
static std::multimap<string, Object*> *ObjectMap = NULL;   // 保存类型名称与类的实例映射关系

using namespace std;

IMPLEMENT_CLASS(Object)
bool Object::Register(ClassInfo* ci)
{
	if (!classInfoMap)
	{
		classInfoMap = new std::map<string, ClassInfo*>();
	}

	if (ci)
	{
		if (classInfoMap->find(ci->m_className) == classInfoMap->end())
		{
			classInfoMap->insert(make_pair(ci->m_className, ci));

		}
	}

	return true;
}

Object* Object::CreateObject(string name)
{
	map<string, ClassInfo*>::const_iterator iter = classInfoMap->find(name);
	if (classInfoMap->end() != iter)
	{
		Object* objPtr = iter->second->CreateObject();
		if (!objPtr)
		{
			return NULL;
		}

		if (!ObjectMap)
		{
			ObjectMap = new std::multimap<string, Object*>();
		}
		ObjectMap->insert(make_pair(name, objPtr));

		return objPtr;
	}
	
	std::cout << "类型：" << name << " 没有被定义" << std::endl;
	return NULL;
}


bool Register(ClassInfo* ci){
	return Object::Register(ci);
}

std::vector<Object*> ResolveGroup(string className)
{
	std::vector<Object*> ret;

	auto range = ObjectMap->equal_range(className);
	for (auto i = range.first; i != range.second; ++i)
	{
		ret.push_back(i->second);
	}

	return ret;
}

void ReleaseAll()
{
	if (classInfoMap)
	{
		delete classInfoMap;
		classInfoMap = NULL;
	}

	if (ObjectMap)
	{
		delete ObjectMap;
		ObjectMap = NULL;
	}
}