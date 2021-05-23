#include "stdafx.h"
#include "..\Header\Player_Fire.h"
#include "AnimationController.h"
#include "StateController.h"
#include "Player_Attack.h"

#include "SphereCollider.h"
#include "Bullet_Move.h"
#include "Mesh_Renderer.h"

#include "Weapon_Status.h"
#include "VIBuffer_Renderer.h"

#include "HudManager.h"
#include "Zed.h"
#include "BulletManager.h"

#include "Camera_FPS.h"

Player_Fire::Player_Fire()
{
}


Player_Fire::~Player_Fire()
{
}

void Player_Fire::Initialize()
{
}

void Player_Fire::EnterState()
{
	//m_pCurWeapon = m_GameObject->Get_Component<Player_Attack>()->Get_CurWeapon();
	
	if (m_pPlayerAttack == nullptr)
	{
		m_pPlayerAttack = m_GameObject->Get_Component<Player_Attack>();
	}

	m_pCurWeaponStatus = m_pPlayerAttack->Get_CurWeaponStatus();

	if (m_pPlayerCol == nullptr)
	{
		m_pPlayerCol = m_GameObject->Get_Component<SphereCollider>();
	}

	if (m_pCamera == nullptr)
	{
		m_pCamera = m_GameObject->Get_Component<Camera_FPS>();
	}



	if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType != Weapon_Knife)
	{
		m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet -= 1;

		m_GameObject->Get_Component<AnimationController>()->Play(3);
		
		BulletManager::Get_Instance()->Create_Bullet(
			m_GameObject,
			m_pCurWeaponStatus->m_tWeaponInfo,
			m_pCurWeaponStatus->m_tWeaponInfo.m_iBuck);
		BulletManager::Get_Instance()->Create_Muzzle(m_GameObject,m_pPlayerAttack->Get_Renderer()->Get_Mesh(), m_pCurWeaponStatus->m_tWeaponInfo);
		
		m_pCamera->Recoil(m_pCurWeaponStatus->m_tWeaponInfo.m_fRecoilForce);
		//Bullet_Test();
		//m_pCurWeapon->m_fCurRapid = m_pCurWeapon->m_fMaxRapid;

		m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid = 0.f;
	}
	else 
	{
		m_pPlayerCol->Set_Check(true);
		m_GameObject->Get_Component<AnimationController>()->Play(3);
	}

	if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType == Weapon_Shotgun)
	{
		m_bIronSight = m_pPlayerAttack->Get_IronSight();
		m_pPlayerAttack->Set_IronSight(false);
	}

}

void Player_Fire::UpdateState()
{

	DEBUG_LOG(L"Player Cur State : Fire");
	DEBUG_LOG(L"Cur : " + to_wstring(m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid)
		+ L" / Max : " + to_wstring(m_pCurWeaponStatus->m_tWeaponInfo.m_fMaxRapid));
	
	if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType != Weapon_Knife)
	{
		m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid += fTime;

		if (m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid
			>= m_pCurWeaponStatus->m_tWeaponInfo.m_fMaxRapid)
		{
			if (m_pCurWeaponStatus->m_tWeaponInfo.m_bAuto)
			{
				if (MousePress(KEY_STATE_LMouse))
				{
					if (m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet <= 0)
					{
						m_pStateController->Set_State(L"Player_Reload");
						return;
					}
					m_pCurWeaponStatus->m_tWeaponInfo.m_iCurBullet -= 1;
					m_GameObject->Get_Component<AnimationController>()->Play(3);
					
					m_pCamera->Recoil(m_pCurWeaponStatus->m_tWeaponInfo.m_fRecoilForce);
					BulletManager::Get_Instance()->Create_Bullet(m_GameObject, m_pCurWeaponStatus->m_tWeaponInfo);
					BulletManager::Get_Instance()->Create_Muzzle(m_GameObject, m_pPlayerAttack->Get_Renderer()->Get_Mesh(), m_pCurWeaponStatus->m_tWeaponInfo);
					
					//Bullet_Test();
					
					m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid = 0.f;
				}
			}
		}
	}
	else 
	{
		auto pZeds = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_ZED);


		for (auto& zed : pZeds)
		{
			if (m_pPlayerCol->Collision_Check(zed, L"Body"))
			{
				if (auto pStatus = zed->Get_Component<Zed>())
				{
					pStatus->Damaged(m_pCurWeaponStatus->m_tWeaponInfo.m_iDmg);
				}
				m_pPlayerCol->Set_Check(false);

				return;
			}
		}
	}


	
	if (m_GameObject->Get_Component<AnimationController>()->IsEnd()
		|| m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid >= m_pCurWeaponStatus->m_tWeaponInfo.m_fMaxRapid)
	{
		m_pCurWeaponStatus->m_tWeaponInfo.m_fCurRapid = 0.f;
		m_pStateController->Set_State(L"Player_Idle");

		if (m_pCurWeaponStatus->m_tWeaponInfo.m_eType == Weapon_Shotgun)
		{
			//if (m_bIronSight)
			//{
			//	m_pPlayerAttack->On_IronSight();
			//}
		}
	}
}

void Player_Fire::ExitState()
{
}



//void Player_Fire::Bullet_Test()
//{
//	GameObject* Bullet = INSTANTIATE(OBJECT_TAG_BULLET, L"TestBullet");
//	Vector3  vDir = m_Transform->Get_Position() /*+ m_Transform->Get_Forward()*50.f*/;
//	Bullet->Set_Position(vDir);
//	Bullet->Set_Rotation(m_Transform->Get_Rotation());
//
//	//Mesh_Renderer::Desc bulletRenderer;
//	//bulletRenderer.szMeshName = L"DebugSphere";
//	//Bullet->Add_Component<Mesh_Renderer>(&bulletRenderer);
//
//#ifdef _DEBUG
//	SphereCollider::Desc ColDesc;
//	ColDesc.fRadius = 0.5f;
//	ColDesc.szColName = L"bullet";
//	Bullet->Add_Component<SphereCollider>(&ColDesc);
//#endif //_DEBUG
//
//	//VIBuffer_Renderer::Desc BulletTrace_Desc;
//	//BulletTrace_Desc.wBufferName = L"Rect_Texture";
//	//BulletTrace_Desc.wTextureName = L"BulletTrace01"; 
//	//BulletTrace_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Alpha;
//	//Bullet->Add_Component<VIBuffer_Renderer>(&BulletTrace_Desc);
//
//	Bullet_Move::Desc bulletmove;
//	bulletmove.Spd = 2000.f;
//	bulletmove.Dmg = m_pCurWeaponStatus->m_tWeaponInfo.m_iDmg;
//	Bullet->Add_Component<Bullet_Move>(&bulletmove);
//
//
//}
