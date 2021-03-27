#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Engine_Include.h"

#include "Cycle.h"

//#include "GameObject.h"

class GameObject;
class Transform;

class _declspec(dllexport) Component : public Cycle
{
public:
	explicit Component() = default;
	virtual ~Component() = default;

protected:
	/* Cycle */
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void ReadyRender() override;
	virtual void Render() override;
	virtual void Release() override = 0;

public:
	//Active On/Off
	virtual void On_Active() override;
	virtual void Off_Active() override;

public:
	//collision



#pragma region Template
	//������Ʈ�ȿ� ������Ʈ ���� �����ϰ�...?
	//�ϴ� �� ��Ÿ�� ��ζ�� SR �Ĺ�� �� ���� �����ߴµ� 
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

	template<class T>
	static Component* Instantiate()
	{
		Component* Instance = nullptr;
		Instance = new T();
		
		assert(L"Component Instance failed" && Instance);

		return Instance;
	}

//public: /* Get */
#pragma endregion 
public: /* Function */


public: /* Get */
	GameObject*	Get_GameObject();
	Transform*	Get_Transform();

	bool		Get_Active()	const;
	bool		Get_Alive()		const;

public: /* Set */
	void		Set_Active(bool _onoff);
	void		Set_Alive(bool _FalseIsDead);

	void		Set_GameObject(GameObject* _pGameObj);

	void		Set_Transform(Transform* _pTransform);
	void		Set_Position(const Vector3& _vPos);
	void		Set_Scale(const Vector3& _vScale);
	

protected: 
	//������Ƽ��� �� ���� ��?
	GameObject*		m_GameObject = nullptr;
	Transform*		m_Transform = nullptr;

private:
	bool		m_bActive	= true;
	bool		m_bAlive	= true;

	//wstring		m_wName = L"Default"; //�̰ɷ� ���� �̸��� ���Ұ� �ƴϰ�,
	//���� �ش�Ƽ������ typeid(T).name()�� Component Ŭ���� �̸� ��ü�� �־���.
	//�ϴ� �� ����. �������ΰ� ������ �� �ܿ��� �� �����ϸ� �־��ֱ�.
};

#endif