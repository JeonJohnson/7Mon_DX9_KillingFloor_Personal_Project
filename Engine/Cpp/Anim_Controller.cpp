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
	//???߿? ???ø????? ???????? MeshRenderer ?־??????ҵ?...?

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

	//1. ?ε????? ?ش??ϴ? ?ִϸ??̼? ??Ʈ ?޾ƿ???.
	m_pAnimController->GetAnimationSet(_iNewIndex, &m_pAnimSet);

	//2. ?ش? ?ִϸ??̼Ǽ?Ʈ???? ?ʿ??? ???? ?޾ƿ???.
	m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	//3. ???????? ?ʿ??????? ?׳? ???? Ʈ???? ?ִϸ??̼? ?? ?ø???.
	m_pAnimController->SetTrackAnimationSet(m_iCurTrack, m_pAnimSet);

	//4. Ʈ?? Ȱ??ȭ.
	m_pAnimController->SetTrackEnable(m_iCurTrack, TRUE);

	//5. ?ش? Ʈ???? ???? ?޾ƿ???.
	//
	//???? null?? ?޾ƿ???.

	//6. ???? ?????? ???ؼ? ?? ?ʱ?ȭ ?ϱ?.
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

	////?ִϸ??̼? ??Ʈ ????????.
	//m_pAnimController->GetAnimationSet(_iNewIndex, &m_pAnimSet);
	//				//=>GetAnimationSetByName()???? ?ҷ??? ?? ????.
	////m_pAnimSet = pAnimSet;

	////?ִϸ??̼? Ű?????? ?ִ?ġ ????????
	//m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	////Ʈ?? ????
	//m_pAnimController->SetTrackAnimationSet(m_iNewTrack, m_pAnimSet);

	//m_pAnimController->UnkeyAllTrackEvents(m_iCurTrack);
	//m_pAnimController->UnkeyAllTrackEvents(m_iNewTrack);

	//m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_fCurKeyFrame);

	//m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_fCurKeyFrame + 0.25);

	////?ش? Ʈ???? ?????Ǵ? ?ð????? ???? Ű ???????? ? ?ӵ??? ?????̰? ?? ???ΰ?
	//m_pAnimController->KeyTrackSpeed(m_iCurTrack, 1.f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	////?ش? Ʈ???? ?????Ǵ? ?ð????? ???? Ű ???????? ????ġ?? ??? ?????? ???ΰ? 
	//m_pAnimController->KeyTrackWeight(m_iCurTrack, 0.1f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	//Ʈ???? Ȱ??ȭ, ???? ?ִϸ??̼? ????.
	//m_pAnimController->SetTrackEnable(m_iNewTrack, TRUE);
	////?ش? Ʈ???? ???۵Ǵ? ?ð????? ???? Ű ???????? ? ?ӵ??? ?????̰? ?? ???ΰ?
	//m_pAnimController->KeyTrackSpeed(m_iNewTrack, 1.f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	////?ش? Ʈ???? ???۵Ǵ? ?ð????? ???? Ű ???????? ????ġ?? ??? ?????? ???ΰ? 
	//m_pAnimController->KeyTrackWeight(m_iNewTrack, 0.9f, m_fCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

	////AdvanceTime ȣ?? ?? ?????ϴ? ?ð? ???? ?ʱ?ȭ
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

	//AdvanceTime ȣ?? ?? ?????ϴ? ?ð? ???? ?ʱ?ȭ
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
