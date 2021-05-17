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
}

void Zed::Update()
{
	Setting_Components();


	
	
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
}

void Zed::Walk()
{
}

void Zed::Run()
{

}

void Zed::Death()
{
	
}

void Zed::Attack()
{

}

void Zed::Damaged(int _iDmg)
{
	m_tZedStatus.m_iCurHp -= _iDmg;

	if (m_tZedStatus.m_iCurHp < 0)
	{
		m_tZedStatus.m_iCurHp = 0;

		if (m_pStateCtrl->Get_CurStateName() != L"Zed_Death")
		{
			m_pStateCtrl->Set_State(L"Zed_Death");
		}
	}
	else 
	{
		m_pStateCtrl->Set_State(L"Zed_Hit");
	}

}
