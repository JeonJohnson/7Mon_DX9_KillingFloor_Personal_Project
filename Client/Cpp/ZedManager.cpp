#include "stdafx.h"
#include "..\Header\ZedManager.h"

ZedManager* ZedManager::m_pInstance = nullptr;

ZedManager::ZedManager(Desc * _desc)
{
}

ZedManager::~ZedManager()
{
}

ZedManager * ZedManager::Get_Instance()
{
	return nullptr;
}

void ZedManager::Destroy_Instance()
{
}

void ZedManager::Initialize()
{
}

void ZedManager::Update()
{
}

void ZedManager::LateUpdate()
{
}

void ZedManager::ReadyRender()
{
}

void ZedManager::Release()
{
}
