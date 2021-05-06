#include "stdafx.h"
#include "..\Header\IntroSkipper.h"

IntroSkipper::IntroSkipper(Desc * _desc)
{
	m_pFade = _desc->pFade;
	m_bOn = true;
	m_bOff = false;
}

IntroSkipper::~IntroSkipper()
{
}

void IntroSkipper::Initialize()
{
}

void IntroSkipper::Update()
{
	DEBUG_LOG(L"Cur Scene : Intro");

	if (m_bOn)
	{
		if (((Sprite*)(m_pFade->Get_Sprite()))->Get_Alpha() <= 0.f)
		{
			m_bOn = false; 
		}
		else 
		{
			((Sprite*)m_pFade->Get_Sprite())->Add_Alpha(-1.f * fTime * 0.5f);
		}
		
	}
	else 
	{
		m_fDeltaTime += fTime;

		if (m_fDeltaTime >= 2.f)
		{
			m_bOff = true;
		}
	}
	
	if (m_bOff)
	{
		if (((Sprite*)(m_pFade->Get_Sprite()))->Get_Alpha() < 1.f)
		{
			((Sprite*)m_pFade->Get_Sprite())->Add_Alpha(fTime * 0.5f);
		}
		else 
		{
			EngineFunction->Load_Scene(L"Test_Scene");
		}
		
	}

}

void IntroSkipper::LateUpdate()
{
}

void IntroSkipper::ReadyRender()
{
}

void IntroSkipper::Release()
{
}
