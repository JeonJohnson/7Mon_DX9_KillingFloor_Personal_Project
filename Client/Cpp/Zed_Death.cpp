#include "stdafx.h"
#include "..\Header\Zed_Death.h"
#include "AnimationController.h"
#include "ZedManager.h"
#include "Zed.h"
#include "..\..\Engine\Header\SphereCollider.h"


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

	m_GameObject->Get_Component<SphereCollider>()->Set_Alive(false);

	if (m_pAnimCtrl->Get_CurAnimIndex() != m_iDeathIndex)
	{
		m_pAnimCtrl->Play(m_iDeathIndex, true);
	}

	vRight = m_GameObject->Get_Transform()->Get_Right();

	Death_Sound();
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
		ZedManager::Get_Instance()->Add_CurZedCount(-1);

		switch (m_pZedInfo->Get_ZedInfo().m_eName)
		{
		case 0: //clot
		{ //9~12
			for (int i = 9; i < 13; ++i)
			{
				EngineFunction->Stop_Sound(i);
			}
		}
		break;

		case 1: //goreFast
		{ //13 ~17
			for (int i = 13; i < 18; ++i)
			{
				EngineFunction->Stop_Sound(i);
			}

		}
		break;

		case 2: //Scrake
		{
			//18~23
			for (int i = 18; i < 24; ++i)
			{
				EngineFunction->Stop_Sound(i);
			}
		}
		break;


		default:
			break;
		}

		m_GameObject->Set_Alive(false);
	}
	

	//double curFrame = m_GameObject->Get_Component<AnimationController>()->Get_CurFrame();
	//double maxFrame = m_GameObject->Get_Component<AnimationController>()->Get_MaxFrame();
	//DEBUG_LOG(to_wstring(curFrame) + L"/" + to_wstring(maxFrame));

	//if (curFrame >= 1.5)
	//{
	//	m_pAnimCtrl->Set_Play(false);
	//	//���⿡ ���� �Ѿ����� �ִϸ��̼�? Transform ��ȯ �ֱ�.
	//}

}
void Zed_Death::ExitState()
{
}

void Zed_Death::Death_Sound()
{

	wstring SoundName;

	int iRand = 0;

	switch (m_pZedInfo->Get_ZedInfo().m_eName)
	{
	case 0: //clot
	{
		iRand = rand() % 3;

		SoundName = L"Zed_Clot_Death" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Clot_Death);
	}
	break;

	case 1: //goreFast
	{
		iRand = rand() % 4;

		SoundName = L"Zed_Gorefast_Death" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_GoreFast_Death);

	}
	break;

	case 2: //Scrake
	{
		iRand = rand() % 4;

		SoundName = L"Zed_Scrake_Death" + to_wstring(iRand) + L".wav";
		EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Scrake_Death);
	}
	break;


	default:
		break;
	}
}
