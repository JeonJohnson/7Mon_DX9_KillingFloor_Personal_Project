#include "stdafx.h"
#include "..\Header\Zed_Run.h"
#include "StateController.h"
#include "AnimationController.h"
#include "Zed.h"

Zed_Run::Zed_Run()
{
}


Zed_Run::~Zed_Run()
{
}

void Zed_Run::Initialize()
{
}

void Zed_Run::EnterState()
{
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}

	

	if (m_pZedInfo->Get_ZedInfo().m_eName == 0)
	{
		m_iRunIndex = 1;
	}

	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iRunIndex)
	{
		m_pAnimCtrl->Play(m_iRunIndex, true);
	}

	m_fRunCurTime = 0.f;
	m_fRunFullTime = (rand() % 6) + 1.5f;
}

void Zed_Run::UpdateState()
{
	DEBUG_LOG(L"Zed : Run");

	m_fRunCurTime += fTime;

	Vector3 vForward = m_Transform->Get_Forward();
	m_Transform->Add_Position(vForward * fTime * m_pZedInfo->Get_ZedInfo().m_fRunSpd);

	if (m_GameObject->Get_Component<Zed>()->Get_Distance() <= 30.f)
	{
		m_pStateController->Set_State(L"Zed_Att");
	}
	else 
	{
		if (m_fRunCurTime >= m_fRunFullTime)
		{
			m_pStateController->Set_State(L"Zed_Walk");
		}
	}


}

void Zed_Run::ExitState()
{
}
