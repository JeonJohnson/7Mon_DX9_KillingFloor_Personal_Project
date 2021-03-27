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
	//컴포넌트안에 컴포넌트 삽입 가능하게...?
	//일단 내 스타일 대로라면 SR 컴뱃에서 할 일이 없긴했는데 
	//일단 만들지 말아보자. 

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
	//프로텍티드로 할 이유 유?
	GameObject*		m_GameObject = nullptr;
	Transform*		m_Transform = nullptr;

private:
	bool		m_bActive	= true;
	bool		m_bAlive	= true;

	//wstring		m_wName = L"Default"; //이걸로 딱히 이름을 정할건 아니고,
	//원래 준니티에서는 typeid(T).name()로 Component 클래스 이름 자체를 넣어줌.
	//일단 난 보류. 디버깅용인거 같으니 그 외에꺼 다 성공하면 넣어주기.
};

#endif