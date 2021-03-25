#include "..\Header\Component.h"

#include "GameObject.h"
#include "Transform.h"

//Component::Component()
//{
//}
//
//
//Component::~Component()
//{
//}

void Component::Initialize()
{
}

void Component::Update()
{
}

void Component::LateUpdate()
{
}

void Component::ReadyRender()
{
}

void Component::Release()
{
}

void Component::On_Active()
{
}

void Component::Off_Active()
{
}

GameObject * Component::Get_GameObject() 
{
	return m_GameObject;
}

Transform * Component::Get_Transform() 
{
	return m_Transform;
}

bool Component::Get_Active() const
{
	return m_bActive;
}

bool Component::Get_Alive() const
{
	return m_bAlive;
}

void Component::Set_Active(bool _onoff)
{
	m_bActive = _onoff;
}

void Component::Set_Alive(bool _FalseIsDead)
{
	m_bAlive = _FalseIsDead;
}

void Component::Set_GameObject(GameObject * _pGameObj)
{
	assert(L"Set GameObject is failed"&& _pGameObj);

	m_GameObject = _pGameObj;
}

void Component::Set_Transform(Transform * _pTransform)
{
	assert(L"Set Transform is failed"&& _pTransform);
	
	m_Transform = _pTransform;
}

void Component::Set_Position(const Vector3 & _vPos)
{
	
}

void Component::Set_Scale(const Vector3 & _vScale)
{
}
