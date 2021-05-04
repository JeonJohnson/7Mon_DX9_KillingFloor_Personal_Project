#include "..\Header\AnimationController.h"

#include "GameObject.h"
#include "TimeManager.h"
#include "Function_String.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"

AnimationController::AnimationController(Desc * _desc)
{



}

AnimationController::~AnimationController()
{
}

void AnimationController::Initialize()
{
}

void AnimationController::Update()
{
	m_dDeltaTime = TimeManager::Get_Instance()->Get_dTime();

	if (m_bPlay)
	{
		Animating();
	}
}

void AnimationController::LateUpdate()
{

}

void AnimationController::ReadyRender()
{

}

void AnimationController::Release()
{
}

HRESULT AnimationController::SetUp_AnimCtrl()
{
	if (m_GameObject == nullptr)
	{
		return;
	}

	Mesh_Renderer* Temp_MeshRenderer = m_GameObject->Get_Component<Mesh_Renderer>();

	if (Temp_MeshRenderer == nullptr)
	{
		Temp_MeshRenderer = m_GameObject->Get_NewComponent<Mesh_Renderer>();
	}

	assert(L"Cant find MeshRenderer at AnimCtrler" && Temp_MeshRenderer);

	LPD3DXANIMATIONCONTROLLER pTempAnimCtrl = Temp_MeshRenderer->Get_Mesh()->Get_AnimController();

	if (pTempAnimCtrl != nullptr)
	{
		pTempAnimCtrl->CloneAnimationController(
			pTempAnimCtrl->GetMaxNumAnimationOutputs(),
			pTempAnimCtrl->GetMaxNumAnimationSets(),
			pTempAnimCtrl->GetMaxNumTracks(),
			pTempAnimCtrl->GetMaxNumEvents(),
			&m_pAnimCtrl);

		m_iMaxIndex = m_pAnimCtrl->GetMaxNumAnimationSets();
	}

}


void AnimationController::Animating()
{
	//마지막 프레임 넘어가는거 잡기
	//현재 프레임에서 먼저 더 해보고 그 값이 맥스값을 넘어가면
	//맥스 프레임으로 잡아 주는거.
	//1. 루프 아니면 그대로 맥스프레임 넣어줘서 걍 멈추면 되고
	//2. 루프면...? 걍 그대로 

	if (m_bLoop)
	{
		 m_pAnimCtrl->AdvanceTime(m_dDeltaTime * m_dAnimSpd, NULL);
	}
	else 
	{
		if (m_dCurKeyFrame + (m_dDeltaTime*m_dAnimSpd) >= m_dMaxKeyFrame)
		{
			m_pAnimCtrl->SetTrackPosition(m_iCurTrackIndex, m_dMaxKeyFrame);
		}
		else { m_pAnimCtrl->AdvanceTime(m_dDeltaTime * m_dAnimSpd, NULL); }
	}

	m_pAnimCtrl->GetTrackDesc(m_iCurTrackIndex, m_pCurTrackInfo);
	m_dCurKeyFrame = m_pCurTrackInfo->Position;

}

void AnimationController::Play(int _iNewIndex, bool _bBlending)
{
	if (m_iCurIndex == _iNewIndex)
	{
		return;
	}

	m_iNewTrackIndex = (m_iCurTrackIndex == 0) ? 1 : 0;


	m_pAnimCtrl->GetAnimationSet(_iNewIndex, &m_pAnimSet);
	m_dMaxKeyFrame = m_pAnimSet->GetPeriod();


	if (!_bBlending)
	{//Do not Animation Blending for Animation change
		m_pAnimCtrl->SetTrackAnimationSet(m_iNewTrackIndex, m_pAnimSet);
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iCurTrackIndex);
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iNewTrackIndex);

		m_pAnimCtrl->SetTrackEnable(m_iNewTrackIndex, TRUE);
	}
	else
	{//Do Blending for Animation Change
	 //트랙 세팅->해제
		m_pAnimCtrl->SetTrackAnimationSet(m_iNewTrackIndex, m_pAnimSet);
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iCurTrackIndex);
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iNewTrackIndex);
		
		//현재 재생되고 있는 애니메이션을 어디까지 재생할 것인가.
		m_pAnimCtrl->KeyTrackEnable(m_iCurTrackIndex, FALSE, m_dCurKeyFrame + 0.25);
		//해당 트랙이 해제되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
		m_pAnimCtrl->KeyTrackSpeed(m_iCurTrackIndex, 1.f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);
		//해당 트랙이 해제되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
		m_pAnimCtrl->KeyTrackWeight(m_iCurTrackIndex, 0.1f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

		//새 트랙을 활성화, 다음 애니메이션 시작.
		m_pAnimCtrl->SetTrackEnable(m_iNewTrackIndex, TRUE);
		//새 트랙이 시작되는 시간동안 새로운 애니메이션은 어떤 속도로 움직이게 할 것인가
		m_pAnimCtrl->KeyTrackSpeed(m_iNewTrackIndex, 1.f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);
		//새 트랙이 시작되는 시간동안 새로운 애니메이션의 가중치를 어떻게 설정할 것인가 
		m_pAnimCtrl->KeyTrackWeight(m_iNewTrackIndex, 0.9f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);
		
	}

	m_pAnimCtrl->ResetTime();
	m_dCurKeyFrame = 0.0;

	m_pAnimCtrl->SetTrackPosition(m_iNewTrackIndex, 0.0);
	m_iCurIndex = _iNewIndex;
	m_iCurTrackIndex = m_iNewTrackIndex;

	m_pAnimCtrl->GetTrackDesc(m_iCurTrackIndex, m_pCurTrackInfo);
}

LPD3DXANIMATIONCONTROLLER AnimationController::Get_AnimController()
{
	return m_pAnimCtrl;
}

LPD3DXANIMATIONSET AnimationController::Get_AnimSet()
{
	return m_pAnimSet;
}

LPD3DXTRACK_DESC AnimationController::Get_TrackInfo()
{
	return m_pCurTrackInfo;
}

wstring AnimationController::Get_AnimName()
{
	wstring szResult;

	Function_String::stringTowstring(m_pAnimSet->GetName(),szResult);

	return szResult;
}

int AnimationController::Get_CurIndex()
{
	return m_iCurIndex;
}

int AnimationController::Get_MaxIndex()
{
	return m_iMaxIndex;
}

bool AnimationController::IsEnd()
{
	if (m_dCurKeyFrame >= m_dMaxKeyFrame - m_dOffSet)
	{
		return true;
	}
	return false;
}

void AnimationController::Set_AnimController(LPD3DXANIMATIONCONTROLLER _pAnimCtrl)
{
	assert(L"_AnimCtrl is nullptr" && _pAnimCtrl);
	m_pAnimCtrl = _pAnimCtrl;
}

void AnimationController::Set_AnimSpd(double _dAnimSpd)
{
	m_dAnimSpd = _dAnimSpd;
}

void AnimationController::Set_Play(bool _OnOff)
{
	m_bPlay = _OnOff;
}

void AnimationController::Set_Loop(bool _OnOff)
{
	m_bLoop = _OnOff;
}
