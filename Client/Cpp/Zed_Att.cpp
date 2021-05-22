#include "stdafx.h"
#include "..\Header\Zed_Att.h"
#include "Zed.h"
#include "StateController.h"
#include "AnimationController.h"
#include "SphereCollider.h"
#include "Player_Status.h"
#include "ShakeObject.h"
#include "HudManager.h"


Zed_Att::Zed_Att()
{
}


Zed_Att::~Zed_Att()
{
}

void Zed_Att::Initialize()
{
}

void Zed_Att::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	if (m_pCol == nullptr)
	{
		m_pCol = m_GameObject->Get_Component<SphereCollider>();
	}

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);
	}

	
	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iAttAnimIndex)
	{
		m_pAnimCtrl->Play(m_iAttAnimIndex);
	}

	//m_fAttFrame = Function_Math::RandFloat(-0.5f, 0.5f);
}

void Zed_Att::UpdateState()
{
	DEBUG_LOG(L"Zed : Attack");

	float curFrame = (float)m_pAnimCtrl->Get_CurFrame();
	float maxFrame = (float)m_pAnimCtrl->Get_MaxFrame();

	if (curFrame >= maxFrame / 2.f + m_fAttFrame)
	{
		if (m_pCol->Collision_Check(m_pPlayer, L"Player"))
		{
			m_pPlayer->Get_Component<Player_Status>()->Damaged(m_pZedInfo->Get_ZedInfo().m_iDmg);
			m_pPlayer->Get_Component<ShakeObject>()->Shaking(0.5f, 10, 0.025f);
			HudManager::Get_Instance()->Hit_EffectOn();
			m_pCol->Set_Check(false);
		}
	}

	if (m_pAnimCtrl->IsEnd())
	{
		m_pCol->Set_Check(true);
		m_pStateController->Set_State(L"Zed_Idle");
	}
}

void Zed_Att::ExitState()
{
}
