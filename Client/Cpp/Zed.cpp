#include "stdafx.h"
#include "..\Header\Zed.h"
#include "StateController.h"
#include "AnimationController.h"
#include "BulletManager.h"


Zed::Zed(Desc * _desc)
{

	m_tZedStatus = _desc->tZed_Status;
	m_pNaviMesh = _desc->pNaviMesh;

}

Zed::~Zed()
{
}

void Zed::Initialize()
{
	m_pTarget = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);

	m_fLookOffset = (rand()%10 +1) / 100.f;
}

void Zed::Update()
{

	Setting_Components();
	
	if (!m_bEnding)
	{
		m_vDirection = m_pTarget->Get_Position() - m_Transform->Get_Position();
		m_fDistance = D3DXVec3Length(&m_vDirection);

		DEBUG_LOG(L"Zed to player Distance : " + to_wstring(m_fDistance));


		LookAt();
	}
	else
	{
		m_vDirection = m_vEndingPos - m_Transform->Get_Position();
		m_fDistance = D3DXVec3Length(&m_vDirection);

		m_Transform->LookAt(m_vEndingPos, 50.f, m_fLookOffset);
	}

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
	if (!m_bDeath && !m_bDontLook)
	{
		Vector3 PlayerPos = m_pTarget->Get_Position();
		PlayerPos.y = 0;
		m_Transform->LookAt(PlayerPos, 50.f, m_fLookOffset);
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

	int	iRand = rand() % 16;
	//24~32
	int Channel = rand() % 8 + 24;

	EngineFunction->OverlapPlay_Sound(L"All_Hit" + to_wstring(iRand) + L".wav", Channel);
	BulletManager::Get_Instance()->Create_Blood(m_Transform->Get_Position());

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

//void Zed::Change_Target(Vector3 Pos)
//{
//}

ZED_INFO Zed::Get_ZedInfo()
{
	return m_tZedStatus;
}

float Zed::Get_Distance()
{
	return m_fDistance;
}

NaviMesh * Zed::Get_NaviMesh()
{
	return m_pNaviMesh;
}

bool Zed::Get_DontLook()
{
	return m_bDontLook;
}

void Zed::Set_NaviMesh(NaviMesh * _pNaviMesh)
{
	m_pNaviMesh = _pNaviMesh;
}

void Zed::Set_DontLook(bool _falseIsDontLook)
{
	m_bDontLook = _falseIsDontLook;
}

void Zed::Setting_Ending(const Vector3& _vPos)
{
	if(!m_bEnding)
	{
		m_bEnding = true;
	
		Vector3 Pos = _vPos;
		Pos.y = 20.f;
		m_vEndingPos = Pos;
	}
}
