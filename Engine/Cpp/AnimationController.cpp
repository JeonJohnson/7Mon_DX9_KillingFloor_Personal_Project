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
	{//���� ����ϰ� �ִ� �ε����� ���� ��쿣 �� ����������
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

	//Xfile�� ���� �Ǿ��ִ� �ִϸ��̼� ��Ʈ ��������
	m_pAnimationController->GetAnimationSet(_iIndex, &pAnimSet);
	//�̸����� �˻��ϱ� ->GetAnimationSetByName();

	//�ִϸ��̼��� ��ü ��� �ð�
	m_dPeriod = pAnimSet->GetPeriod(); 

	// Ʈ�� ���� ������ �ִϸ��̼� ���� ����
	m_pAnimationController->SetTrackAnimationSet(m_iNewTrack, pAnimSet);

	m_pAnimationController->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAnimationController->UnkeyAllTrackEvents(m_iNewTrack);

	
	m_pAnimationController->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);
	
	//�ش� Ʈ���� �����Ǵ� �ð����� ���� Ű �������� � �ӵ��� �����̰� �� ���ΰ�
	m_pAnimationController->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//�ش� Ʈ���� �����Ǵ� �ð����� ���� Ű �������� ����ġ�� ��� ������ ���ΰ� 
	m_pAnimationController->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//Ʈ���� Ȱ��ȭ
	m_pAnimationController->SetTrackEnable(m_iNewTrack, TRUE);
	//�ش� Ʈ���� ���۵Ǵ� �ð����� ���� Ű �������� � �ӵ��� �����̰� �� ���ΰ�
	m_pAnimationController->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//�ش� Ʈ���� ���۵Ǵ� �ð����� ���� Ű �������� ����ġ�� ��� ������ ���ΰ� 
	m_pAnimationController->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	//AdvanceTime ȣ�� �� �����ϴ� �ð� ���� �ʱ�ȭ
	m_pAnimationController->ResetTime();
	m_fAccTime = 0.f;

	m_pAnimationController->SetTrackPosition(m_iNewTrack, 0.0);
	m_iOldIndex = _iIndex;

	m_iCurrentTrack = m_iNewTrack;
}

void AnimationController::Play_AnimationSet()
{
	//��Ʈ�ѷ� ������ ���������� �����Ǵ� �ð� �� ���� �����ֱ�.

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
