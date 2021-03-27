#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/* include */
#include "Engine_Include.h"

#include "Cycle.h"

#include "Component.h"
#include "Transform.h"

/* define */
#define INSTANTIATE	GameObject::Instantiate
#define DESTROY		GameObject::Destroy

class _declspec(dllexport) GameObject : public Cycle
{
private:
	/* 생성자/소멸자가 아니라 Instantiate랑 destroy로 겜 옵줵 생성/소멸 관리 할꺼임 */
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
	virtual void ReadyRender() override;
	virtual void Release() override;

#pragma region Template
public:
	/* Set / Add */
	template <class T>
	GameObject* Add_Component(class T::Desc* _desc)
	{
		Component* component = nullptr;
		component = Component::Instantiate<T>(_desc);
		assert(L"Add Component is failed" && component);

		component->Set_GameObject(this);
		//compoent->Set_Transform(m_Transform);

		//Test
		m_vecComponents.emplace_back(component);

		return this;
	}

	template <class T>
	GameObject* Add_Component()
	{
		Component* component = nullptr;
		component = Component::Instantiate<T>();
		assert(L"Add Component is failed" && component);

		component->Set_GameObject(this);
		//component->Set_Transform(m_Transform);
		
		//Test
		m_vecComponents.emplace_back(component);

		return this;
	}

	/* Get */
	template<class T>
	T* Get_Component()
	{

	}

	template<class T>
	T* Get_NewComponent()
	{
	
	}

	/* Delete */
	template<class T>
	void Delete_Component()
	{

	}

#pragma endregion

public: /* functions */
	

public: /* Get */
	Transform*		Get_Transform()		const;
	const Vector3&	Get_Position()		const;
	const Vector3&	Get_Scale()			const;

	const wstring	Get_Name()			const;
	int				Get_Tag()			const;

	bool			Get_DontDestroy()	const;
	bool			Get_Active()		const;
	bool			Get_Alive()			const;

public: /* Set */
	void		Set_Transform(Transform* _pTransform);
	void		Set_Position(const Vector3& _vPos);
	void		Set_Position(float _x, float _y, float _z);
	void		Set_Scale(const Vector3& _vScale);
	void		Set_Scale(float _x, float _y, float _z);
	void		Set_Rotation(const Quaternion& _qRot);
	void		Set_Rotation(float _x, float _y, float _z);

	void		Set_DontDestroy(bool _FalseIsDestroyWhenChangeScene);
	void		Set_Active(bool _onoff);
	void		Set_Alive(bool _FalseIsDead);

private:
	vector<Component*>		m_vecComponents;
	vector<Component*>		m_vecNewComponents;
	//=> new 컴포넌트가 있는 이유?
		//혹시 LateUdpate처럼 Update가 아닌 다른 순서에서 생성되서 바로 들어간다면
		//그 컴포넌트도 그 Cycle의 순서부터 도는데
		//순차적으로 굴러가야 되는 경우 문제 생길 수도 있어서
		//생성하고, 추가하고 다음 프레임에서 일괄적으로 등록하기 위해서. 그렇읍니다.

protected:
	Transform* m_Transform = nullptr;

private:
	int			m_iTag = 0;
	wstring		m_wName = L"Default";
	
	bool		m_bActive = true; //
	bool		m_bAlive = true; //false, 즉 Dead상태되면 다음 프레임에서 바로 삭제
	bool		m_bDontDestroy = false; //씬 지나도 삭제 되지 않도록.


										// Cycle을(를) 통해 상속됨
	

};

#endif