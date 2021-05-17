#include "stdafx.h"
#include "..\Header\Zed.h"
#include "StateController.h"
#include "AnimationController.h"


Zed::Zed(Desc * _desc)
{

	m_tZedStatus = _desc->tZed_Status;


}

Zed::~Zed()
{
}

void Zed::Initialize()
{
	m_pPlayer = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);
}

void Zed::Update()
{

	Setting_Components();

	m_vDirection = m_pPlayer->Get_Position() - m_Transform->Get_Position();
	m_fDistance = D3DXVec3Length(&m_vDirection);

	DEBUG_LOG(L"Zed to player Distance : " + to_wstring(m_fDistance));

	LookAt();

	//if (m_fDistance > 30.f)
	//{		
	//	Walk();
	//}
	//else 
	//{
	//	Attack();
	//}
	//
	
	DEBUG_LOG(L"HP : " + to_wstring(m_tZedStatus.m_iCurHp) + L"/" + to_wstring(m_tZedStatus.m_iMaxHp));
}

void Zed::LateUpdate()
{
}

void Zed::ReadyRender()
{
}

void Zed::Release()
{
}

void Zed::Setting_Components()
{
	if (!m_pStateCtrl)
	{
		m_pStateCtrl = m_GameObject->Get_Component<StateController>();
	}

	if (!m_pAnimCtrl)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}
	
	//if (!m_pStatus)
	//{
	//	m_pStatus = m_GameObject->Get_Component<Zed_Status>();
	//}

}

void Zed::LookAt()
{
	if (!m_bDeath)
	{
		Vector3 PlayerPos = m_pPlayer->Get_Position();
		PlayerPos.y = 0;
		m_Transform->LookAt(PlayerPos, 50.f);
	}

	//m_Transform->RotateAxis(Vector3(0, 1, 0), fTime);

}

void Zed::Walk()
{
	m_pStateCtrl->Set_State(L"Zed_Walk");
	//Vector3 vForward = m_Transform->Get_Forward();
	//m_Transform->Add_Position(vForward * fTime * m_tZedStatus.m_fWalkSpd);
}

void Zed::Run()
{
	m_pStateCtrl->Set_State(L"Zed_Run");
}

//void Zed::Death()
//{
//	
//}

void Zed::Attack()
{
	m_pStateCtrl->Set_State(L"Zed_Att");

}

void Zed::Damaged(int _iDmg)
{
	m_tZedStatus.m_iCurHp -= _iDmg;

	if (m_tZedStatus.m_iCurHp <= 0)
	{
		m_tZedStatus.m_iCurHp = 0;

		if (m_pStateCtrl->Get_CurStateName() != L"Zed_Death")
		{
			m_bDeath = true;
			m_pStateCtrl->Set_State(L"Zed_Death");
		}
	}
	else 
	{
		m_pStateCtrl->Set_State(L"Zed_Hit");
	}

}

ZED_INFO Zed::Get_ZedInfo()
{
	return m_tZedStatus;
}

float Zed::Get_Distance()
{
	return m_fDistance;
}
