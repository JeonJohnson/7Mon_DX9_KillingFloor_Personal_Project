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
	
	m_fWalkOffset = Function_Math::RandFloat(0.f ,5.f);

	m_fRandAttDist = Function_Math::RandFloat(0.f, 5.f);

	m_fSound_MaxTime = (float)(rand() % 5 + 3);
}

void Zed_Walk::UpdateState()
{
	DEBUG_LOG(L"Zed : Walk");
	

	Walk_Sound();



	Vector3	vPos = m_Transform->Get_Position();
	Vector3 vForward = m_Transform->Get_Forward();
	//Vector3 vRight = m_Transform->Get_Right();
	//Vector3	vLeft = vRight * -1;

	//float fSpd = m_pZedInfo->Get_ZedInfo().m_fWalkSpd + ;
	//m_Transform->Add_Position(vForward * fTime * m_pZedInfo->Get_ZedInfo().m_fWalkSpd);


	//if (m_pNaviMesh->Add_Pos(vPos, vForward * fTime * fSpd, &m_icurCellIndex) == Vector3(0.f, 0.f, 0.f))
	//{//길이 막혔을때.
	//	m_pZedInfo->Set_DontLook(true);

	//	if (m_pNaviMesh->Add_Pos(vPos, vRight * fTime * fSpd, &m_icurCellIndex) == Vector3(0.f, 0.f, 0.f))
	//	{//Right 쪽도 막혀있을때.
	//		if (m_pNaviMesh->Add_Pos(vPos, vLeft * fTime * fSpd, &m_icurCellIndex) == Vector3(0.f, 0.f, 0.f))
	//		{ //Left 쪽도 막혀 있을때.
	//			//가 있을려나?

	//		}
	//		else 
	//		{ //Left 쪽으로 돌기

	//			DEBUG_LOG(L"Zed Trun Left");
	//			m_Transform->RotateY(fTime * 40 * -1);
	//		}
	//	}
	//	else
	//	{ //Right쪽으로 돌기.
	//		DEBUG_LOG(L"Zed Turn Right");
	//		m_Transform->RotateY(fTime * 40 * 1);
	//	}
	//}
	//else 
	//{
	//	m_pZedInfo->Set_DontLook(false);

		m_Transform->Add_Position(m_pNaviMesh->Add_Pos(m_Transform->Get_Position(), 
			vForward * fTime * (m_pZedInfo->Get_ZedInfo().m_fWalkSpd + m_fWalkOffset), 
			&m_icurCellIndex));
	//}

	
	
	if (m_GameObject->Get_Component<Zed>()->Get_Distance() <= 30.f + m_fRandAttDist)
	{
		m_pStateController->Set_State(L"Zed_Att");
	}

}

void Zed_Walk::ExitState()
{
}

void Zed_Walk::Walk_Sound()
{
	m_fSound_CurTime += fTime;

	if (m_fSound_CurTime >= m_fSound_MaxTime)
	{
		wstring SoundName;

		int iRand = 0;
		switch (m_pZedInfo->Get_ZedInfo().m_eName)
		{
		case 0: //clot
		{
			iRand = rand() % 4;

			SoundName = L"Zed_Clot_Attack" + to_wstring(iRand) + L".wav";
			EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Clot_IDLE);
		}
		break;

		case 1: //goreFast
		{
			iRand = rand() % 5;
			SoundName = L"Zed_Gorefast_Idle" + to_wstring(iRand) + L".wav";
			EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_GoreFast_Idle);
			
		}
		break;

		case 2: //Scrake
		{
			SoundName = L"Zed_Scrake_Idle.wav";
			EngineFunction->OverlapPlay_Sound(SoundName, SoundCH_Scrake_Idle);
		}
		break;


		default:
			break;
		}

	
		m_fSound_CurTime = 0.f;
	}




}
