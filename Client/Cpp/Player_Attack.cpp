#include "stdafx.h"

#include "..\Header\Player_Attack.h"
#include "StateController.h"
#include "AnimationController.h"

//#include "Weapon.h"
#include "WeaponManager.h"
#include "Weapon_Status.h"
#include "Mesh_Renderer.h"

#include "HudManager.h"
#include "SphereCollider.h"


Player_Attack::Player_Attack(Desc * _desc)
{
//Beretta
	GameObject* Beretta = WeaponManager::Get_Instance()->Get_CloneWeapon(L"Beretta");
	assert(L"Beretta has't exist WeaponManager" && Beretta);

	m_arrWeapons[1].emplace_back(Beretta);
	
	//Knife
	GameObject* Knife = WeaponManager::Get_Instance()->Get_CloneWeapon(L"Knife");
	assert(L"Knife has't exist WeaponManager" && Knife);

	m_arrWeapons[2].emplace_back(Knife);
		
	if (_desc->szInitWeapon == L"")
	{
		m_iNewWeaponKind = 1;
		m_pCurWeapon = Beretta;
	}
	else 
	{
		GameObject* PrimaryWeapon = WeaponManager::Get_Instance()->Get_CloneWeapon(_desc->szInitWeapon);
		m_arrWeapons[0].emplace_back(PrimaryWeapon);
		m_iNewWeaponKind = 0;
		m_pCurWeapon = PrimaryWeapon;

		GameObject* PrimaryWeapon2 = WeaponManager::Get_Instance()->Get_CloneWeapon(L"ShotGun");
		m_arrWeapons[WEAPON_PRIORITY::Weapon_Primary].emplace_back(PrimaryWeapon2);
		//m_iNewWeaponKind = 0;
		//m_pCurWeapon = PrimaryWeapon;


	
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

	ChangeWeapon();
}

void Player_Attack::Update()
{

	Swap();
	Reload();
	Fire();

	DEBUG_LOG(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
	DEBUG_LOG(to_wstring(m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet) 
		+ L" / " + to_wstring(m_pCurWeaponStatus->m_tWeaponInfo.m_iMaxBullet));

	HudManager::Get_Instance()->Set_TextWeaponName(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
	HudManager::Get_Instance()->Set_TextBullet(m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet);
	HudManager::Get_Instance()->Set_TextMagazine(m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine);
	HudManager::Get_Instance()->Set_TextGranade(3);
	

	//if (KeyDown(KEY_STATE_F1))
	//{
	//	GameObject* TestClot = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" + to_wstring(m_iTest));
	//	TestClot->Set_Position(Vector3(m_iTest * 30.f, 0.f, 100.f));
	//	TestClot->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));

	//	Mesh_Renderer::Desc Clot_Test;
	//	Clot_Test.szMeshName = L"Clot";
	//	TestClot->Add_Component<Mesh_Renderer>(&Clot_Test);

	//	AnimationController::Desc Clot_Anim;
	//	Clot_Anim.InitIndex = 3;
	//	Clot_Anim.bLoop = true;
	//	Clot_Anim.bClone = true;
	//	TestClot->Add_Component<AnimationController>(&Clot_Anim);

	//	SphereCollider::Desc Clot_Col;
	//	Clot_Col.fRadius = 12.5f;
	//	Clot_Col.vOffset = Vector3(0.f, 15.f, 0.f);
	//	Clot_Col.szColName = L"Clot_Body";
	//	TestClot->Add_Component<SphereCollider>(&Clot_Col);

	//	++m_iTest;
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
	if (MouseDown(KEY_STATE_LMouse)
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Reload"
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Fire"
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Swap")
	{

		if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType != Weapon_Knife)
		{
			if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet <= 0)
			{
				m_pStateCtlr->Set_State(L"Player_Reload");
				return;
			}
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
	if (m_pStateCtlr->Get_CurStateName() != L"Player_Swap")
	{
		if (KeyDown(KEY_STATE_1))
		{
			m_iNewWeaponKind = 0;
			ChangeWeapon();
		}
		if (KeyDown(KEY_STATE_2))
		{
			m_iNewWeaponKind = 1;
			ChangeWeapon();
		}
		if (KeyDown(KEY_STATE_3))
		{
			m_iNewWeaponKind = 2;
			ChangeWeapon();
		}

		//if (m_iCurWeaponKind != m_iNewWeaponKind)
		//{
		//	if (m_arrWeapons[m_iNewWeaponKind].size() <= 0)
		//	{
		//		return;
		//	}

		//	Set_CurWeapon(m_arrWeapons[m_iNewWeaponKind].front());

		//	m_pWeaponRenderer->Set_Mesh(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
		//	m_pWeaponAnim->SetUp_AnimCtrl();

		//	m_pStateCtlr->Set_State(L"Player_Swap");

		//	//m_pWeaponAnim->Play(1);

		//	m_iCurWeaponKind = m_iNewWeaponKind;

		//	return;
		//}
		//else
		//{//같으면 저 거 같은 인덱스의 무기들중 지금말고 다음꺼 고를 수 있게.
		//	//없음말고 ㅋㅋ;
		//	if (m_arrWeapons[m_iNewWeaponKind].size() >= m_iCurKindIndex)
		//	{
		//		--m_iCurKindIndex;
		//		if (m_iCurKindIndex < 0)
		//		{
		//			m_iCurKindIndex == 0;
		//		}
		//	}
		//	else {
		//		++m_iCurKindIndex;
		//	}

		//	Set_CurWeapon(m_arrWeapons[m_iNewWeaponKind][m_iCurKindIndex]);

		//	m_pWeaponRenderer->Set_Mesh(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
		//	m_pWeaponAnim->SetUp_AnimCtrl();

		//	m_pStateCtlr->Set_State(L"Player_Swap");

		//	//m_pWeaponAnim->Play(1);

		//	m_iCurWeaponKind = m_iNewWeaponKind;
		//	
		//}

	}

}

void Player_Attack::ChangeWeapon()
{
	if (m_iCurWeaponKind != m_iNewWeaponKind)
	{
		if (m_arrWeapons[m_iNewWeaponKind].size() <= 0)
		{
			return;
		}

		Set_CurWeapon(m_arrWeapons[m_iNewWeaponKind].front());

		m_pWeaponRenderer->Set_Mesh(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
		m_pWeaponAnim->SetUp_AnimCtrl();

		m_pStateCtlr->Set_State(L"Player_Swap");

		//m_pWeaponAnim->Play(1);

		m_iCurWeaponKind = m_iNewWeaponKind;

		return;
	}
	else
	{//같으면 저 거 같은 인덱스의 무기들중 지금말고 다음꺼 고를 수 있게.
	 //없음말고 ㅋㅋ;

		if (m_arrWeapons[m_iNewWeaponKind].size() <= 1)
		{
			return;
		}

		if (m_arrWeapons[m_iNewWeaponKind].size() <= m_iCurKindIndex)
		{
			m_iCurKindIndex -= 1;
			
			if (m_iCurKindIndex <= 0)
			{
				m_iCurKindIndex = 0;
			}
		}
		else 
		{
			++m_iCurKindIndex;
		}

		Set_CurWeapon(m_arrWeapons[m_iNewWeaponKind][m_iCurKindIndex]);

		m_pWeaponRenderer->Set_Mesh(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
		m_pWeaponAnim->SetUp_AnimCtrl();

		m_pStateCtlr->Set_State(L"Player_Swap");

		//m_pWeaponAnim->Play(1);

		m_iCurWeaponKind = m_iNewWeaponKind;

	}
}

void Player_Attack::Drop()
{
}

void Player_Attack::SetUp()
{
}

GameObject * Player_Attack::Get_CurWeapon()
{
	return m_pCurWeapon;
}

Weapon_Status * Player_Attack::Get_CurWeaponStatus()
{
	return m_pCurWeaponStatus;
}

Mesh_Renderer * Player_Attack::Get_Renderer()
{
	return m_pWeaponRenderer;
}


AnimationController * Player_Attack::Get_AnimCtrl()
{
	return m_pWeaponAnim;
}

int Player_Attack::Get_iCurKind()
{
	return m_iCurWeaponKind;
}

vector<GameObject*>* Player_Attack::Get_WeaponsArr()
{
	return m_arrWeapons;
}

void Player_Attack::Set_CurWeapon(GameObject * _pWeapon)
{
	m_pCurWeapon = _pWeapon;
	m_pCurWeaponStatus = _pWeapon->Get_Component<Weapon_Status>();
}


