#include "..\Header\AnimationController.h"

#include "GameObject.h"
#include "TimeManager.h"
#include "Function_String.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"

AnimationController::AnimationController(Desc * _desc)
{
	m_iCurIndex = _desc->InitIndex;
	m_dAnimSpd = _desc->dAnimSpd;

	m_bLoop = _desc->bLoop;
	m_bPlay = _desc->bPlay;

	m_pCurTrackInfo = new D3DXTRACK_DESC;
	ZeroMemory(m_pCurTrackInfo, sizeof(D3DXTRACK_DESC));

	m_bClone = _desc->bClone;
}

AnimationController::~AnimationController()
{

}

void AnimationController::Initialize()
{
	SetUp_AnimCtrl();
	Play(m_iCurIndex);
}

void AnimationController::Update()
{
	m_dDeltaTime = TimeManager::Get_Instance()->Get_dTime();

	//if (m_bPlay)
	//{
	//	Animating();
	//}
}

void AnimationController::LateUpdate()
{
	
}

void AnimationController::ReadyRender()
{

}

void AnimationController::Release()
{
	Safe_Delete(m_pCurTrackInfo);
}

//HRESULT AnimationController::SetUp_Clone_AnimCtrl()
//{
//	if (m_GameObject == nullptr)
//	{
//		return E_FAIL;
//	}
//
//	Mesh_Renderer* Temp_MeshRenderer = m_GameObject->Get_Component<Mesh_Renderer>();
//
//	if (Temp_MeshRenderer == nullptr)
//	{
//		Temp_MeshRenderer = m_GameObject->Get_Component<Mesh_Renderer>();
//	}
//
//	assert(L"Cant find MeshRenderer at AnimCtrler" && Temp_MeshRenderer);
//
//	if (Temp_MeshRenderer->Get_Mesh() == nullptr)
//	{
//		return E_FAIL;
//	}
//
//	LPD3DXANIMATIONCONTROLLER pTempAnimCtrl = Temp_MeshRenderer->Get_Mesh()->Get_AnimController();
//
//	if (pTempAnimCtrl != nullptr)
//	{
//		pTempAnimCtrl->CloneAnimationController(
//			pTempAnimCtrl->GetMaxNumAnimationOutputs(),
//			pTempAnimCtrl->GetMaxNumAnimationSets(),
//			pTempAnimCtrl->GetMaxNumTracks(),
//			pTempAnimCtrl->GetMaxNumEvents(),
//			&m_pAnimCtrl);
//
//		m_iMaxIndex = m_pAnimCtrl->GetMaxNumAnimationSets();
//	}
//
//	return S_OK;
//}

HRESULT AnimationController::SetUp_AnimCtrl()
{
	if (m_GameObject == nullptr)
	{
		return E_FAIL;
	}

	Mesh_Renderer* Temp_MeshRenderer = m_GameObject->Get_Component<Mesh_Renderer>();

	if (Temp_MeshRenderer == nullptr)
	{
		Temp_MeshRenderer = m_GameObject->Get_Component<Mesh_Renderer>();
	}

	assert(L"Cant find MeshRenderer at AnimCtrler" && Temp_MeshRenderer);

	if (Temp_MeshRenderer->Get_Mesh() == nullptr)
	{
		return E_FAIL;
	}

	LPD3DXANIMATIONCONTROLLER pTempAnimCtrl = Temp_MeshRenderer->Get_Mesh()->Get_AnimController();

	if (pTempAnimCtrl != nullptr)
	{
		if (m_bClone == false)
		{
			m_pAnimCtrl = pTempAnimCtrl;
		}
		else 
		{
			pTempAnimCtrl->CloneAnimationController(
				pTempAnimCtrl->GetMaxNumAnimationOutputs(),
				pTempAnimCtrl->GetMaxNumAnimationSets(),
				pTempAnimCtrl->GetMaxNumTracks(),
				pTempAnimCtrl->GetMaxNumEvents(),
				&m_pAnimCtrl);
		}

		

		m_iMaxIndex = m_pAnimCtrl->GetMaxNumAnimationSets();
	}

	return S_OK;
}


