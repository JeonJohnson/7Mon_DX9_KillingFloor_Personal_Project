#include "stdafx.h"
#include "..\Header\Zed_Death.h"
#include "AnimationController.h"
#include "ZedManager.h"
#include "Zed.h"


Zed_Death::Zed_Death()
{
}


Zed_Death::~Zed_Death()
{
}

void Zed_Death::Initialize()
{
}

void Zed_Death::EnterState()
{
	
	if (m_pAnimCtrl == nullptr)
	{
		m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	}

	if (m_pZedInfo == nullptr)
	{
		m_pZedInfo = m_GameObject->Get_Component<Zed>();
	}


	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iDeathIndex)
	{
		m_pAnimCtrl->Play(m_iDeathIndex, true);
	}

	vRight = m_GameObject->Get_Transform()->Get_Right();
}

void Zed_Death::UpdateState()
{
	DEBUG_LOG(L"Zed : Death");      
	Vector3 vRotate = m_GameObject->Get_Transform()->Get_Rotation_Euler();
	DEBUG_LOG(L"Rotate : " + to_wstring(vRotate.x) + L"/" + to_wstring(vRotate.y) + L"/" + to_wstring(vRotate.z));
	
	m_fDownAcc += fTime;



	if (vRotate.x <= 85.f )
	{

		m_GameObject->Get_Transform()->RotateAxis(vRight, m_fDownAcc / 100.f);
	}
	else
	{
		ZedManager::Get_Instance()->Add_ZedCount(-1);
		m_GameObject->Set_Alive(false);
	}
	

	//double curFrame = m_GameObject->Get_Component<AnimationController>()->Get_CurFrame();
	//double maxFrame = m_GameObject->Get_Component<AnimationController>()->Get_MaxFrame();
	//DEBUG_LOG(to_wstring(curFrame) + L"/" + to_wstring(maxFrame));

	//if (curFrame >= 1.5)
	//{
	//	m_pAnimCtrl->Set_Play(false);
	//	//여기에 이제 넘어지는 애니메이션? Transform 변환 넣기.
	//}

}
void Zed_Death::ExitState()
{
}
