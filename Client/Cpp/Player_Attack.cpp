#include "stdafx.h"

#include "..\Header\Player_Attack.h"
#include "StateController.h"
#include "AnimationController.h"

#include "Weapon.h"
#include "WeaponManager.h"
#include "Mesh_Renderer.h"


Player_Attack::Player_Attack(Desc * _desc)
{

	if (_desc->szInitPri != L"")
	{
		Weapon* temp = WeaponManager::Get_Instance()->Get_Weapon(_desc->szInitPri);
		if (temp)
		{
			m_arrWeapons[0].emplace_back(temp);
			m_iCurWeaponIndex = 1;
			m_pCurWeapon = temp;
		}
	}

	{
		Weapon* temp = WeaponManager::Get_Instance()->Get_Weapon(_desc->szInitSec);
		if (temp)
		{
			m_arrWeapons[1].emplace_back(temp);
		}
	}

	{
		Weapon*	temp = WeaponManager::Get_Instance()->Get_Weapon(L"Knife");
		if (temp)
		{
			m_arrWeapons[2].emplace_back(temp);
		}
	}


}

Player_Attack::~Player_Attack()
{
}

void Player_Attack::Initialize()
{

	m_pStateCtlr = m_GameObject->Get_NewComponent<StateController>();
	m_pWeaponRenderer = m_GameObject->Get_NewComponent<Mesh_Renderer>();
	// m_pWeaponRenderer->Set_Mesh(m_pCurWeapon->m_szName);
	m_pWeaponAnim = m_GameObject->Get_NewComponent<AnimationController>();
	//m_pWeaponAnim->SetUp_AnimCtrl();


	//Mesh_Renderer::Desc weaponMesh;
	//weaponMesh.szMeshName = m_pCurWeapon->m_szName;
	//m_GameObject->Add_Component<Mesh_Renderer>(&weaponMesh);

	//AnimationController::Desc Anim;
	//Anim.dAnimSpd = 1.0;
	//Anim.bLoop = false;
	//Anim.bPlay = true;
	//m_GameObject->Add_Component<AnimationController>(&Anim);

	//m_pWeaponRenderer = m_GameObject->Get_NewComponent<Mesh_Renderer>();
	//m_pWeaponAnim = m_GameObject->Get_NewComponent<AnimationController>();

}

void Player_Attack::Update()
{

	

	Swap();
	Reload();
	Fire();


	DEBUG_LOG(m_pCurWeapon->m_szName);
	DEBUG_LOG(to_wstring(m_pCurWeapon->m_iCurBullet) + L" / " + to_wstring(m_pCurWeapon->m_iMaxBullet));
	//if (m_pStateCtlr->Get_CurStateName() == L"Idle")
	//{
	//	Swap();
	//	Fire();	
	//}

	//if (m_pStateCtlr->Get_CurStateName() != L"Reload")
	//{
	//	IronSight();
	//}
}

void Player_Attack::LateUpdate()
{
}

void Player_Attack::ReadyRender()
{
}

void Player_Attack::Release()
{
}

void Player_Attack::Fire()
{
	//if (m_pCurWeapon->m_bAuto)
	//{
	//	if (MousePress(KEY_STATE_LMouse))
	//	{
	//		if (m_pCurWeapon->m_fCurRapid >= m_pCurWeapon->m_fMaxRapid)
	//		{
	//			m_pStateCtlr->Set_State(L"Player_Fire");
	//		}
	//	}

	//}
	//else 
	//{
	//	if (MouseDown(KEY_STATE_LMouse))
	//	{
	//		if (m_pCurWeapon->m_fCurRapid >= m_pCurWeapon->m_fMaxRapid)
	//		{
	//			m_pStateCtlr->Set_State(L"Player_Fire");
	//		}
	//	}
	//}

	if (MouseDown(KEY_STATE_LMouse))
	{
		m_pStateCtlr->Set_State(L"Player_Fire");
	}
}

void Player_Attack::IronSight()
{

}

void Player_Attack::Reload()
{
	if (KeyDown(KEY_STATE_R))
	{
		if (m_pStateCtlr->Get_CurStateName() != L"Player_Reload")
		{
			m_pStateCtlr->Set_State(L"Player_Reload");
	 	}
	}
}

void Player_Attack::Swap()
{
	if (KeyDown(KEY_STATE_1))
	{
		m_iNewWeaponIndex = 0;
	}
	if (KeyDown(KEY_STATE_2))
	{
		m_iNewWeaponIndex = 1;
	}
	if (KeyDown(KEY_STATE_3))
	{
		m_iNewWeaponIndex = 2;
	}

	if (m_iCurWeaponIndex != m_iNewWeaponIndex)
	{
		/*if(m_pStateCtlr->Get_CurStateName() != Fire)*/
		m_pCurWeapon = m_arrWeapons[m_iNewWeaponIndex].front();

		m_pWeaponRenderer->Set_Mesh(m_pCurWeapon->m_szName);
		m_pWeaponAnim->SetUp_AnimCtrl();

		m_pWeaponAnim->Play(1);

		m_iCurWeaponIndex = m_iNewWeaponIndex;
		
		return;
	}
	else 
	{//같으면 저 거 같은 인덱스의 무기들중 지금말고 다음꺼 고를 수 있게.
		//없음말고 ㅋㅋ;
	}

	

}

void Player_Attack::SetUp()
{
}

Weapon * Player_Attack::Get_CurWeapon()
{
	return m_pCurWeapon;
}

Mesh_Renderer * Player_Attack::Get_Renderer()
{
	return m_pWeaponRenderer;
}


AnimationController * Player_Attack::Get_AnimCtrl()
{
	return m_pWeaponAnim;
}


