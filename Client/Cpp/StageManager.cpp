#include "stdafx.h"
#include "..\Header\StageManager.h"
#include "StateController.h"


StageManager*	StageManager::m_pInstance = nullptr;


StageManager::StageManager(Desc * _desc)
{
}

StageManager::~StageManager()
{
}

StageManager * StageManager::Get_Instance()
{
	if (m_pInstance == nullptr)
	{
		GameObject*	mgrObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"StageManager");
		mgrObj->Add_Component<StageManager>();
		//mgrObj->Add_Component<StateController>();

		m_pInstance = mgrObj->Get_NewComponent<StageManager>();

		//m_pInstance->SetDontDestory(true);
	}

	return m_pInstance;
}

void StageManager::Destory_Instance()
{
	if (m_pInstance)
	{
		GameObject::Destory(m_pInstance->Get_GameObject());
		m_pInstance = nullptr;
	}
}

void StageManager::Initialize()
{
}

void StageManager::Update()
{
	//wstring szCurStage = m_pStateCtrl->Get_CurStateName();
	//
	//if (szCurStage == L"Stage_1")
	//{
	//	m_eCurStage = STAGE_NAME::STAGE_1;
	//}
	//else if (szCurStage == L"Stage_2")
	//{
	//	m_eCurStage = STAGE_NAME::STAGE_2;
	//}
	//else if (szCurStage == L"Stage_Boss")
	//{
	//	m_eCurStage = STAGE_NAME::STAGE_BOSS;
	//}
	//else if (szCurStage == L"Stage_Shop")
	//{
	//	m_eCurStage = STAGE_NAME::STAGE_SHOP;
	//}
		


}

void StageManager::LateUpdate()
{
}

void StageManager::ReadyRender()
{
}

void StageManager::Release()
{
}

STAGE_NAME StageManager::Get_CurStageName()
{
	return m_eCurStage;
}

void StageManager::Set_CurStage(STAGE_NAME _eCurStageName)
{
	m_eCurStage = _eCurStageName;
}
