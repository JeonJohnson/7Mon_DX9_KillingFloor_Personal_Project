#pragma once

#ifndef _UI_COMPONENT_H_
#define _UI_COMPONENT_H_

#include "Engine_Include.h"

#include "Cycle.h"

class UI;
class Transform;

class DLL_STATE UI_Component : public Cycle
{

	//ComponentÀÇ ¿ªÇÒ.

public:
	explicit UI_Component() = default;
	virtual ~UI_Component() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Render() override;
	virtual void Release() override;

#pragma region	Template
public:
	template <class T>
	static UI_Component* Instantiate(class T::Desc* _desc)
	{
		UI_Component* Instance = nullptr;
		Instance = new T(_desc);
		assert("UI_Component Instance Failed" && Instance);
		Instance->Initialize();

		return Instance;
	}

	//template <class T>
	//static UI_Component* Instantiate(T::Desc* _desc)
	//{
	//	UI_Component* Instance = nullptr;
	//	Instance = new T(_desc);
	//	assert("UI_Component Instance Failed" && Instance);
	//	Instance->Initialize();

	//	return Instance;
	//}

#pragma endregion

public: /* function */

public: /* Get */
	virtual		UI_KIND	Get_UIkind() const = 0;

	bool		Get_Active() const;
	bool		Get_Alive()	const;

public: /* Set */
	void		Set_Active(bool _onoff);
	void		Set_Alive(bool _FalseIsDead);


private:
	Vector3				m_vPosition;
	Vector3				m_vScale;
	Vector3				m_vRotation;

	bool			m_bActive = true;
	bool			m_bAlive = true;
	
};

#endif //_UI_COMPONENT_H_