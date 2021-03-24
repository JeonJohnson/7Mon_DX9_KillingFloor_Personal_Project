#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Engine_Include.h"
#include "Cycle.h"
#include "GameObject.h"


class _declspec(dllexport) Component : public Cycle
{
public:
	Component();
	~Component();

protected:
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void Release() override = 0;

#pragma region Template
	//������Ʈ�ȿ� ������Ʈ ���� �����ϰ�...?
	//�ϴ� SR �Ĺ�� �� ���� �����ߴµ� 
	//�ϴ� ������ ���ƺ���.

public: /* Create */
	template<class T>
	static Component* Instantiate(class T::Desc* _desc)
	{
		Component* Instance = nullptr;
		Instance = new T(_desc);
		
		assert(L"Component Instance failed" && Instance);
		
		return Instance;
	}

//public: /* Get */
#pragma endregion 

public:

public:

protected:
	GameObject*		m_GameObject;
	//Transform*		m_Transform;

private:
	bool		m_bActive	= true;
	bool		m_bAlive	= true;

};

#endif