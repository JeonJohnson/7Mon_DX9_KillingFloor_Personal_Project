#include "stdafx.h"
#include "..\Header\Zed_Death.h"
#include "AnimationController.h"
#include "ZedManager.h"


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
	
	m_pAnimCtrl = m_GameObject->Get_Component<AnimationController>();
	m_pAnimCtrl->Set_Loop(false);
	m_pAnimCtrl->Play(6, true);
}

void Zed_Death::UpdateState()
{
	DEBUG_LOG(L"Zed : Death");
	
	Vector3 vRotate = m_GameObject->Get_Transform()->Get_Rotation_Euler();
	DEBUG_LOG(L"Rotate : " + to_wstring(vRotate.x) + L"/" + to_wstring(vRotate.y) + L"/" + to_wstring(vRotate.z));

	if (vRotate.z <= 90.f )
	{
		m_GameObject->Get_Transform()->RotateZ(fTime * 45.f);
	}
	else
	{
		ZedManager::Get_Instance()->Add_ZedCount(-1);
		m_GameObject->Set_Alive(false);
	}
	

	double curFrame = m_GameObject->Get_Component<AnimationController>()->Get_CurFrame();
	double maxFrame = m_GameObject->Get_Component<AnimationController>()->Get_MaxFrame();
	DEBUG_LOG(to_wstring(curFrame) + L"/" + to_wstring(maxFrame));

	if (curFrame >= 1.2)
	{
		m_pAnimCtrl->Set_Play(false);
		//여기에 이제 넘어지는 애니메이션? Transform 변환 넣기.
	}

}
void Zed_Death::ExitState()
{
}
