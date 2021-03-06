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
	m_bPlay = _desc->bPlay;

	m_tCurTrackInfo = new D3DXTRACK_DESC;
	ZeroMemory(m_tCurTrackInfo, sizeof(D3DXTRACK_DESC));
}

Anim_Controller::~Anim_Controller()
{
}

void Anim_Controller::Initialize()
{
	
}

void Anim_Controller::Update()
{
	m_fdTime = TimeManager::Get_Instance()->Get_fTime();


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
	Safe_Delete(m_tCurTrackInfo);
}
 
HRESULT Anim_Controller::Setup_AnimController(GameObject* _pGameObject)
{
	//나중에 템플릿으로 연결지을 MeshRenderer 넣어줘야할덧...?

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

			//pTempAnimCtrl->CloneAnimationController(
			//	pTempAnimCtrl->GetMaxNumAnimationOutputs(),
			//	pTempAnimCtrl->GetMaxNumAnimationSets(),
			//	pTempAnimCtrl->GetMaxNumTracks(),
			//	pTempAnimCtrl->GetMaxNumEvents(),
			//	&m_pAnimController);

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
	//if (m_fCurKeyFrame + m_fdTime >= (float)m_dMaxKeyFrame )
	//{
	//	m_fCurKeyFrame = m_dMaxKeyFrame;

	//	m_pAnimController->AdvanceTime((m_dMaxKeyFrame-m_fdTime-0.01) * m_fAnimSpd, NULL);
	//}
	//else 
	{
		//m_pAnimController->AdvanceTime(m_fdTime * m_fAnimSpd, NULL);
	}

	if (m_bLoop)
	{
		m_pAnimController->AdvanceTime(m_fdTime *m_fAnimSpd, NULL);
	}
	else
	{
		if (m_fCurKeyFrame + (m_fdTime* m_fAnimSpd) >= m_dMaxKeyFrame)
		{
			m_pAnimController->SetTrackPosition(m_iCurTrack, m_dMaxKeyFrame);
		}
		else { m_pAnimController->AdvanceTime(m_fdTime* m_fAnimSpd, NULL); }


	//	if (m_fCurKeyFrame < (float)m_dMaxKeyFrame - 0.01)
	//	{
	//		if (m_fCurKeyFrame + (m_fdTime*m_fAnimSpd) >= (float)m_dMaxKeyFrame)
	//		{
	//			//m_pAnimController->SetTrackPosition(m_iCurTrack, m_dMaxKeyFrame);

	//			float LastFrameOffset = (float)(m_dMaxKeyFrame - (m_fdTime*m_fAnimSpd));

	//			m_pAnimController->AdvanceTime(LastFrameOffset, NULL);
	//		}
	//		else 
	//		{
	//			m_pAnimController->AdvanceTime(m_fdTime * m_fAnimSpd, NULL);
	//		}
	//	}
	//	else 
	//	{
	//		m_pAnimController->SetTrackPosition(m_iCurTrack, m_dMaxKeyFrame);
	//	}
	}

	

	m_pAnimController->GetTrackDesc(m_iCurTrack, m_tCurTrackInfo);

	m_fCurKeyFrame = (float)m_tCurTrackInfo->Position;


}

//void Anim_Controller::Reset_Frame()
//{
//
//}

//void Anim_Controller::Stop_Animation()
//{
//	m_bPlay = false;
//}

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

float Anim_Controller::Get_CurFrame() const
{
	return (float)m_tCurTrackInfo->Position;
}

float Anim_Controller::Get_MaxFrame() const
{
	return (float)m_dMaxKeyFrame;
}

bool Anim_Controller::Get_End()
{
	if (m_fCurKeyFrame >= (float)(m_dMaxKeyFrame - m_dOffSet))
	{
		return true;
	}
	return false;
}

void Anim_Controller::Set_AnimController(LPD3DXANIMATIONCONTROLLER _pAnimCtrl)
{
	assert(L"Set AnimController is nullptr" && _pAnimCtrl);
	
	m_pAnimController = _pAnimCtrl;
}

