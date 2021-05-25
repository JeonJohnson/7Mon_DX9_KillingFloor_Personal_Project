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
#include "ShopManager.h"
#include "Player_Status.h"
#include "StageManager.h"


Player_Attack::Player_Attack(Desc * _desc)
{
//Beretta
	GameObject* Beretta = WeaponManager::Get_Instance()->Get_CloneWeapon(L"Beretta");
	assert(L"Beretta has't exist WeaponManager" && Beretta);
	m_arrWeapons[WEAPON_PRIORITY::Weapon_Secondary].emplace_back(Beretta);
	
	//Knife
	GameObject* Knife = WeaponManager::Get_Instance()->Get_CloneWeapon(L"Knife");
	assert(L"Knife has't exist WeaponManager" && Knife);
	m_arrWeapons[Weapon_Melee].emplace_back(Knife);
		
	//Heal
	GameObject* Injector = WeaponManager::Get_Instance()->Get_ProtoWeapon(L"Injector");
	assert(L"Injector has't exist WeaponManager" && Injector);
	m_pHealInjector = Injector;
	//m_arrWeapons[Weapon_Special].emplace_back(Injector);
	m_pHealInjector_Status = m_pHealInjector->Get_Component<Weapon_Status>();

	//Bomb
	GameObject* Bomb = WeaponManager::Get_Instance()->Get_ProtoWeapon(L"PipeBomb");
	assert(L"Bomb has't exist WeaponManager" && Bomb);
	m_pBomb = Bomb;
	m_arrWeapons[Weapon_Special].emplace_back(Bomb);
	m_pBomb_Status = m_pBomb->Get_Component<Weapon_Status>();

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

	
	Shop_ItempSetting();
	ShopManager::Get_Instance()->Create_ItemUI();
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
	m_pPlayerStatus = m_GameObject->Get_Component<Player_Status>();

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

	if (StageManager::Get_Instance()->Get_CurStageName() != STAGE_ENDING)
	{
		if (ShopManager::Get_Instance()->Get_ShopOn() == false)
		{
			if (m_pStateCtlr->Get_CurStateName() != L"Player_Heal"
				&& m_pStateCtlr->Get_CurStateName() != L"Player_Bomb")
			{
				Swap();
				Reload();
				Fire();
				IronSight();
				Bomb_Drop();
			}
			Heal();

			DEBUG_LOG(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
			DEBUG_LOG(to_wstring(m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet)
				+ L" / " + to_wstring(m_pCurWeaponStatus->m_tWeaponInfo.m_iMaxBullet));
			DEBUG_LOG(L"Anim Spd : " + to_wstring(m_pWeaponAnim->Get_AnimSpd()));

			HudManager::Get_Instance()->Set_TextWeaponName(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
			HudManager::Get_Instance()->Set_TextBullet(m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet);
			HudManager::Get_Instance()->Set_TextMagazine(m_pCurWeaponStatus->m_tWeaponInfo.m_iCurMagazine);

			HudManager::Get_Instance()->Set_TextHeal(m_pHealInjector_Status->m_tWeaponInfo.m_iCurBullet);

			HudManager::Get_Instance()->Set_TextGranade(m_pBomb_Status->m_tWeaponInfo.m_iCurMagazine);
		}
	}
	else { //m_pWeaponRenderer->Set_MeshScale(Vector3(0.1f, 0.1f, 0.1f)); 
	}
	

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
	if (MouseDown(KEY_STATE_RMouse)
		&& m_pStateCtlr->Get_CurStateName() != L"Player_Reload"
		&& m_pCurWeaponStatus->m_tWeaponInfo.m_eType != WEAPON_TYPE::Weapon_Knife)
	{
		m_bIronSight ^= true;
	}

	//float fSpd = fTime * 15.f;

	if (!m_bIronSight)
	{//견착 상태
		//Vector 2.5f, 0.f, 0.5f
		
		if (m_fIronSpdX <= 2.5f)
		{
			m_fIronSpdX += fTime * 15.f;
		}
		
		if(m_fIronSpdX > 2.5f) 
		{ m_fIronSpdX = 2.5f; }

		if (m_fIronSpdZ <= 0.5f)
		{
			m_fIronSpdZ += fTime * 15.f;
		}
		
		if(m_fIronSpdZ > 0.5f) 
		{ m_fIronSpdZ = 0.5f; }

		m_pWeaponRenderer->Set_MeshPos(Vector3(m_fIronSpdX, 0.f, m_fIronSpdZ));

		//Vector3 MeshPos = m_pWeaponRenderer->Get_MeshPos();
		
		//if (m_pWeaponRenderer->Get_MeshPos().x <= 0.f)
		//{
		//	m_pWeaponRenderer->Set_MeshPosX(0.f);
		//}

		//if (m_pWeaponRenderer->Get_MeshPos().z >= 0.5f)
		//{
		//	m_pWeaponRenderer->Set_MeshPosZ(0.5f);
		//}
	}
	else 
	{//정조준 상태
		//vector 0.f,0.f,-2.5f

		if (m_fIronSpdX >= 0.f)
		{
			m_fIronSpdX -= fTime * 15.f;
		}
		if(m_fIronSpdX < 0.f)
		{ m_fIronSpdX = 0.f; }

		if (m_fIronSpdZ >= -2.5f)
		{
			m_fIronSpdZ -= fTime * 15.f;
		}
		if (m_fIronSpdZ < -2.5f)
		{
			m_fIronSpdZ = -2.5f;
		}

		m_pWeaponRenderer->Set_MeshPos(Vector3(m_fIronSpdX, 0.f, m_fIronSpdZ));

		//m_pWeaponRenderer->Add_MeshPos(Vector3(fSpd, 0.f, -fSpd));

		//if (m_pWeaponRenderer->Get_MeshPos().x >= 2.5f)
		//{
		//	m_pWeaponRenderer->Set_MeshPosX(2.5f);
		//}

		//if (m_pWeaponRenderer->Get_MeshPos().z  <= -5.f)
		//{
		//	m_pWeaponRenderer->Set_MeshPosZ(-5.f);
		//}
	}
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
		m_pWeaponAnim->Set_AnimSpd(1.f);

		m_pStateCtlr->Set_State(L"Player_Swap");

		//m_pWeaponAnim->Play(1);

		m_iCurWeaponKind = m_iNewWeaponKind;
		m_bIronSight = false;

		return;
	}
	else
	{//같으면 저 거 같은 인덱스의 무기들중 지금말고 다음꺼 고를 수 있게.
	 //없음말고 ㅋㅋ;

		int arrSize = (int)m_arrWeapons[m_iNewWeaponKind].size();

		if (m_arrWeapons[m_iNewWeaponKind].size() <= 1)
		{
			return;
		}

		++m_iCurKindIndex;

		if (m_arrWeapons[m_iNewWeaponKind].size() <= m_iCurKindIndex)
		{
			m_iCurKindIndex -= arrSize;
			
			if (m_iCurKindIndex <= 0)
			{
				m_iCurKindIndex = 0;
			}
		}

		Set_CurWeapon(m_arrWeapons[m_iNewWeaponKind][m_iCurKindIndex]);

		m_pWeaponRenderer->Set_Mesh(m_pCurWeaponStatus->m_tWeaponInfo.m_szName);
		m_pWeaponAnim->SetUp_AnimCtrl();
		m_pWeaponAnim->Set_AnimSpd(1.f);

		m_pStateCtlr->Set_State(L"Player_Swap");

		//m_pWeaponAnim->Play(1);

		m_iCurWeaponKind = m_iNewWeaponKind;
		m_bIronSight = false;
	}

}

void Player_Attack::Heal()
{
	if (KeyDown(KEY_STATE_Q) && m_pStateCtlr->Get_CurStateName() != L"Player_Bomb")
	{
		if (m_pPlayerStatus->Get_PlayerStatus().m_iCurHp < 100
			&& m_pHealInjector_Status->m_tWeaponInfo.m_iCurBullet == 100)
		{
			m_pHealInjector_Status->m_tWeaponInfo.m_iCurBullet = 0;
			m_pStateCtlr->Set_State(L"Player_Heal");

		}
	}

	if (m_pHealInjector_Status->m_tWeaponInfo.m_iCurBullet < 100)
	{
		m_fHealTime += fTime * 12.5f;

		if (m_fHealTime >= 1.f)
		{
			++m_pHealInjector_Status->m_tWeaponInfo.m_iCurBullet;
			m_fHealTime = 0.f;
		}
		
	}
	else { m_pHealInjector_Status->m_tWeaponInfo.m_iCurBullet = 100; }

}

void Player_Attack::Bomb_Drop()
{
	if(KeyDown(KEY_STATE_G))
	{
		if (m_pBomb_Status->m_tWeaponInfo.m_iCurMagazine > 0)
		{
			
			m_pStateCtlr->Set_State(L"Player_Bomb");
		}
	}
}

void Player_Attack::Drop()
{
}

void Player_Attack::SetUp()
{
}

void Player_Attack::Player_Ending()
{
	m_bEnding = true;
	//m_pWeaponRenderer->Set_MeshRot(Vector3(0.f, 90.f, 0.f));
	m_pWeaponRenderer->Set_MeshScale(Vector3(0.f, 0.f, 0.f));
}

void Player_Attack::Shop_ItempSetting()
{
	for (int i = 0; i < WEAPON_PRIORITY::Weapon_Priority_End; ++i)
	{
		for (auto& weapon : m_arrWeapons[i])
		{
			ShopManager::Get_Instance()->Insert_HaveWeapon(weapon->Get_Component<Weapon_Status>());
		}
	}


}

void Player_Attack::All_Ammo()
{
	for (int i = 0; i < WEAPON_PRIORITY::Weapon_Priority_End; ++i)
	{
		for (auto& weapon : m_arrWeapons[i])
		{
			Weapon_Status* temp = weapon->Get_Component<Weapon_Status>();

			temp->m_tWeaponInfo.m_iCurMagazine = temp->m_tWeaponInfo.m_iMaxMagazine;

			//ShopManager::Get_Instance()->Insert_HaveWeapon(weapon->Get_Component<Weapon_Status>());
		}
	}
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

GameObject * Player_Attack::Get_HealInjector()
{
	return m_pHealInjector;
}

Weapon_Status * Player_Attack::Get_HealInjector_Status()
{
	return m_pHealInjector_Status;
}

GameObject * Player_Attack::Get_PipeBomb()
{
	return m_pBomb;
}

Weapon_Status * Player_Attack::Get_PipeBomb_Status()
{
	return m_pBomb_Status;
}

bool Player_Attack::Get_IronSight()
{
	return m_bIronSight;
}

void Player_Attack::Set_CurWeapon(GameObject * _pWeapon)
{
	m_pCurWeapon = _pWeapon;
	m_pCurWeaponStatus = _pWeapon->Get_Component<Weapon_Status>();
}

void Player_Attack::Set_IronSight(bool _OnOff)
{
	m_bIronSight = _OnOff;
}

void Player_Attack::On_IronSight()
{
	m_bIronSight = true;
	m_fIronSpdX = 0.f;
	m_fIronSpdZ = -2.5f;
	//m_pWeaponRenderer->Set_MeshPos(Vector3(0.f, 0.f, -2.5f));
}


