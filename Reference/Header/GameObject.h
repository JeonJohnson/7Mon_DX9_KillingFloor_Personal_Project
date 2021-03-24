#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/* include */
#include "Engine_Include.h"

#include "Cycle.h"


/* define */
#define INSTANTIATE	GameObject::Instantiate
#define DESTROY		GameObject::Destroy

class _declspec(dllexport) GameObject : public Cycle
{
private: /* ������/�Ҹ��ڰ� �ƴ϶� Instantiate�� destroy�� �� �ɢh ����/�Ҹ� ���� �Ҳ��� */
	explicit GameObject() = default;
	virtual ~GameObject() = default;

public:
	static GameObject*	Instantiate(int _iTag = 0, wstring _wName = L"");
	static void			Destory(GameObject* _pObj);

public:
	// Cycle��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

#pragma region Template
public:
	template <class T>
	GameObject* Add_Component(class T::Desc* _desc)
	{
		
	}

	template <class T>
	GameObject* Add_Component()
	{
	
	}


#pragma endregion

public:

private:
};

#endif