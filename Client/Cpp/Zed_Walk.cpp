#include "stdafx.h"
#include "..\Header\Zed_Walk.h"
#include "AnimationController.h"
#include "Zed.h"
#include "StateController.h"
#include "NaviMesh.h"

Zed_Walk::Zed_Walk()
{
}


Zed_Walk::~Zed_Walk()
{
}

void Zed_Walk::Initialize()
{
}

void Zed_Walk::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	if (m_pNaviMesh == nullptr)
	{
		m_pNaviMesh = m_pZedInfo->Get_NaviMesh();
	}

	if (m_pZedInfo->Get_ZedInfo().m_eName== 3)
	{
		m_iWalknimIndex = 2;
	}

	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iWalknimIndex)
	{	
		m_pAnimCtrl->Play(m_iWalknimIndex, true);
	}
}

void Zed_Walk::UpdateState()
{
	DEBUG_LOG(L"Zed : Walk");
	
	Vector3 vForward = m_Transform->Get_Forward();
	//m_Transform->Add_Position(vForward * fTime * m_pZedInfo->Get_ZedInfo().m_fWalkSpd);
	m_Transform->Add_Position(m_pNaviMesh->Add_Pos(m_Transform->Get_Position(), vForward * fTime * m_pZedInfo->Get_ZedInfo().m_fWalkSpd));
	
	 
	
	if (m_GameObject->Get_Component<Zed>()->Get_Distance() <= 30.f)
	{
		m_pStateController->Set_State(L"Zed_Att");
	}

}

void Zed_Walk::ExitState()
{
}
