#include "..\Header\GameObject.h"


GameObject * GameObject::Instantiate(int _iTag, wstring _wName)
{
	GameObject* obj = nullptr;

	obj = new GameObject;
	assert(L"GameObject instance failed." && obj);
	
	obj->Initialize();
	obj->m_iTag = _iTag;
	obj->m_wName = _wName;

	return obj;
}

void GameObject::Destory(GameObject * _pObj)
{
}

void GameObject::Initialize()
{
	m_bActive = true; 
	m_bAlive = true; 
	m_bDontDestroy = false; 
}

void GameObject::Update()
{
}

void GameObject::LateUpdate()
{
}

void GameObject::Release()
{
}
