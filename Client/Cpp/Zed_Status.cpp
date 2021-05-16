#include "stdafx.h"
#include "..\Header\Zed_Status.h"


Zed_Status::Zed_Status(Desc * _desc)
{
	m_tZedStatus = _desc->tZedInfo;
}

Zed_Status::~Zed_Status()
{
}

void Zed_Status::Initialize()
{
}

void Zed_Status::Update()
{
	DEBUG_LOG(L"Zed Hp : " + to_wstring(m_tZedStatus.m_iCurHp));
}

void Zed_Status::LateUpdate()
{
}

void Zed_Status::ReadyRender()
{
}

void Zed_Status::Release()
{
}

ZED_INFO Zed_Status::Get_Status()
{
	return m_tZedStatus;
}

void Zed_Status::Damaged(int _iDmg)
{
	m_tZedStatus.m_iCurHp -= _iDmg;

	//애니메이션 돌리기. or 스테이트 바꾸기.   

	if (m_tZedStatus.m_iCurHp <= 0)
	{
		m_tZedStatus.m_iCurHp = 0;
	}
}