void AnimationController::Animating()
{
	//������ ������ �Ѿ�°� ���
	//���� �����ӿ��� ���� �� �غ��� �� ���� �ƽ����� �Ѿ��
	//�ƽ� ���������� ��� �ִ°�.
	//1. ���� �ƴϸ� �״�� �ƽ������� �־��༭ �� ���߸� �ǰ�
	//2. ������...? �� �״�� 

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

void AnimationController::Play(int _iNewAnimIndex, bool _bBlending)
{
	//if (m_iCurIndex == _iNewIndex)
	//{
	//	return;
	//}
	if (m_pAnimCtrl == nullptr)
	{
		return;
	}

	m_pAnimCtrl->GetAnimationSet(_iNewAnimIndex, &m_pAnimSet);
	m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	if (!_bBlending)
	{//Do not Animation Blending for Animation change
		//0. ����Ǿ��ִ� �̺�Ʈ ����(������ ���� ����)
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iCurTrackIndex);

		//1. �ε����� �ش��ϴ� �ִϸ��̼� ��Ʈ �޾ƿ���
		//m_pAnimCtrl->GetAnimationSet(_iNewAnimIndex, &m_pAnimSet);


		//2. �ش� �ִϸ��̼ǙV���� �ʿ��� ���� �޾ƿ���.
		m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

		//3. ���� �ʿ� ������ �׳� ���� Ʈ���� �ִϸ��̼� ��Ʈ�ø���
		m_pAnimCtrl->SetTrackAnimationSet(m_iCurTrackIndex, m_pAnimSet);

		//4. Ʈ�� Ȱ��ȭ
		m_pAnimCtrl->SetTrackEnable(m_iCurTrackIndex, TRUE);

		//5. ���ο� �ִϸ��̼��� �����ϱ� ���ؼ� �� �ʱ�ȭ.
		m_pAnimCtrl->ResetTime();
		m_pAnimCtrl->SetTrackPosition(m_iCurTrackIndex, 0.0);
		m_dCurKeyFrame = 0.0;

		m_iCurIndex = _iNewAnimIndex;
	}
	else
	{//Do Blending for Animation Change
		// track Index Check;
		m_iNewTrackIndex = (m_iCurTrackIndex == 0) ? 1 : 0;

		//Ʈ�� ����->����
		m_pAnimCtrl->SetTrackAnimationSet(m_iNewTrackIndex, m_pAnimSet);
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iCurTrackIndex);
		m_pAnimCtrl->UnkeyAllTrackEvents(m_iNewTrackIndex);
		
		//���� ����ǰ� �ִ� �ִϸ��̼��� ������ ����� ���ΰ�.
		m_pAnimCtrl->KeyTrackEnable(m_iCurTrackIndex, FALSE, m_dCurKeyFrame + 0.25);
		//�ش� Ʈ���� �����Ǵ� ���� ���� � �ӵ��� ������ ���ΰ�.
		m_pAnimCtrl->KeyTrackSpeed(m_iCurTrackIndex, 1.f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);
		//�ش� Ʈ���� �����Ǵ� �ð����� ���� Ű �������� ����ġ�� ��� ������ ���ΰ� 
		m_pAnimCtrl->KeyTrackWeight(m_iCurTrackIndex, 0.2f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

		//�� Ʈ�� Ȱ��ȭ.
		m_pAnimCtrl->SetTrackEnable(m_iNewTrackIndex, TRUE);
		//�� Ʈ���� ���۵Ǵ� �ð����� ���ο� �ִϸ��̼��� � �ӵ��� �����̰� �� ���ΰ�
		m_pAnimCtrl->KeyTrackSpeed(m_iNewTrackIndex, 1.f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);
		//�� Ʈ���� ���۵Ǵ� �ð����� ���ο� �ִϸ��̼��� ����ġ�� ��� ������ ���ΰ� 
		m_pAnimCtrl->KeyTrackWeight(m_iNewTrackIndex, 0.8f, m_dCurKeyFrame, 0.25, D3DXTRANSITION_LINEAR);

		//�� ����.
		m_pAnimCtrl->ResetTime();
		//m_pAnimCtrl->SetTrackPosition(m_iNewTrackIndex, 0.0);
		m_dCurKeyFrame = 0.0;

		m_iCurIndex = _iNewAnimIndex;
		m_iCurTrackIndex = m_iNewTrackIndex;
	}

	m_pAnimCtrl->GetTrackDesc(m_iCurTrackIndex, m_pCurTrackInfo);
}

