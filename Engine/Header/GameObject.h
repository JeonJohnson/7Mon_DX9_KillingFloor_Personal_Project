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

class DLL_STATE GameObject : public Cycle
{
	friend class GameObjectManager;
	//�׿ɢh �Ŵ������� �����Ҷ� ����,�Ҹ��ڰ� private�� ������ ģ�� ����.
		//=>friend �ھƹ����� public�̰� private�̰� �� �� �� ���� ����;
private:
	/* ������/�Ҹ��ڰ� �ƴ϶� Instantiate�� destroy�� �� �ɢh ����/�Ҹ� ���� �Ҳ��� */
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
		component->Set_Transform(m_Transform);
		//�̰� ���� ������Ʈ�����ڶ� �̴ϼȶ����� ������� �����̵Ǽ� �̷��ǳ�.

		//Test
		//m_vecComponents.emplace_back(component);
		string strName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		wstring wName;
		wName.assign(strName.begin(), strName.end());
		 
		m_vecNewComponents.emplace_back(pair<wstring, Component*>(wName,component));

		return this;
	}

	template <typename T>
	GameObject* Add_Component()
	{
		Component* component = nullptr;
		
		typename T::Desc tempDesc;
		component = Component::Instantiate<T>(&tempDesc);
		assert(L"Add Component is failed" && component);

		component->Set_GameObject(this);
		component->Set_Transform(m_Transform);
		
		//Test
		//m_vecComponents.emplace_back(component);
		//wstring wName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		string strName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		wstring wName;
		wName.assign(strName.begin(), strName.end());

		m_vecNewComponents.emplace_back(pair<wstring, Component*>(wName, component));

		return this;
	}

	/* Get */
	template<class T>
	T* Get_Component()
	{
		//�ù� ��� ã����� string�� �ʿ��ϳ�
		string strName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		wstring wName;
		wName.assign(strName.begin(), strName.end());

		for (auto& component : m_vecComponents)
		{
			if (component.first == wName)
			{
				return (T*)component.second;
			}
		}

		return nullptr;
	}

	template<class T>
	T* Get_NewComponent()
	{
		if (m_vecNewComponents.size() == 0)
		{
			return nullptr;
		}
		
		string strName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		wstring wName;
		wName.assign(strName.begin(), strName.end());

		for (auto& newComponent : m_vecNewComponents)
		{
			if (newComponent.first == wName)
			{
				return (T*)newComponent.second;
			}
		}

		return nullptr;
	}

	/* Delete */
	template<class T>
	void Delete_Component()
	{
		string strName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		wstring wName;
		wName.assign(strName.begin(), strName.end());

		for (auto& component : m_vecComponents)
		{
			if (component->first == wName)
			{
				component->second->Set_Alive(false);
				//������ ������ �� ������Ʈ���� ���ݵ��.
			}
		}

	}

#pragma endregion

public: /* functions */
	void Merge_Components();
	void Delete_DeadComponents();
	
public: /* Get */
#pragma region Transform
	Transform*			Get_Transform()		const;
	const Vector3&		Get_Position()		const;
	const Vector3&		Get_Scale()			const;
	const Quaternion&	Get_Rotation()		const;
	Vector3		Get_Rotation_Euler() const;
#pragma endregion

	const wstring	Get_Name()			const;
	int				Get_Tag()			const;

	bool			Get_DontDestroy()	const;
	bool			Get_Active()		const;
	bool			Get_Alive()			const;

public: /* Set */
#pragma region Transform
	void		Set_Transform(Transform* _pTransform);
	
	//position
	void		Set_Position(const Vector3& _vPos);
	void		Set_Position(float _x, float _y, float _z);
	void		Add_Position(const Vector3& _vPos);
	void		Add_PosX(float _x);
	void		Add_PosY(float _y);
	void		Add_PosZ(float _z);

	//scale
	void		Set_Scale(const Vector3& _vScale);
	void		Set_Scale(float _x, float _y, float _z);
	void		Add_Scale(const Vector3& _vScale);
	void		Add_ScaleX(float _x);
	void		Add_ScaleY(float _y);
	void		Add_ScaleZ(float _z);

	//rotation
	void		Set_Rotation(const Quaternion& _qRot);
	void		Set_Rotation(float _eulerX, float _eulerY, float _eulerZ);
	void		Set_Rotation(const Vector3 & _euluerVector);
	void		Set_RotationX(float _eulerX);
	void		Set_RotationY(float _eulerY);
	void		Set_RotationZ(float _eulerZ);
	void		RotateX(float _eulerX);
	void		RotateY(float _eulerY);
	void		RotateZ(float _eulerZ);
	void		RotateAxis(const Vector3& _axis, float _radian, Quaternion* _pOut);
	void		RotateAxis(const Vector3& _axis, float _radian);

#pragma endregion

	void		Set_DontDestroy(bool _FalseIsDestroyWhenChangeScene);
	void		Set_Active(bool _onoff);
	void		Set_Alive(bool _FalseIsDead);

private:
	vector<pair<wstring, Component*>>	 	m_vecNewComponents;
	vector<pair<wstring, Component*>>		m_vecComponents;
	//=> new ������Ʈ�� �ִ� ����?
		//Ȥ�� LateUdpateó�� Update�� �ƴ� �ٸ� �������� �����Ǽ� �ٷ� ���ٸ�
		//�� ������Ʈ�� �� Cycle�� �������� ���µ�
		//Update���� ���������� �������� �Ǵ� ��� ���� ���� ���� �־
		//�����ϰ�, ��� �߰��ϴ� ���� ������ Update���� �ϰ������� ����ϱ� ���ؼ�. ��, �׷����ϴ�.
	//Gameobject�� �䷸�� ���������ϱ� ������

	//�� wsring �ִ� pair������ٰ� �ֳ�
	//Get�Ҷ�� �� �־�� �ϴµ� �׶� ����� ����;

protected:
	Transform* m_Transform = nullptr;

private:
	int			m_iTag = 0;
	wstring		m_wName = L"Default";
	
	bool		m_bActive = true; //
	bool		m_bAlive = true; //false, �� Dead���µǸ� ���� �����ӿ��� �ٷ� ����
	bool		m_bDontDestroy = false; //�� ������ ���� ���� �ʵ���.

};

#endif //_GAMEOBJECT_H_