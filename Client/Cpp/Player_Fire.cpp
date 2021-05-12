#include "stdafx.h"
#include "..\Header\Player_Fire.h"
#include "AnimationController.h"
#include "StateController.h"
#include "Player_Attack.h"
#include "Weapon.h"
#include "..\..\Engine\Header\SphereCollider.h"
#include "Bullet_Move.h"

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
	m_pCurWeapon = m_GameObject->Get_Component<Player_Attack>()->Get_CurWeapon();
	

	m_GameObject->Get_Component<AnimationController>()->Play(3);
	Bullet_Test();
	//m_pCurWeapon->m_fCurRapid = m_pCurWeapon->m_fMaxRapid;
	m_pCurWeapon->m_fCurRapid = 0.f;
}

void Player_Fire::UpdateState()
{

	DEBUG_LOG(L"Player Cur State : Fire");
	DEBUG_LOG(L"Cur : " + to_wstring(m_pCurWeapon->m_fCurRapid)
		+ L" / Max : " + to_wstring(m_pCurWeapon->m_fMaxRapid));
	


	m_pCurWeapon->m_fCurRapid += fTime;

	if (m_pCurWeapon->m_fCurRapid >= m_pCurWeapon->m_fMaxRapid)
	{
		if (m_pCurWeapon->m_bAuto)
		{
			if (MousePress(KEY_STATE_LMouse))
			{
				m_GameObject->Get_Component<AnimationController>()->Play(3);
				Bullet_Test();
				m_pCurWeapon->m_fCurRapid = 0.f;
			}
		}
		//else
		//{
		//	if (MouseDown(KEY_STATE_LMouse))
		//	{
		//		m_GameObject->Get_Component<AnimationController>()->Play(3);
		//		m_pCurWeapon->m_fCurRapid = 0.f;
		//	}
		//}

		
	}


	
	if (m_GameObject->Get_Component<AnimationController>()->IsEnd()
		|| m_pCurWeapon->m_fCurRapid >= m_pCurWeapon->m_fMaxRapid)
	{
		m_pCurWeapon->m_fCurRapid = 0.f;
		m_pStateController->Set_State(L"Player_Idle");
	}
}

void Player_Fire::ExitState()
{
}

void Player_Fire::Bullet_Test()
{
	GameObject* Bullet = INSTANTIATE(OBJECT_TAG_DEFAULT, L"TestBullet");
	Vector3  vDir = m_Transform->Get_Position()/* + m_Transform->Get_Forward()*15.f*/;

	Bullet->Set_Position(vDir);
	Bullet->Set_Rotation(m_Transform->Get_Rotation());

	SphereCollider::Desc ColDesc;
	ColDesc.fRadius = 0.5f;
	ColDesc.szColName = L"bullet";
	Bullet->Add_Component<SphereCollider>(&ColDesc);

	Bullet_Move::Desc bulletmove;
	bulletmove.Spd = 2000.f;
	Bullet->Add_Component<Bullet_Move>(&bulletmove);
}
