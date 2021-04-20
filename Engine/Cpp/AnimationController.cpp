#include "..\Header\AnimationController.h"
#include "..\..\Reference\Header\TimeManager.h"

AnimationController::AnimationController()
{
}

AnimationController::AnimationController(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAnimationController(pAniCtrl)
	, m_iCurrentTrack(0)
	, m_iNewTrack(1)
	, m_iOldIndex(9990)
	, m_fAccTime(0.f)
	, m_dPeriod(0.0)
{
}


AnimationController::AnimationController(const AnimationController & rhs)
	: m_iCurrentTrack(rhs.m_iCurrentTrack),
	m_iNewTrack(rhs.m_iNewTrack),
	m_iOldIndex(rhs.m_iOldIndex),
	m_fAccTime(rhs.m_fAccTime),
	m_dPeriod(0.0)
{
	rhs.m_pAnimationController->CloneAnimationController(
		rhs.m_pAnimationController->GetMaxNumAnimationOutputs(),
		rhs.m_pAnimationController->GetMaxNumAnimationSets(),
		rhs.m_pAnimationController->GetMaxNumTracks(),
		rhs.m_pAnimationController->GetMaxNumEvents(),
		&m_pAnimationController);
}

AnimationController::~AnimationController()
{
	Safe_Release(m_pAnimationController);
}

HRESULT AnimationController::Ready_Controller()
{
	return S_OK;
}

void AnimationController::Set_AnimationSet(int _iIndex)
{
	if (m_iOldIndex == _iIndex)
	{//현재 재생하고 있는 인덱스와 같을 경우엔 걍 나가버리기
		return;
	}

	if (m_iCurrentTrack == 0)
	{
		m_iNewTrack = 1;
	}
	else
	{
		m_iNewTrack = 0;
	}

	LPD3DXANIMATIONSET	pAnimSet = nullptr;

	//Xfile에 저장 되어있는 애니메이션 세트 가져오기
	m_pAnimationController->GetAnimationSet(_iIndex, &pAnimSet);
	//이름으로 검색하기 ->GetAnimationSetByName();

	//애니메이션의 전체 재생 시간
	m_dPeriod = pAnimSet->GetPeriod(); 

	// 트랙 위에 추출한 애니메이션 셋을 세팅
	m_pAnimationController->SetTrackAnimationSet(m_iNewTrack, pAnimSet);

	m_pAnimationController->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAnimationController->UnkeyAllTrackEvents(m_iNewTrack);

	
	m_pAnimationController->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);
	
	//해당 트랙이 해제되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
	m_pAnimationController->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//해당 트랙이 해제되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
	m_pAnimationController->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//트랙을 활성화
	m_pAnimationController->SetTrackEnable(m_iNewTrack, TRUE);
	//해당 트랙이 시작되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
	m_pAnimationController->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//해당 트랙이 시작되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
	m_pAnimationController->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//AdvanceTime 호출 시 증가하던 시간 값을 초기화
	m_pAnimationController->ResetTime();
	m_fAccTime = 0.f;

	m_pAnimationController->SetTrackPosition(m_iNewTrack, 0.0);
	m_iOldIndex = _iIndex;

	m_iCurrentTrack = m_iNewTrack;
}

void AnimationController::Play_AnimationSet()
{
	//컨트롤러 구동시 내부적으로 증가되는 시간 값 증가 시켜주기.

	m_pAnimationController->AdvanceTime(TimeManager::Get_Instance()->Get_Time(), NULL);

	m_fAccTime += TimeManager::Get_Instance()->Get_Time();
}

void AnimationController::Set_AnimContoller(LPD3DXANIMATIONCONTROLLER _controller)
{
	m_pAnimationController = _controller;
}

LPD3DXANIMATIONCONTROLLER AnimationController::Get_Controller()
{
	return m_pAnimationController;
}

bool AnimationController::Get_IsPlaying()
{
	D3DXTRACK_DESC	TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAnimationController->GetTrackDesc(m_iCurrentTrack, &TrackInfo);

	if (TrackInfo.Position >= m_dPeriod - 0.1)
	{
		return false;
	}

	return true;
}
