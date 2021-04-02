#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Engine_Include.h"

#include "Cycle.h"

//#include "GameObject.h"

class GameObject;
class Transform;

class DLL_STATE Component : public Cycle
{
public:
	explicit Component() = default;
	virtual ~Component() = default;

public:
	/* Cycle */
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void ReadyRender() override = 0;
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
		Instance->Initialize();
		
		
		return Instance;
	}

	template<class T>
	static Component* Instantiate()
	{
		Component* Instance = nullptr;
		Instance = new T();
		assert(L"Component Instance failed" && Instance);
		Instance->Initialize();
		

		return Instance;
	}


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

	virtual void	Set_Transform(Transform* _pTransform);
	/* Set_Transform에 virtual건 이유
	Gameobject를 init하는 과정에서 m_Transform도 Component기 때문에 Add_Component를 하는데
	Add Component안에서 Set_Transform을 함.
	근디 아직 GameObject의 transform은 없지. 만드는 중인데...
	그래서 자기 자신을 받을꺼임.
	헌테 이게 Component(부모) 함수가 호출되는거니까 override 걸어주면 딱 되것다. 이거야.
	어차피 다른 component들한테는 이거 안 만들 꺼거든
	*/

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

#endif //_COMPONENT_H_