void Anim_Controller::Set_AnimIndex(int _iNewIndex)
{
	//if (m_iCurIndex == _iNewIndex)
	//{
	//	return;
	//}


#pragma region Test
	//m_pAnimController->UnkeyAllTrackEvents(m_iCurTrack);
	//m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_fCurKeyFrame);

	//1. 인덱스에 해당하는 애니메이션 세트 받아오기.
	m_pAnimController->GetAnimationSet(_iNewIndex, &m_pAnimSet);

	//2. 해당 애니메이션세트에서 필요한 정보 받아오기.
	m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	//3. 블랜딩이 필요없으니 그냥 현재 트랙에 애니메이션 셋 올리기.
	m_pAnimController->SetTrackAnimationSet(m_iCurTrack, m_pAnimSet);

	//4. 트랙 활성화.
	m_pAnimController->SetTrackEnable(m_iCurTrack, TRUE);

	//5. 해당 트랙의 정보 받아오기.
	//
	//지금 null로 받아와짐.

	//6. 새로 시작을 위해서 값 초기화 하기.
	m_pAnimController->SetTrackPosition(m_iCurTrack, 0.0);
	m_pAnimController->ResetTime();
	m_fCurKeyFrame = 0.f;

	m_pAnimController->GetTrackDesc(m_iCurTrack, m_tCurTrackInfo);
#pragma endregion 




#pragma region Origin

	//if (m_iCurTrack == 0)
	//{
	//	m_iNewTrack = 1;
	//}
	//else
	//{
	//	m_iNewTrack = 0;
	//}

	////애니메이션 세트 가져오기.
	//m_pAnimController->GetAnimationSet(_iNewIndex, &m_pAnimSet);
	//				//=>GetAnimationSetByName()으로 불러올 수 있음.
	////m_pAnimSet = pAnimSet;

	////애니메이션 키프레임 최대치 가져오기
	//m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	////트랙 세팅
	//m_pAnimController->SetTrackAnimationSet(m_iNewTrack, m_pAnimSet);

	//m_pAnimController->UnkeyAllTrackEvents(m_iCurTrack);
	//m_pAnimController->UnkeyAllTrackEvents(m_iNewTrack);

	//m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_fCurKeyFrame);

	//m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_fCurKeyFrame + 0.25);

	////해당 트랙이 해제되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
	//m_pAnimController->KeyTrackSpeed(m_iCurTrack, 1.f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	////해당 트랙이 해제되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
	//m_pAnimController->KeyTrackWeight(m_iCurTrack, 0.1f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	//트랙을 활성화, 다음 애니메이션 시작.
	//m_pAnimController->SetTrackEnable(m_iNewTrack, TRUE);
	////해당 트랙이 시작되는 시간동안 현재 키 프레임은 어떤 속도로 움직이게 할 것인가
	//m_pAnimController->KeyTrackSpeed(m_iNewTrack, 1.f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	////해당 트랙이 시작되는 시간동안 현재 키 프레임의 가중치를 어떻게 설정할 것인가 
	//m_pAnimController->KeyTrackWeight(m_iNewTrack, 0.9f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	////AdvanceTime 호출 시 증가하던 시간 값을 초기화
	//m_pAnimController->ResetTime();
	//m_fCurKeyFrame = 0.f;
	//m_pAnimController->SetTrackPosition(m_iNewTrack, 0.0);

	//m_iCurIndex = _iNewIndex;
	//m_iCurTrack = m_iNewTrack;
#pragma	endregion


}

void Anim_Controller::Set_AnimIndex_NoBlend(int _iNewIndex)
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

	m_pAnimController->GetAnimationSet(_iNewIndex, &pAnimSet);
	m_pAnimSet = pAnimSet;
	m_dMaxKeyFrame = pAnimSet->GetPeriod();

	//m_pAnimController->SetTrackPosition(m_iCurTrack, 0.0);

	m_pAnimController->SetTrackAnimationSet(m_iCurTrack, pAnimSet);
	//m_pAnimController->UnkeyAllTrackEvents(m_iCurTrack);
	//m_pAnimController->UnkeyAllTrackEvents(m_iNewTrack);
	m_pAnimController->SetTrackEnable(m_iCurTrack, TRUE);

	//m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE);
	//m_pAnimController->SetTrackEnable(m_iNewTrack, TRUE);

	//AdvanceTime 호출 시 증가하던 시간 값을 초기화
	m_pAnimController->ResetTime();
	m_fCurKeyFrame = 0.f;

	m_pAnimController->SetTrackPosition(m_iCurTrack, 0.0);

	m_iCurIndex = _iNewIndex;

	//m_iCurTrack = m_iNewTrack;

}

void Anim_Controller::Set_AnimSpd(float _fAnimSpd)
{
	m_fAnimSpd = _fAnimSpd;
}

void Anim_Controller::Set_CurFrame(float _fFrame)
{
	m_fCurKeyFrame = _fFrame;
}

void Anim_Controller::Set_Loop(bool _bLoop)
{
	m_bLoop = _bLoop;
}

void Anim_Controller::Set_AnimReset(int _iIndex)
{
	m_pAnimController->SetTrackPosition(_iIndex, 0.0);
}
