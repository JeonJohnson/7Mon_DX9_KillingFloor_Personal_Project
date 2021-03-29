#include "..\Header\GameObject.h"

#include "GameObjectManager.h"



GameObject * GameObject::Instantiate(int _iTag, wstring _wName)
{
	GameObject* obj = nullptr;

	obj = new GameObject;
	assert(L"GameObject instance failed." && obj);
	
	obj->Initialize();
	obj->m_iTag = _iTag;
	obj->m_wName = _wName;

	GameObjectManager::Get_Instance()->Insert_GameObject(obj);

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
	//newCompo랑 그냥Compo랑 합치기
	Merge_Components();
	Delete_DeadComponents();

	for (auto& component : m_vecComponents)
	{
		component.second->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_vecComponents)
	{
		component.second->LateUpdate();
	}
}

void GameObject::ReadyRender()
{
	for (auto& component : m_vecComponents)
	{
		component.second->ReadyRender();
	}
}

void GameObject::Release()
{
}

void GameObject::Merge_Components()
{
	if (m_vecNewComponents.size() == 0)
	{
		return;
	}

	for (auto& newComponent : m_vecNewComponents)
	{
		m_vecComponents.emplace_back(newComponent);
	}

	m_vecNewComponents.clear();
	m_vecNewComponents.shrink_to_fit();

	m_vecComponents.shrink_to_fit();

}

void GameObject::Delete_DeadComponents()
{
	//for (auto& component : m_vecComponents)
	//{
	//	if (component.second->Get_Alive() == false)
	//	{
	//		component.second->Release();
	//		delete component.second;
	//
	// 근히ㅡ야 벡터 삭제할때 이 ㅣㅈ랄 나면 좆되는거 ㅇㄹ잖아 무지성 코딩 금지
	//	}
	//}

	for (auto iter = m_vecComponents.begin(); iter != m_vecComponents.end();)
	{
		if (iter->second->Get_Alive() == false)
		{
			iter->second->Release();
			delete iter->second;
			iter = m_vecComponents.erase(iter);
		}
		else { ++iter; }
	}

	m_vecComponents.shrink_to_fit();
}

Transform * GameObject::Get_Transform() const
{
	return m_Transform;
}

const Vector3 & GameObject::Get_Position() const
{
	Vector3 asdf;
	return asdf;
}

const Vector3 & GameObject::Get_Scale() const
{
	Vector3 asdf;
	return asdf;
}

const wstring GameObject::Get_Name() const
{
	return m_wName;
}

int GameObject::Get_Tag() const
{
	return m_iTag;
}

bool GameObject::Get_DontDestroy() const
{
	return m_bDontDestroy;
}

bool GameObject::Get_Active() const
{
	return m_bActive;
}

bool GameObject::Get_Alive() const
{
	return m_bAlive;
}

void GameObject::Set_Transform(Transform * _pTransform)
{
}

void GameObject::Set_Position(const Vector3 & _vPos)
{
}

void GameObject::Set_Position(float _x, float _y, float _z)
{
}

void GameObject::Set_Scale(const Vector3 & _vScale)
{
}

void GameObject::Set_Scale(float _x, float _y, float _z)
{
}

void GameObject::Set_Rotation(const Quaternion & _qRot)
{
}

void GameObject::Set_Rotation(float _x, float _y, float _z)
{
}

void GameObject::Set_DontDestroy(bool _FalseIsDestroyWhenChangeScene)
{
	m_bDontDestroy = _FalseIsDestroyWhenChangeScene;
}

void GameObject::Set_Active(bool _onoff)
{
	m_bActive = _onoff;
}

void GameObject::Set_Alive(bool _FalseIsDead)
{
	m_bAlive = _FalseIsDead;
}


