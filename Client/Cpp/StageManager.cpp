#include "stdafx.h"
#include "..\Header\StageManager.h"

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
	}
}

void StageManager::Initialize()
{
}

void StageManager::Update()
{
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
