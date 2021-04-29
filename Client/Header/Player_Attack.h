#pragma once
#ifndef _PLAYER_ATT_H_
#define _PLAYER_ATT_H_

#include "Component.h"

class Mesh_Renderer;
class Anim_Controller;

class Player_Attack : public Component
{
public:
	struct Desc
	{
		Mesh_Renderer*		pMeshRenderer = nullptr;
		//Mesh*				pPrimary = nullptr;
		//Mesh*				pSecondary = nullptr;
		//Mesh*				pMelee = nullptr;

		wstring				szPrimary = L"";
		wstring				szSecondary = L"";
		wstring				szMelee = L"";

		Anim_Controller*	pAnimCtrl = nullptr;

	};
public:
	explicit Player_Attack(Desc* _desc);
	virtual ~Player_Attack();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: //Functions
	bool	IronSight();
	bool	Shoot();
	bool	Reload();
	bool	Swap();

public:	//Get


public: //Set


private:
	Mesh_Renderer*		m_pWeapon_Mesh = nullptr;
	
	//Mesh*				m_arrWeapons[3] = { nullptr, nullptr, nullptr };
	wstring				m_arrWeapons[3] = { L"", L"", L"" };

	int					m_iNewWeaponIndex = 0;
	int					m_iCurWeaponIndex = -1;
	//int					m_iOldWeaponIndex = -1;

	Anim_Controller*	m_pWeaponAnim = nullptr;

};

#endif //_PLAYER_ATT_H_