void AnimationController::Play(const wstring & _szNewAnimName, bool _bBlending)
{
	//if (m_pAnimCtrl == nullptr)
	//{
	//	return;
	//}

	//m_pAnimCtrl->GetAnimationSetByName(_szNewAnimName, &m_pAnimSet);
	//m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	//if (!_bBlending)
	//{//Do not Animation Blending for Animation change
	// //0. ����Ǿ��ִ� �̺�Ʈ ����(������ ���� ����)
	//	m_pAnimCtrl->UnkeyAllTrackEvents(m_iCurTrackIndex);

	//	//1. �ε����� �ش��ϴ� �ִϸ��̼� ��Ʈ �޾ƿ���
	//	m_pAnimCtrl->GetAnimationSet(_iNewAnimIndex, &m_pAnimSet);

	//	//2. �ش� �ִϸ��̼ǙV���� �ʿ��� ���� �޾ƿ���.
	//	m_dMaxKeyFrame = m_pAnimSet->GetPeriod();

	//	//3. ���� �ʿ� ������ �׳� ���� Ʈ���� �ִϸ��̼� ��Ʈ�ø���
	//	m_pAnimCtrl->SetTrackAnimationSet(m_iCurTrackIndex, m_pAnimSet);

	//	//4. Ʈ�� Ȱ��ȭ
	//	m_pAnimCtrl->SetTrackEnable(m_iCurTrackIndex, TRUE);

	//	//5. ���ο� �ִϸ��̼��� �����ϱ� ���ؼ� �� �ʱ�ȭ.
	//	m_pAnimCtrl->ResetTime();
	//	m_pAnimCtrl->SetTrackPosition(m_iCurTrackIndex, 0.0);
	//	m_dCurKeyFrame = 0.0;

	//	m_iCurIndex = _iNewAnimIndex;
	//}
	//else
	//{//Do Blending for Animation Change
	// // track Index Check;
	//	m_iNewTrackIndex = (m_iCurTrackIndex == 0) ? 1 : 0;

	//	//Ʈ�� ����->����
	//	m_pAnimCtrl->SetTrackAnimationSet(m_iNewTrackIndex, m_pAnimSet);
	//	m_pAnimCtrl->UnkeyAllTrackEvents(m_iCurTrackIndex);
	//	m_pAnimCtrl->UnkeyAllTrackEvents(m_iNewTrackIndex);

	//	//���� ����ǰ� �ִ� �ִϸ��̼��� ������ ����� ���ΰ�.
	//	m_pAnimCtrl->KeyTrackEnable(m_iCurTrackIndex, FALSE, m_dCurKeyFrame + 0.1);
	//	//�ش� Ʈ���� �����Ǵ� ���� ���� � �ӵ��� ������ ���ΰ�.
	//	m_pAnimCtrl->KeyTrackSpeed(m_iCurTrackIndex, 1.f, m_dCurKeyFrame, 0.1, D3DXTRANSITION_LINEAR);
	//	//�ش� Ʈ���� �����Ǵ� �ð����� ���� Ű �������� ����ġ�� ��� ������ ���ΰ� 
	//	m_pAnimCtrl->KeyTrackWeight(m_iCurTrackIndex, 0.2f, m_dCurKeyFrame, 0.1, D3DXTRANSITION_LINEAR);

	//	//�� Ʈ�� Ȱ��ȭ.
	//	m_pAnimCtrl->SetTrackEnable(m_iNewTrackIndex, TRUE);
	//	//�� Ʈ���� ���۵Ǵ� �ð����� ���ο� �ִϸ��̼��� � �ӵ��� �����̰� �� ���ΰ�
	//	m_pAnimCtrl->KeyTrackSpeed(m_iNewTrackIndex, 1.f, m_dCurKeyFrame, 0.1, D3DXTRANSITION_LINEAR);
	//	//�� Ʈ���� ���۵Ǵ� �ð����� ���ο� �ִϸ��̼��� ����ġ�� ��� ������ ���ΰ� 
	//	m_pAnimCtrl->KeyTrackWeight(m_iNewTrackIndex, 0.8f, m_dCurKeyFrame, 0.1, D3DXTRANSITION_LINEAR);

	//	//�� ����.
	//	m_pAnimCtrl->ResetTime();
	//	m_pAnimCtrl->SetTrackPosition(m_iNewTrackIndex, 0.0);
	//	m_dCurKeyFrame = 0.0;

	//	m_iCurIndex = _iNewAnimIndex;
	//	m_iCurTrackIndex = m_iNewTrackIndex;
	//}

	//m_pAnimCtrl->GetTrackDesc(m_iCurTrackIndex, m_pCurTrackInfo);
}

bool AnimationController::IsEnd()
{
	if (m_dCurKeyFrame >= m_dMaxKeyFrame - m_dOffSet)
	{
		return true;
	}
	return false;
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

wstring AnimationController::Get_CurAnimName()
{
	wstring szResult;

	Function_String::stringTowstring(m_pAnimSet->GetName(),szResult);

	return szResult;
}

int AnimationController::Get_CurAnimIndex()
{
	return m_iCurIndex;
}

int AnimationController::Get_MaxAnimIndex()
{
	return m_iMaxIndex;
}

double AnimationController::Get_CurFrame()
{
	return m_dCurKeyFrame;
}

double AnimationController::Get_MaxFrame()
{
	return m_dMaxKeyFrame;
}

double AnimationController::Get_AnimSpd()
{
	return m_dOffSet;
}

bool AnimationController::Get_Playing()
{
	return m_bPlay;
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

void AnimationController::Set_OffSet(double _dOffSet)
{
	m_dOffSet = _dOffSet;
}
