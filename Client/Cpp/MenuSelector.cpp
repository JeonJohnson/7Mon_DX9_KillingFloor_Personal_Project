#include "stdafx.h"
#include "..\Header\MenuSelector.h"
#include "UI.h"
#include "Sprite.h"


MenuSelector::MenuSelector(Desc * _desc)
{
	m_vecButtons[0] = _desc->StartButton;
	m_vecButtons[1] = _desc->ExitButton;
	m_pLoading = _desc->Loading;
	m_pFade = _desc->Fade;

	m_pFadeSprite = (Sprite*)(m_pFade->Get_Sprite());
}

MenuSelector::~MenuSelector()
{
}

void MenuSelector::Initialize()
{
	
}

void MenuSelector::Update()
{
	DEBUG_LOG(L"Cur Scene : MainMenu");

	if (!m_bNextScene)
	{
		FadeOUt();
		CutScene_Sound();
		FadeIn();
		
			
		
	}
	else
	{
		//m_pLoading->Set_Active(true);
		EngineFunction->Load_Scene(L"Test_Scene"); 
		//m_bFadeIn = false;
	}


	for (int i = 0; i < 2; ++i)
	{
		if (m_vecButtons[i]->MouseOn())
		{
			((Sprite*)m_vecButtons[i]->Get_Sprite())->Set_Texture(L"HighLight");

			if (m_vecButtons[i]->Pressed())
			{
				((Sprite*)m_vecButtons[i]->Get_Sprite())->Set_Texture(L"Pressed");
			}
		}
		else 
		{
			((Sprite*)m_vecButtons[i]->Get_Sprite())->Set_Texture(L"Idle");
		}

		if (m_vecButtons[i]->ClickedUp())
		{
			switch (i)
			{
			case 0:
			{
				for (int i = 0; i < 2; ++i)
				{
					m_vecButtons[i]->Set_Active(false);
				}
				//m_pLoading->Set_Active(true);
				//EngineFunction->Load_Scene(L"Test_Scene"); 
				EngineFunction->StopAll_Sound();
				m_bFadeOut = true;
				m_pFade->Set_Active(true);
				m_pFadeSprite->Set_Alpha(0.f);

			}
			break;

			case 1:
			{
				PostQuitMessage(0);
			}
			break;
			
			default:
				break;
			}
			
		}
	}

	FadeIn();



}

void MenuSelector::LateUpdate()
{
}

void MenuSelector::ReadyRender()
{
}

void MenuSelector::Release()
{
}

bool MenuSelector::FadeIn()
{
	if (m_bFadeIn)
	{//밝아지기 (로딩씬 넘어가기 전)
		if (m_pFadeSprite->Get_Alpha() <= 0.f)
		{
			m_bFadeIn = false;
			m_bNextScene = true;
			return true;
		}
		else 
		{
			m_pFadeSprite->Add_Alpha(-1.f * fTime * 0.5f);
			return false;
		}
		return false;
	}
	return false;
}

bool MenuSelector::CutScene_Sound()
{
	if (m_bCutScene)
	{
		m_fCutSceneTime += fTime;



		////if (m_fCutSceneTime >= 10.f)
		////{
		////	m_bRadio = false;
		////}

		//if ()
		//{
		//	m_bExplosion = false;
		//}

		if (!m_bChopperFly && !m_bExplosion)
		{
			EngineFunction->Play_Sound(L"CutScene_Chopper_Fly.wav", SoundCH_BGM);
			//m_bChopperFly = true;
		}

		if (!m_bPullUp && !m_bExplosion)
		{
			EngineFunction->Play_Sound(L"CutScene_PullUp.wav", 20);
			//m_bPullUp = true;
		}

		if (m_fCutSceneTime >= 10.f && !m_bRadio)
		{
			EngineFunction->Play_Sound(L"CutScene_Radio_Voice.wav", 25);
			m_bRadio = true;
		}

		if (m_fCutSceneTime >= 20.f && !m_bExplosion)
		{
			EngineFunction->StopAll_Sound();
			EngineFunction->Play_Sound(L"CutScene_Chopper_Explosion.wav", 30);
			m_bChopperFly = true;
			m_bPullUp = true;
			m_bExplosion = true;
		}

		if (m_fCutSceneTime >= 30.f)
		{
			m_bFadeIn = true;
			m_pLoading->Set_Active(true);
			m_bCutScene = false;
			return true;
		}
	}
	return false;
}

bool MenuSelector::FadeOUt()
{
	if (m_bFadeOut)
	{//어두워지기.
		if (m_pFadeSprite->Get_Alpha() >= 1.f)
		{
			return true;
		}
		else
		{
			m_pFadeSprite->Add_Alpha(1.f * fTime * 0.5f);
			m_bCutScene = true;
			return false;
		}

	}
	return false;
}
