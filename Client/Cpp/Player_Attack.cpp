#include "stdafx.h"

#include "..\Header\Player_Attack.h"
#include "StateController.h"
#include "AnimationController.h"

#include "Weapon.h"
#include "WeaponManager.h"
#include "Mesh_Renderer.h"


Player_Attack::Player_Attack(Desc * _desc)
{
//Beretta
	Weapon* Beretta = WeaponManager::Get_Instance()->Get_CloneWeapon(L"Beretta");
	assert(L"Beretta has't exist WeaponManager" && Beretta);

	m_arrWeapons[1].emplace_back(Beretta);
	
	//Knife
	Weapon* Knife = WeaponManager::Get_Instance()->Get_CloneWeapon(L"Knife");
	assert(L"Knife has't exist WeaponManager" && Knife);

	m_arrWeapons[2].emplace_back(Knife);
		
	if (_desc->szInitWeapon == L"")
	{
		m_iNewWeaponIndex = 1;
		m_pCurWeapon = Beretta;
	}
	else 
	{
		Weapon* PrimaryWeapon = WeaponManager::Get_Instance()->Get_CloneWeapon(_desc->szInitWeapon);
		m_arrWeapons[0].emplace_back(PrimaryWeapon);
		m_iNewWeaponIndex = 0;
		m_pCurWeapon = PrimaryWeapon;
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
	if (MouseDown(KEY_STATE_LMouse)
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Reload"
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Fire"
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Swap")
	{
		if (m_pCurWeapon->m_iCurBullet <= 0)
		{
			m_pStateCtlr->Set_State(L"Player_Reload");
			return;
		}
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
		if (m_arrWeapons[m_iNewWeaponIndex].size() <= 0)
		{
			return;
		}

		

		//if (m_pStateCtlr->Get_CurStateName() != Fire);
	
		m_pCurWeapon = m_arrWeapons[m_iNewWeaponIndex].front();

		m_pWeaponRenderer->Set_Mesh(m_pCurWeapon->m_szName);
		m_pWeaponAnim->SetUp_AnimCtrl();

		m_pStateCtlr->Set_State(L"Player_Swap");
		
		//m_pWeaponAnim->Play(1);

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

int Player_Attack::Get_iCurIndex()
{
	return m_iCurWeaponIndex;
}

vector<Weapon*>* Player_Attack::Get_WeaponsArr()
{
	return m_arrWeapons;
}

void Player_Attack::Set_CurWeapon(Weapon * _pWeapon)
{
	m_pCurWeapon = _pWeapon;
}


