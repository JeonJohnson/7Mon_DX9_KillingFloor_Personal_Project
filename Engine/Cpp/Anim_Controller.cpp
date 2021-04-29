#include "..\Header\Anim_Controller.h"

#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"
#include "TimeManager.h"

Anim_Controller::Anim_Controller(Desc * _desc)
{
	//assert(L"gameObject is Nullptr" && _desc->gameObject);

	if (Setup_AnimController(_desc->pGameObject) == S_OK)
	{
		Set_AnimIndex(_desc->iInitIndex);
	}

	m_fAnimSpd = _desc->fAnimSpd;
	m_iCurIndex = _desc->iInitIndex;

	m_bLoop = _desc->bLoop;

}

Anim_Controller::~Anim_Controller()
{
}

void Anim_Controller::Initialize()
{
	
}

void Anim_Controller::Update()
{
	m_fdTime = TimeManager::Get_Instance()->Get_Time();

	Play_Animation();
}

void Anim_Controller::LateUpdate()
{

}

void Anim_Controller::ReadyRender()
{

}

void Anim_Controller::Release()
{

}
 
HRESULT Anim_Controller::Setup_AnimController(GameObject* _pGameObject)
{
	if (_pGameObject != nullptr)
	{
		Mesh_Renderer* Temp_MeshRenderer = _pGameObject->Get_NewComponent<Mesh_Renderer>();

		if (Temp_MeshRenderer == nullptr)
		{
			Temp_MeshRenderer = _pGameObject->Get_Component<Mesh_Renderer>();

			if (Temp_MeshRenderer == nullptr)
			{
				return E_FAIL;
			}
		}

		LPD3DXANIMATIONCONTROLLER pTempAnimCtrl = Temp_MeshRenderer->Get_Mesh()->Get_AnimController();

		if (pTempAnimCtrl != nullptr)
		{
			m_pAnimController = pTempAnimCtrl;

			pTempAnimCtrl->CloneAnimationController(
				pTempAnimCtrl->GetMaxNumAnimationOutputs(),
				pTempAnimCtrl->GetMaxNumAnimationSets(),
				pTempAnimCtrl->GetMaxNumTracks(),
				pTempAnimCtrl->GetMaxNumEvents(),
				&m_pAnimController);

			assert(L"Animation Controller Create Clone is failed" && m_pAnimController);

			m_iMaxIndex = m_pAnimController->GetMaxNumAnimationSets();
		}
		else { return E_FAIL; }
	}
	else { return E_FAIL; }

	return S_OK;
}

void Anim_Controller::Play_Animation()
{
	if (m_bPlay)
	{
		m_pAnimController->AdvanceTime(m_fdTime * m_fAnimSpd, NULL);

		m_fCurKeyFrame += m_fdTime;
	}
}

void Anim_Controller::Stop_Animation()
{
	m_bPlay = false;
}

LPD3DXANIMATIONCONTROLLER Anim_Controller::Get_AnimController() const
{
	return m_pAnimController;
}

int Anim_Controller::Get_CurIndex() const
{
	return m_iCurIndex;
}

int Anim_Controller::Get_MaxIndex() const
{
	return m_iMaxIndex;
}

float Anim_Controller::Get_AnimCurSpd() const
{
	return m_fAnimSpd;
}

bool Anim_Controller::Get_Playing()
{
	D3DXTRACK_DESC	TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAnimController->GetTrackDesc(m_iCurTrack, &TrackInfo);

	if (TrackInfo.Position >= m_dMaxKeyFrame - 0.1)
	{
		return false;
	}
	return true;
}

void Anim_Controller::Set_AnimController(LPD3DXANIMATIONCONTROLLER _pAnimCtrl)
{
	assert(L"Set AnimController is nullptr" && _pAnimCtrl);
	
	m_pAnimController = _pAnimCtrl;
}

void Anim_Controller::Set_AnimIndex(int _iNewIndex)
{
	if (m_iCurIndex == _iNewIndex)
	{
		return;
	}

	if (m_iCurTrack == 0)
	{
		m_iNewTrack = 1;
	}
	else 
	{
		m_iNewTrack = 0;
	}

	LPD3DXANIMATIONSET		pAnimSet = nullptr;
	
	//애니메이션 세트 가져오기.
	m_pAnimController->GetAnimationSet(_iNewIndex, &pAnimSet);
					//=>GetAnimationSetByName()으로 불러올 수 있음.

	//애니메이션 키프레임 최대치 가져오기
	m_dMaxKeyFrame = pAnimSet->GetPeriod();

	//트랙 세팅->해제
	m_pAnimController->SetTrackAnimationSet(m_iNewTrack, pAnimSet);
	m_pAnimController->UnkeyAllTrackEvents(m_iCurTrack);
	m_pAnimController->UnkeyAllTrackEvents(m_iNewTrack);

	m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_fCurKeyFrame + 0.25);

	//해당 트랙이 해제되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
	m_pAnimController->KeyTrackSpeed(m_iCurTrack, 1.f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	//해당 트랙이 해제되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
	m_pAnimController->KeyTrackWeight(m_iCurTrack, 0.1f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	//트랙을 활성화
	m_pAnimController->SetTrackEnable(m_iNewTrack, TRUE);
	//해당 트랙이 시작되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
	m_pAnimController->KeyTrackSpeed(m_iNewTrack, 1.f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	//해당 트랙이 시작되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
	m_pAnimController->KeyTrackWeight(m_iNewTrack, 0.9f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	
	//AdvanceTime 호출 시 증가하던 시간 값을 초기화
		m_pAnimController->ResetTime();
		m_fCurKeyFrame = 0.f;

		m_pAnimController->SetTrackPosition(m_iNewTrack, 0.0);

	m_iCurIndex = _iNewIndex;

	m_iCurTrack = m_iNewTrack;
}

void Anim_Controller::Set_AnimSpd(float _fAnimSpd)
{
	m_fAnimSpd = _fAnimSpd;
}

void Anim_Controller::Set_CurFrame(float _fFrame)
{
	m_fCurKeyFrame = _fFrame;
}
