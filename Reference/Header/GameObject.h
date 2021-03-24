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
private: /* 생성자/소멸자가 아니라 Instantiate랑 destroy로 겜 옵줵 생성/소멸 관리 할꺼임 */
	explicit GameObject() = default;
	virtual ~GameObject() = default;

public:
	static GameObject*	Instantiate(int _iTag = 0, wstring _wName = L"");
	static void			Destory(GameObject* _pObj);

public:
	// Cycle을(를) 통해 상속됨
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