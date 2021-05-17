#pragma once

#ifndef _ZED_H_
#define _ZED_H_

#include "Component.h"

class StateController;
class AnimationController;
class SphereCollider;
class Zed_Status;

class Zed : public Component
{
public:
	struct Desc
	{
		ZED_INFO	tZed_Status;
	};
public:
	Zed(Desc* _desc);
	virtual ~Zed();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void	Setting_Components();
	
	void	LookAt();
	void	Walk();
	void	Run();
	void	Attack();
	void	Damaged(int _iDmg);
	//void	Death();
	

public: /* Func */

public: /* Get */
	ZED_INFO				Get_ZedInfo();
	float					Get_Distance();

public: /* Set */

private:
	StateController*		m_pStateCtrl = nullptr;
	AnimationController*	m_pAnimCtrl = nullptr;
	//Zed_Status*				m_pStatus = nullptr;


	SphereCollider*			m_pCollider = nullptr;

	ZED_INFO				m_tZedStatus;
	bool					m_bDeath = false;

	NaviMesh*				m_pNaviMesh = nullptr;

	//For Player
	GameObject*				m_pPlayer = nullptr;
	Vector3					m_vDirection;
	float					m_fDistance;

};
#endif //_ZED_H_