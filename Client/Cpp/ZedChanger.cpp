#include "stdafx.h"
#include "..\Header\ZedChanger.h"
#include "UI.h"
#include "Sprite.h"

ZedChanger::ZedChanger(Desc * _desc)
{
	m_pZedSprite = _desc->ZedSprite;
	m_fMaxTime = _desc->fMaxTime;
	m_iPastNum = _desc->iPastNum;
}

ZedChanger::~ZedChanger()
{
}

void ZedChanger::Initialize()
{

}

void ZedChanger::Update()
{

	DEBUG_LOG(to_wstring(m_fCurTime));

	if (!m_bChange)
	{
		m_fCurTime += fTime;
	}

	if (m_fCurTime >= m_fMaxTime)
	{
		m_bChange = true;
		m_fCurTime = 0.f;

		while (true)
		{
			int iTemp = rand() % 8;

			if (m_iRandNum != iTemp)
			{
				m_iRandNum = iTemp;
				break;
			}
		}
		
	}

	if (m_bChange)
	{
		if (((Sprite*)m_pZedSprite->Get_Sprite())->Get_Alpha() > 0.f && m_bFadeOn == false)
		{
			((Sprite*)m_pZedSprite->Get_Sprite())->Add_Alpha(fTime * -1.f);
		}
		else
		{
			if (!m_bFadeOn)
			{
				((Sprite*)m_pZedSprite->Get_Sprite())->Set_Texture(L"MainMenu_Zeds_0" + to_wstring(m_iRandNum));
				m_bFadeOn = true;
			}
			else 
			{
				if (((Sprite*)m_pZedSprite->Get_Sprite())->Get_Alpha() < 1.f)
				{
					((Sprite*)m_pZedSprite->Get_Sprite())->Add_Alpha(fTime * 1.f);
				}
				else 
				{
					m_bFadeOn = false;
					m_bChange = false;
				}
			}

			
		
		}

		//((Sprite*)m_pZedSprite->Get_Sprite())->Set_Texture(L"MainMenu_Zeds_0" + to_wstring(m_iRandNum));
		//
		//m_bChange = false;
	}
}

void ZedChanger::LateUpdate()
{
}

void ZedChanger::ReadyRender()
{
}

void ZedChanger::Release()
{
}