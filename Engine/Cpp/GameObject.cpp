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
	_pObj->Set_Alive(false);
}

void GameObject::Initialize()
{
	m_bActive = true; 
	m_bAlive = true; 
	m_bDontDestroy = false; 
	
	this->Add_Component<Transform>();
	Merge_Components();
	m_Transform = Get_Component<Transform>();
}

void GameObject::Update()
{
	//newCompo랑 그냥Compo랑 합치기
	Merge_Components();
	Delete_DeadComponents();

	for (auto& component : m_vecComponents)
	{
		if (component.second->Get_Active())
		{
			component.second->Update();
		}
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_vecComponents)
	{
		if (component.second->Get_Active())
		{
			component.second->LateUpdate();
		}
	}
}

void GameObject::ReadyRender()
{
	for (auto& component : m_vecComponents)
	{
		if (component.second->Get_Active())
		{
			component.second->ReadyRender();
		}
	}
}

void GameObject::Release()
{
	Merge_Components();

	for (auto iter = m_vecComponents.begin(); iter != m_vecComponents.end();)
	{

		(*iter).second->Release();
		delete (*iter).second;

		iter = m_vecComponents.erase(iter);
	}

	if (m_vecComponents.size() > 0)
	{
		assert(0 && L"Components dont Release all");	
	}

}

void GameObject::Merge_Components()
{
	if (m_vecNewComponents.size() == 0)
	{
		return;
	}

	for (auto& newComponent : m_vecNewComponents)
	{
		//컴포넌트 이니셜 라이즈 시기 맞추기.
		newComponent.second->Initialize();
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
		if ((*iter).second->Get_Alive() == false)
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
	return m_Transform->Get_Position();
}

const Vector3 & GameObject::Get_Scale() const
{
	return m_Transform->Get_Scale();
}

const Quaternion & GameObject::Get_Rotation() const
{
	return m_Transform->Get_Rotation();
}

Vector3 GameObject::Get_Rotation_Euler() const
{
	return m_Transform->Get_Rotation_Euler();
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
	m_Transform->Set_Transform(_pTransform);
}

void GameObject::Set_Position(const Vector3 & _vPos)
{
	m_Transform->Set_Position(_vPos);
}

void GameObject::Set_Position(float _x, float _y, float _z)
{
	Vector3 PosTemp = { _x, _y, _z };
	m_Transform->Set_Position(PosTemp);
}

void GameObject::Add_Position(const Vector3 & _vPos)
{
	m_Transform->Add_Position(_vPos);
}

void GameObject::Add_PosX(float _x)
{
	m_Transform->Add_PosX(_x);
}

void GameObject::Add_PosY(float _y)
{
	m_Transform->Add_PosY(_y);
}

void GameObject::Add_PosZ(float _z)
{
	m_Transform->Add_PosZ(_z);
}

void GameObject::Set_Scale(const Vector3 & _vScale)
{
	m_Transform->Set_Scale(_vScale);
}

void GameObject::Set_Scale(float _x, float _y, float _z)
{
	Vector3 ScaleTemp = { _x, _y, _z };
	m_Transform->Set_Scale(ScaleTemp);
}

void GameObject::Add_Scale(const Vector3 & _vScale)
{
	m_Transform->Add_Scale(_vScale);
}

void GameObject::Add_ScaleX(float _x)
{
	m_Transform->Add_ScaleX(_x);
}

void GameObject::Add_ScaleY(float _y)
{
	m_Transform->Add_ScaleY(_y);
}

void GameObject::Add_ScaleZ(float _z)
{
	m_Transform->Add_ScaleZ(_z);
}

void GameObject::Set_Rotation(const Quaternion & _qRot)
{
	m_Transform->Set_Rotation(_qRot);
}

void GameObject::Set_Rotation(float _eulerX, float _eulerY, float _eulerZ)
{
	m_Transform->Set_Rotation(_eulerX, _eulerY, _eulerZ);
}

void GameObject::Set_Rotation(const Vector3& _euluerVector)
{
	m_Transform->Set_Rotation(_euluerVector);
}

void GameObject::Set_RotationX(float _eulerX)
{
	m_Transform->Set_RotationX(_eulerX);
}

void GameObject::Set_RotationY(float _eulerY)
{
	m_Transform->Set_RotationY(_eulerY);
}

void GameObject::Set_RotationZ(float _eulerZ)
{
	m_Transform->Set_RotationZ(_eulerZ);
}

void GameObject::RotateX(float _eulerX)
{
	m_Transform->RotateX(_eulerX);
}

void GameObject::RotateY(float _eulerY)
{
	m_Transform->RotateY(_eulerY);
}

void GameObject::RotateZ(float _eulerZ)
{
	m_Transform->RotateZ(_eulerZ);
}

void GameObject::RotateAxis(const Vector3 & _axis, float _radian, Quaternion * _pOut)
{
	m_Transform->RotateAxis(_axis, _radian, _pOut);
}

void GameObject::RotateAxis(const Vector3 & _axis, float _radian)
{
	m_Transform->RotateAxis(_axis, _radian);
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


